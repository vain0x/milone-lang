#include "milone.h"

struct Val_;

int modules_sub_IntIntFun1_f(int );

int milone_main(void);

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

int milone_main(void) {
    int x_;
    int match_;
    struct Val_ variant_ = (struct Val_){.discriminant = Int_, .Int_ = 0};
    if ((variant_.discriminant != Int_)) goto next_2;
    x_ = variant_.Int_;
    match_ = x_;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != Str_)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int n_ = match_;
    int call_ = modules_sub_IntIntFun1_f(n_);
    int m_ = call_;
    return m_;
}
