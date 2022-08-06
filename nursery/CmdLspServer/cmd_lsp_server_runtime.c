// Linux only.
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <milone.h>

int milone_lstat(struct String path) {
    struct stat st;
    bool ok = lstat(string_to_c_str(path), &st) == 0;
    if (ok == 0) {
        if (errno == ENOENT)
            return -2; // not found
        return -1;     // misc error
    }

    mode_t m = st.st_mode;
    if (S_ISREG(m))
        return 1;
    if (S_ISDIR(m))
        return 2;
    if (S_ISLNK(m))
        return 3;
    return 0; // other
}

struct DirIter *milone_dir_open(struct String dir) {
    DIR *dp = opendir(string_to_c_str(dir));
    return (struct DirIter *)dp;
}

void milone_dir_close(struct DirIter *dp) {
    bool ok = closedir((DIR *)dp);
    assert(ok == 0);
}

bool milone_dir_next(struct DirIter *dp, struct String *name) {
REDO:;
    struct dirent *entry = readdir((DIR *)dp);
    if (entry == NULL)
        return false;

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        goto REDO;

    *name = string_of_c_str(entry->d_name);
    return true;
}

// -----------------------------------------------
// process
// -----------------------------------------------

struct Subprocess {
    pid_t pid;
    bool alive;
    int exit_code;
    FILE *stdin_file;
    FILE *stdout_file;
};

struct StringCons {
    struct String head;
    struct StringCons *tail;
};

// Execute a subprocess and retrieves stdout and exit code.
int milone_subprocess_run2(struct String command, struct StringCons *args,
                          struct String *out_stdout) {
    assert(out_stdout != NULL);

    int stdout_fd[2];
    if (pipe(stdout_fd) != 0) {
        assert(false && "pipe(stdout)");
    }

    pid_t child = fork();
    assert(child != -1);

    if (child == 0) {
        // In child process:

        close(stdout_fd[0]);
        dup2(stdout_fd[1], STDOUT_FILENO);

        // cmd:
        char *cmd = (char *)string_to_c_str(command);

        // args:
        char *arg_array[16] = {cmd};
        int i = 1;
        for (struct StringCons *p = args; p != NULL; p = p->tail) {
            arg_array[i] = (char *)string_to_c_str(p->head);
            i++;
            assert(i < 15 && "too many args");
        }

        exit(execv(cmd, arg_array));
    }

    // In parent process:

    // stdio:
    close(stdout_fd[1]);
    FILE *stdout_file = fdopen(stdout_fd[0], "rb");

    // Read stdout. (trimmed to capacity)
    char buf[8000] = "";
    size_t i = 0;
    while (true) {
        size_t remain = sizeof(buf) - 1 - i;
        size_t read_size = fread(buf + i, 1, remain, stdout_file);
        if (read_size == 0) {
            break;
        }
        i += read_size;
    }

    *out_stdout = string_of_raw_parts(buf, i);

    // Join.
    int status;
    pid_t result = waitpid(child, &status, 0);
    assert(result == child);
    int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;

    return exit_code;
}
