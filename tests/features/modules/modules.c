#include "milone.h"

struct Val_;

int f_1(int x_);

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
    } payload;
};

int f_1(int x_) {
    return x_;
}

int milone_main() {
    int match_;
    struct Val_ variant_ = ((struct Val_){.discriminant = Int_, .payload = {.Int_ = 0}});
    if ((variant_.discriminant != Int_)) goto next_2;
    int x_1 = variant_.payload.Int_;
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
    int call_ = f_1(n_);
    int m_ = call_;
    return m_;
}
