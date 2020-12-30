#include "milone.h"

struct StringList;

struct GitCommitOptions_;

void const* defaultOptions_(int arg_);

int main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct GitCommitOptions_ {
    bool t0;
    bool t1;
    struct StringList const* t2;
    struct StringList const* t3;
    struct StringList const* t4;
    struct StringList const* t5;
    bool t6;
};

void const* defaultOptions_(int arg_) {
    struct GitCommitOptions_ GitCommitOptions_ = (struct GitCommitOptions_){.t0 = false, .t1 = false, .t2 = NULL, .t3 = NULL, .t4 = NULL, .t5 = NULL, .t6 = false};
    void const* box_ = milone_mem_alloc(1, sizeof(struct GitCommitOptions_));
    (*(((struct GitCommitOptions_*)box_))) = GitCommitOptions_;
    return box_;
}

int main() {
    void const* call_ = defaultOptions_(0);
    void const* _options_ = call_;
    return 0;
}
