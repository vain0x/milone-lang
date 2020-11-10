#include "milone.h"

int printIntOrStr_(int isInt_, void* value_);

int main();

int printIntOrStr_(int isInt_, void* value_) {
    int match_;
    if ((!(isInt_))) goto next_2;
    printf("%d\n", (*(((int*)value_))));
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    if (isInt_) goto next_3;
    printf("%s\n", (*(((struct String*)value_))).str);
    int call_1 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
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
