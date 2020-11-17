#include "milone.h"

int fizzBuzz_(int i_);

int main();

int fizzBuzz_(int i_) {
tailrec_1:;
    int if_;
    if ((15 < i_)) goto else_2;
    int if_1;
    if (((i_ % 15) != 0)) goto else_4;
    printf("FizzBuzz\n");
    int call_ = 0;
    if_1 = 0;
    goto end_if_5;
else_4:;
    int if_2;
    if (((i_ % 3) != 0)) goto else_6;
    printf("Fizz\n");
    int call_1 = 0;
    if_2 = 0;
    goto end_if_7;
else_6:;
    int if_3;
    if (((i_ % 5) != 0)) goto else_8;
    printf("Buzz\n");
    int call_2 = 0;
    if_3 = 0;
    goto end_if_9;
else_8:;
    printf("%d\n", i_);
    int call_3 = 0;
    if_3 = 0;
end_if_9:;
    if_2 = 0;
end_if_7:;
    if_1 = 0;
end_if_5:;
    int arg_ = (i_ + 1);
    i_ = arg_;
    goto tailrec_1;
    if_ = 0;
    goto end_if_3;
else_2:;
    if_ = 0;
end_if_3:;
    return 0;
}

int main() {
    int call_4 = fizzBuzz_(1);
    return 0;
}
