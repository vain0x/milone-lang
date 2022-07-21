#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct MyBool_;

struct MyOption_;

int main(int argc, char **argv);

enum MyBool_Discriminant {
    MyBool_MyFalse,
    MyBool_MyTrue,
};

struct MyBool_ {
    enum MyBool_Discriminant discriminant;
};

enum MyOption_Discriminant {
    MyOption_MySome,
    MyOption_MyNone,
};

struct MyOption_ {
    enum MyOption_Discriminant discriminant;
    union {
        struct MyBool_ MyOption_MySome;
    };
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    char match_;
    struct MyOption_ variant_;
    variant_ = (struct MyOption_){.discriminant = MyOption_MySome, .MyOption_MySome = (struct MyBool_){.discriminant = MyBool_MyTrue}};
    if ((variant_.discriminant != MyOption_MySome)) goto next_2;
    if ((variant_.MyOption_MySome.discriminant != MyBool_MyTrue)) goto next_2;
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
    exit(1);
end_match_1:;
    return 0;
}
