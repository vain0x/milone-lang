#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct BoxedVariant_;

struct BoxedVariantoption1_;

typedef struct BoxedVariant_(*VoidConstPtrBoxedVariantoption1_BoxedVariant_FunPtr2)(void const*, struct BoxedVariantoption1_);

struct BoxedVariantoption1_BoxedVariant_Fun1;

struct BoxedVariant_ variant_fun_auto_boxing_bug_variant_fun_auto_boxing_bug_feedNil(struct BoxedVariantoption1_BoxedVariant_Fun1 f_);

int main(int argc, char** argv);

enum BoxedVariant_Discriminant {
    A_,
};

struct BoxedVariant_ {
    enum BoxedVariant_Discriminant discriminant;
    union {
        void const* A_;
    };
};

enum BoxedVariantoption1_Discriminant {
    None_,
    Some_,
};

struct BoxedVariantoption1_ {
    enum BoxedVariantoption1_Discriminant discriminant;
    union {
        struct BoxedVariant_ Some_;
    };
};

struct BoxedVariantoption1_BoxedVariant_Fun1 {
    VoidConstPtrBoxedVariantoption1_BoxedVariant_FunPtr2 fun;
    void const* env;
};

struct BoxedVariant_ variant_fun_auto_boxing_bug_variant_fun_auto_boxing_bug_feedNil(struct BoxedVariantoption1_BoxedVariant_Fun1 f_) {
    struct BoxedVariant_ app_;
    app_ = f_.fun(f_.env, (struct BoxedVariantoption1_){.discriminant = None_});
    return app_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    return 0;
}
