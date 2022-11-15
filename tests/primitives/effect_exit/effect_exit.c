#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

_Noreturn void MiloneCore_Prelude_exit(int32_t);

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    MiloneCore_Prelude_exit(1);
    milone_never_error("effect_exit/effect_exit.milone", 2, 0);
}
