#include "milone.h"

char printIntOrStr_(bool isInt_, void const* value_);

int milone_main();

char printIntOrStr_(bool isInt_, void const* value_) {
    char if_;
    if (isInt_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    printf("%d\n", (*(((int const*)value_))));
    if_ = 0;
    goto if_next_1;
else_3:;
    printf("%s\n", str_to_c_str((*(((struct String const*)value_)))));
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return 0;
}

int milone_main() {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 2;
    char call_ = printIntOrStr_(true, box_);
    void const* box_1 = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_1))) = (struct String){.str = "Fizz", .len = 4};
    char call_1 = printIntOrStr_(false, box_1);
    return 0;
}
