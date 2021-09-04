#include "milone.h"

struct StringStringTuple2_;

void const* dup_(void const* arg_);

void const* bug_(void const* b_);

int milone_main(void);

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

void const* dup_(void const* arg_) {
    struct String x_ = (*(((struct String const*)arg_)));
    struct StringStringTuple2_ StringStringTuple2_ = (struct StringStringTuple2_){.t0 = x_, .t1 = x_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct StringStringTuple2_));
    (*(((struct StringStringTuple2_*)box_))) = StringStringTuple2_;
    return box_;
}

void const* bug_(void const* b_) {
    void const* call_ = dup_(b_);
    return call_;
}

int milone_main(void) {
    printf("x1 = \'a\'\n");
    printf("x2 = \'a\'\n");
    return 0;
}
