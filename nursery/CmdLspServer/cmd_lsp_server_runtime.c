// Linux only.
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <milone.h>

int milone_lstat(struct String path) {
    struct stat st;
    bool ok = lstat(str_to_c_str(path), &st) == 0;
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
    DIR *dp = opendir(str_to_c_str(dir));
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

    *name = str_of_c_str(entry->d_name);
    return true;
}
