#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct BoxedVariant_;

struct BoxedVariantoption1_;

typedef struct BoxedVariant_(*VoidConstPtrBoxedVariantoption1_BoxedVariant_FunPtr2)(void const *, struct BoxedVariantoption1_);

struct BoxedVariantoption1_BoxedVariant_Fun1;

struct BoxedVariant_ resolved_issues_variant_wrapper_auto_box_feedNil(struct BoxedVariantoption1_BoxedVariant_Fun1 f_);

struct BoxedVariant_ resolved_issues_variant_wrapper_auto_box_eta2_A(void const *env_, struct BoxedVariantoption1_ arg_);

void resolved_issues_variant_wrapper_auto_box_test(void);

void resolved_issues_variant_wrapper_auto_box_start(void);

enum BoxedVariant_Discriminant {
    BoxedVariant_A,
};

struct BoxedVariant_ {
    enum BoxedVariant_Discriminant discriminant;
    union {
        void const *BoxedVariant_A;
    };
};

enum BoxedVariantoption1_Discriminant {
    BoxedVariantoption1_None,
    BoxedVariantoption1_Some,
};

struct BoxedVariantoption1_ {
    enum BoxedVariantoption1_Discriminant discriminant;
    union {
        struct BoxedVariant_ BoxedVariantoption1_Some;
    };
};

struct BoxedVariantoption1_BoxedVariant_Fun1 {
    VoidConstPtrBoxedVariantoption1_BoxedVariant_FunPtr2 fun;
    void const *env;
};

struct BoxedVariant_ resolved_issues_variant_wrapper_auto_box_feedNil(struct BoxedVariantoption1_BoxedVariant_Fun1 f_) {
    struct BoxedVariant_ app_;
    app_ = f_.fun(f_.env, (struct BoxedVariantoption1_){.discriminant = BoxedVariantoption1_None});
    return app_;
}

struct BoxedVariant_ resolved_issues_variant_wrapper_auto_box_eta2_A(void const *env_, struct BoxedVariantoption1_ arg_) {
    void const *box_;
    struct BoxedVariant_ variant_;
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct BoxedVariantoption1_)));
    (*(((struct BoxedVariantoption1_ *)box_))) = arg_;
    variant_ = (struct BoxedVariant_){.discriminant = BoxedVariant_A, .BoxedVariant_A = box_};
    return variant_;
}

void resolved_issues_variant_wrapper_auto_box_test(void) {
    struct BoxedVariant_ result_;
    struct BoxedVariantoption1_BoxedVariant_Fun1 fun_;
    struct BoxedVariant_ call_;
    fun_ = (struct BoxedVariantoption1_BoxedVariant_Fun1){.fun = resolved_issues_variant_wrapper_auto_box_eta2_A, .env = NULL};
    call_ = resolved_issues_variant_wrapper_auto_box_feedNil(fun_);
    result_ = call_;
    return;
}

void resolved_issues_variant_wrapper_auto_box_start(void) {
    resolved_issues_variant_wrapper_auto_box_test();
    return;
}
