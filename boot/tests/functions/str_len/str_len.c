#include "milone.h"

int main();

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    struct String world_ = (struct String){.str = "world", .len = 5};
    int match_;
    if (!(((hello_.len != 5) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((hello_.len != 5) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    struct String message_ = str_add(hello_, world_);
    int match_1;
    if (!(((message_.len != 10) == 1))) goto next_5;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((message_.len != 10) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int match_2;
    if (!(((hello_.len != 5) == 1))) goto next_8;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!(((hello_.len != 5) == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return 0;
}
