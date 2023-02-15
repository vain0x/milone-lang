// Example use of MiloneDll.so

#include <assert.h>
#include <dlfcn.h>
#include <milone.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*MiloneInitializeFn)(int, char **);
typedef char const *(*MiloneParseFn)(char const *);

int main(int argc, char **argv) {
    void *lib =
        dlopen("./target/MiloneDll/MiloneDll.so",
               RTLD_LAZY);
    if (lib == NULL) {
        fprintf(stderr, "ERROR: %s\n", dlerror());
        abort();
    }

    MiloneInitializeFn initializeFn =
        (MiloneInitializeFn)dlsym(lib, "MiloneDll_initialize");
    if (initializeFn == NULL) {
        fprintf(stderr, "ERROR: %s\n", dlerror());
        abort();
    }

    // fprintf(stderr, "trace: initialize dll\n");
    initializeFn(argc, argv);

    MiloneParseFn parseFn = (MiloneParseFn)dlsym(lib, "milone_parse");
    if (parseFn == NULL) {
        fprintf(stderr, "ERROR: %s\n", dlerror());
        abort();
    }

    char const *text = "let main _ =\n  0\n";
    char const *output = parseFn(text);
    fprintf(stdout, "output (%lu):\n", (unsigned long)strlen(output));
    fprintf(stdout, "%s", output);
    return 0;
}
