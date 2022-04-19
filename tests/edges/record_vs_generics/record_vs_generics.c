#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntWrapper_;

typedef struct IntWrapper_(*VoidConstPtrIntWrapper_FunPtr1)(void const*);

struct UnitIntWrapper_Fun1;

struct IntWrapper_ record_vs_generics_record_vs_generics_IntWrapperUnitIntWrapperFun2_constant(struct IntWrapper_ value_);

struct IntWrapper_ record_vs_generics_record_vs_generics_eta2_main_constant(void const* env_);

int main(int argc, char** argv);

struct IntWrapper_ {
    int32_t t0;
};

struct UnitIntWrapper_Fun1 {
    VoidConstPtrIntWrapper_FunPtr1 fun;
    void const* env;
};

struct IntWrapper_ record_vs_generics_record_vs_generics_IntWrapperUnitIntWrapperFun2_constant(struct IntWrapper_ value_) {
    return value_;
}

struct IntWrapper_ record_vs_generics_record_vs_generics_eta2_main_constant(void const* env_) {
    struct IntWrapper_ arg_1;
    struct IntWrapper_ call_;
    arg_1 = (*(((struct IntWrapper_ const*)env_)));
    call_ = record_vs_generics_record_vs_generics_IntWrapperUnitIntWrapperFun2_constant(arg_1);
    return call_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct UnitIntWrapper_Fun1 f_;
    struct IntWrapper_ wrapper_;
    struct IntWrapper_ IntWrapper_;
    void const* box_;
    struct UnitIntWrapper_Fun1 fun_;
    struct IntWrapper_ app_;
    IntWrapper_ = (struct IntWrapper_){.t0 = 42};
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct IntWrapper_)));
    (*(((struct IntWrapper_*)box_))) = IntWrapper_;
    fun_ = (struct UnitIntWrapper_Fun1){.fun = record_vs_generics_record_vs_generics_eta2_main_constant, .env = box_};
    f_ = fun_;
    app_ = f_.fun(f_.env);
    wrapper_ = app_;
    milone_assert((wrapper_.t0 == 42), (struct String){.ptr = "record_vs_generics/record_vs_generics.milone", .len = 44}, 12, 2);
    return 0;
}
