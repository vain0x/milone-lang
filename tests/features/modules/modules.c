#include "milone.h"

struct Val_;

int f_(int);

int milone_main();

enum Val_Discriminant {
    Int_,
    Str_,
};

struct Val_ {
    enum Val_Discriminant discriminant;
    union {
        int Int_;
        struct String Str_;
    };
};

int milone_main() {
    int x_1;
    int match_;
    struct Val_ variant_ = (struct Val_){.discriminant = Int_, .Int_ = 0};
    if ((variant_.discriminant != Int_)) goto next_2;
    x_1 = variant_.Int_;
    match_ = x_1;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != Str_)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int n_ = match_;
    int call_ = f_(n_);
    int m_ = call_;
    return m_;
}
