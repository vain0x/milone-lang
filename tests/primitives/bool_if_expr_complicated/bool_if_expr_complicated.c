#include "milone.h"

int milone_main();

int milone_main() {
    int if_;
    if (true) {
        goto then_2;
    } else {
        goto else_6;
    }
then_2:;
    printf("then\n");
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int if_1;
    if (true) {
        goto then_4;
    } else {
        goto else_5;
    }
then_4:;
    if_1 = 0;
    goto if_next_3;
else_5:;
    printf("else: %s\n", str_to_c_str(hello_));
    if_1 = 1;
    goto if_next_3;
if_next_3:;
    if_ = if_1;
    goto if_next_1;
else_6:;
    printf("else\n");
    if_ = 1;
    goto if_next_1;
if_next_1:;
    return if_;
}
