#include "milone.h"

enum BoxedVariant_Discriminant;

struct BoxedVariant_;

struct BoxedVariant_OptionBoxedVariant_Fun1;

struct BoxedVariant_Option;

struct BoxedVariant_ feedNil_(struct BoxedVariant_OptionBoxedVariant_Fun1 f_);

int milone_main();

enum BoxedVariant_Discriminant {
    A_,
};

struct BoxedVariant_ {
    enum BoxedVariant_Discriminant discriminant;
    union {
        void const* A_;
    };
};

struct BoxedVariant_OptionBoxedVariant_Fun1 {
    struct BoxedVariant_(*fun)(void const*, struct BoxedVariant_Option);
    void const* env;
};

struct BoxedVariant_Option {
    bool some;
    struct BoxedVariant_ value;
};

struct BoxedVariant_ feedNil_(struct BoxedVariant_OptionBoxedVariant_Fun1 f_) {
    struct BoxedVariant_ app_ = f_.fun(f_.env, ((struct BoxedVariant_Option){}));
    return app_;
}

int milone_main() {
    return 0;
}
