#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct MyOption_;

int main(int argc, char **argv);

enum MyOption_Discriminant {
    MyOption_MySome,
    MyOption_MyNone,
};

struct MyOption_ {
    enum MyOption_Discriminant discriminant;
    union {
        int32_t MyOption_MySome;
    };
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    char match_;
    struct MyOption_ variant_;
    variant_ = (struct MyOption_){.discriminant = MyOption_MySome, .MyOption_MySome = 1};
    if ((variant_.discriminant != MyOption_MySome)) goto next_2;
    if ((variant_.MyOption_MySome != 1)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != MyOption_MySome)) goto next_3;
    if (true) milone_assert_error("match_nested_nonbinding/match_nested_nonbinding.milone", 16, 16);
    match_ = 0;
    goto end_match_1;
next_3:;
    if ((variant_.discriminant != MyOption_MyNone)) goto next_4;
    if (true) milone_assert_error("match_nested_nonbinding/match_nested_nonbinding.milone", 17, 14);
    match_ = 0;
    goto end_match_1;
next_4:;
    milone_exhaust_error("match_nested_nonbinding/match_nested_nonbinding.milone", 14, 2);
end_match_1:;
    return 0;
}
