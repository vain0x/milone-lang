#include "milone.h"

int fizzBuzz_(int i_);

int main();

int fizzBuzz_(int i_) {
tailrec_1:;
    int match_;
    if ((15 < i_)) goto next_3;
    int match_1;
    if (((i_ % 15) != 0)) goto next_6;
    printf("FizzBuzz\n");
    int call_ = 0;
    match_1 = 0;
    goto end_match_5;
next_6:;
    if (((i_ % 15) == 0)) goto next_7;
    int match_2;
    if (((i_ % 3) != 0)) goto next_9;
    printf("Fizz\n");
    int call_1 = 0;
    match_2 = 0;
    goto end_match_8;
next_9:;
    if (((i_ % 3) == 0)) goto next_10;
    int match_3;
    if (((i_ % 5) != 0)) goto next_12;
    printf("Buzz\n");
    int call_2 = 0;
    match_3 = 0;
    goto end_match_11;
next_12:;
    if (((i_ % 5) == 0)) goto next_13;
    printf("%d\n", i_);
    int call_3 = 0;
    match_3 = 0;
    goto end_match_11;
next_13:;
    exit(1);
end_match_11:;
    match_2 = 0;
    goto end_match_8;
next_10:;
    exit(1);
end_match_8:;
    match_1 = 0;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    int arg_ = (i_ + 1);
    i_ = arg_;
    goto tailrec_1;
    match_ = 0;
    goto end_match_2;
next_3:;
    if ((15 >= i_)) goto next_4;
    match_ = 0;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return 0;
}

int main() {
    int call_4 = fizzBuzz_(1);
    return 0;
}
