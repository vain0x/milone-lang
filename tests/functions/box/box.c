#include "milone.h"

int printIntOrStr_(bool isInt_, void* value_);

int main();

int printIntOrStr_(bool isInt_, void* value_) {
    int if_;
    if (isInt_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    printf("%d\n", (*(((int*)value_))));
    if_ = 0;
    goto if_next_1;
else_3:;
    printf("%s\n", (*(((struct String*)value_))).str);
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return 0;
}

int main() {
    void* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 2;
    int call_ = printIntOrStr_(true, box_);
    void* box_1 = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_1))) = (struct String){.str = "Fizz", .len = 4};
    int call_1 = printIntOrStr_(false, box_1);
    return 0;
}
