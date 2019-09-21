#include "milone.h"

int fizzBuzz_(int i_);

int main();

int fizzBuzz_(int i_) {
    int match_;
    if ((15 < i_)) goto next_2;
    int match_1;
    if (((i_ % 15) != 0)) goto next_5;
    printf("FizzBuzz\n");
    int call_ = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (((i_ % 15) == 0)) goto next_6;
    int match_2;
    if (((i_ % 3) != 0)) goto next_8;
    printf("Fizz\n");
    int call_1 = 0;
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (((i_ % 3) == 0)) goto next_9;
    int match_3;
    if (((i_ % 5) != 0)) goto next_11;
    printf("Buzz\n");
    int call_2 = 0;
    match_3 = 0;
    goto end_match_10;
next_11:;
    if (((i_ % 5) == 0)) goto next_12;
    printf("%d\n", i_);
    int call_3 = 0;
    match_3 = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int call_4 = fizzBuzz_((i_ + 1));
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((15 >= i_)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return 0;
}

int main() {
    int call_5 = fizzBuzz_(1);
    return 0;
}
