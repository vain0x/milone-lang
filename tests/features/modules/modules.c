#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Val_;

int32_t modules_sub_Int32Int32Fun1_f(int32_t);

int main(int argc, char **argv);

enum Val_Discriminant {
    Val_Int,
    Val_String,
};

struct Val_ {
    enum Val_Discriminant discriminant;
    union {
        int32_t Val_Int;
        struct String Val_String;
    };
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t x_;
    int32_t n_;
    int32_t m_;
    int32_t match_;
    struct Val_ variant_;
    int32_t call_;
    variant_ = (struct Val_){.discriminant = Val_Int, .Val_Int = 0};
    if ((variant_.discriminant != Val_Int)) goto next_2;
    x_ = variant_.Val_Int;
    match_ = x_;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != Val_String)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_exhaust_error("modules/modules.milone", 8, 4);
end_match_1:;
    n_ = match_;
    call_ = modules_sub_Int32Int32Fun1_f(n_);
    m_ = call_;
    return m_;
}
