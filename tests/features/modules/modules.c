#include "milone.h"

int f_1(int x_1);

enum Val_Tag;

struct Val_;

int main();

int f_1(int x_1) {
    return x_1;
}

enum Val_Tag {
    Int_,
    Str_,
};

struct Val_ {
    enum Val_Tag tag;
    union {
        void* Int_;
        void* Str_;
    };
};

int main() {
    int match_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    struct Val_ variant_ = (struct Val_){.tag = Int_, .Int_ = box_};
    if ((variant_.tag != Int_)) goto next_2;
    int x_ = (*(((int*)variant_.Int_)));
    match_ = x_;
    goto end_match_1;
next_2:;
    if ((variant_.tag != Str_)) goto next_3;
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
