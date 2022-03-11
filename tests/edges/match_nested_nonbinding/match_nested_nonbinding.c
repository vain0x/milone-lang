#include <milone.h>

struct MyBool_;

struct MyOption_;

int main(int argc, char** argv);

enum MyBool_Discriminant {
    MyFalse_,
    MyTrue_,
};

struct MyBool_ {
    enum MyBool_Discriminant discriminant;
};

enum MyOption_Discriminant {
    MySome_,
    MyNone_,
};

struct MyOption_ {
    enum MyOption_Discriminant discriminant;
    union {
        struct MyBool_ MySome_;
    };
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    char match_;
    struct MyOption_ variant_;
    variant_ = (struct MyOption_){.discriminant = MySome_, .MySome_ = (struct MyBool_){.discriminant = MyTrue_}};
    if ((variant_.discriminant != MySome_)) goto next_2;
    if ((variant_.MySome_.discriminant != MyTrue_)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != MySome_)) goto next_3;
    milone_assert(false, (struct String){.str = "match_nested_nonbinding/match_nested_nonbinding.milone", .len = 54}, 16, 16);
    match_ = 0;
    goto end_match_1;
next_3:;
    if ((variant_.discriminant != MyNone_)) goto next_4;
    milone_assert(false, (struct String){.str = "match_nested_nonbinding/match_nested_nonbinding.milone", .len = 54}, 17, 14);
    match_ = 0;
    goto end_match_1;
next_4:;
    exit(1);
end_match_1:;
    return 0;
}
