#include "milone.h"

struct BoxedVariant_;

struct BoxedVariantOption_;

struct BoxedVariantOption_BoxedVariant_Fun1;

struct BoxedVariant_ variant_fun_auto_boxing_bug_Program_feedNil(struct BoxedVariantOption_BoxedVariant_Fun1 f_);

int milone_main(void);

enum BoxedVariant_Discriminant {
    A_,
};

struct BoxedVariant_ {
    enum BoxedVariant_Discriminant discriminant;
    union {
        void const* A_;
    };
};

enum BoxedVariantOption_Discriminant {
    None_,
    Some_,
};

struct BoxedVariantOption_ {
    enum BoxedVariantOption_Discriminant discriminant;
    union {
        struct BoxedVariant_ Some_;
    };
};

struct BoxedVariantOption_BoxedVariant_Fun1 {
    struct BoxedVariant_(*fun)(void const*, struct BoxedVariantOption_);
    void const* env;
};

struct BoxedVariant_ variant_fun_auto_boxing_bug_Program_feedNil(struct BoxedVariantOption_BoxedVariant_Fun1 f_) {
    struct BoxedVariant_ app_ = f_.fun(f_.env, (struct BoxedVariantOption_){.discriminant = None_});
    return app_;
}

int milone_main(void) {
    return 0;
}
