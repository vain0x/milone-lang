#include "milone.h"

int printIntOrStr_(int isInt_, void* value_);

int main();

int printIntOrStr_(int isInt_, void* value_) {
    int if_;
    if ((!(isInt_))) goto else_1;
    printf("%d\n", (*(((int*)value_))));
    int call_ = 0;
    if_ = 0;
    goto end_if_2;
else_1:;
    printf("%s\n", (*(((struct String*)value_))).str);
    int call_1 = 0;
    if_ = 0;
end_if_2:;
    return 0;
}

int main() {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 2;
    int call_2 = printIntOrStr_(1, box_);
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_1))) = (struct String){.str = "Fizz", .len = 4};
    int call_3 = printIntOrStr_(0, box_1);
    return 0;
}
