#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Stringoption1_;

struct GitCommitOptions_;

void const *record_large_record_large_defaultOptions(void);

int main(int argc, char **argv);

enum Stringoption1_Discriminant {
    None_,
    Some_,
};

struct Stringoption1_ {
    enum Stringoption1_Discriminant discriminant;
    union {
        struct String Some_;
    };
};

struct GitCommitOptions_ {
    bool t0;
    bool t1;
    struct Stringoption1_ t2;
    struct Stringoption1_ t3;
    struct Stringoption1_ t4;
    struct Stringoption1_ t5;
    bool t6;
};

void const *record_large_record_large_defaultOptions(void) {
    struct GitCommitOptions_ GitCommitOptions_;
    void const *box_;
    GitCommitOptions_ = (struct GitCommitOptions_){.t0 = false, .t1 = false, .t2 = (struct Stringoption1_){.discriminant = None_}, .t3 = (struct Stringoption1_){.discriminant = None_}, .t4 = (struct Stringoption1_){.discriminant = None_}, .t5 = (struct Stringoption1_){.discriminant = None_}, .t6 = false};
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct GitCommitOptions_)));
    (*(((struct GitCommitOptions_ *)box_))) = GitCommitOptions_;
    return box_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    void const *_options;
    void const *call_;
    call_ = record_large_record_large_defaultOptions();
    _options = call_;
    return 0;
}
