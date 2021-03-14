#include "milone.h"

struct StringOption;

struct GitCommitOptions_;

void const* defaultOptions_(char arg_);

int milone_main();

struct StringOption {
    bool some;
    struct String value;
};

struct GitCommitOptions_ {
    bool t0;
    bool t1;
    struct StringOption t2;
    struct StringOption t3;
    struct StringOption t4;
    struct StringOption t5;
    bool t6;
};

void const* defaultOptions_(char arg_) {
    struct GitCommitOptions_ GitCommitOptions_ = (struct GitCommitOptions_){.t0 = false, .t1 = false, .t2 = (struct StringOption){.some = false}, .t3 = (struct StringOption){.some = false}, .t4 = (struct StringOption){.some = false}, .t5 = (struct StringOption){.some = false}, .t6 = false};
    void const* box_ = milone_mem_alloc(1, sizeof(struct GitCommitOptions_));
    (*(((struct GitCommitOptions_*)box_))) = GitCommitOptions_;
    return box_;
}

int milone_main() {
    void const* call_ = defaultOptions_(0);
    void const* _options_ = call_;
    return 0;
}
