#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef void(*VoidConstPtrInt32VoidFunPtr2)(void const *, int32_t);

struct Int32UnitFun1;


      // Embedded by __nativeDecl.
      #include <stdio.h>
  
uintptr_t native_code_native_code_Int32UnitFun1MutPtrUIntPtrFun1_alignOf(struct Int32UnitFun1 *arg_);

uintptr_t native_code_native_code_Int32MutPtrUIntPtrFun1_alignOf(int32_t *arg_1);

uintptr_t native_code_native_code_CharMutPtrUIntPtrFun1_alignOf(char *arg_2);

void native_code_native_code_writeLine(struct String msg_);

int32_t native_code_native_code_freshId(void);

void native_code_native_code_nativeExprWithPlaceholder(void);

void native_code_native_code_nativeStmtWithTyPlaceholder(void);

int main(int argc, char **argv);

struct Int32UnitFun1 {
    VoidConstPtrInt32VoidFunPtr2 fun;
    void const *env;
};


uintptr_t native_code_native_code_Int32UnitFun1MutPtrUIntPtrFun1_alignOf(struct Int32UnitFun1 *arg_) {
typedef struct Int32UnitFun1 T;    return _Alignof(T);
}

uintptr_t native_code_native_code_Int32MutPtrUIntPtrFun1_alignOf(int32_t *arg_1) {
typedef int32_t T;    return _Alignof(T);
}

uintptr_t native_code_native_code_CharMutPtrUIntPtrFun1_alignOf(char *arg_2) {
typedef char T;    return _Alignof(T);
}

void native_code_native_code_writeLine(struct String msg_) {

      fprintf(stdout, "%s\n", string_to_c_str(msg_));
        return;
}

int32_t native_code_native_code_freshId(void) {

    static int s_last;
      return ++s_last;
}

void native_code_native_code_nativeExprWithPlaceholder(void) {
    struct String s_;
    int32_t n_;
    s_ = (struct String){.ptr = "hello", .len = 5};
    n_ = s_.len;
    if ((n_ != 5)) milone_assert_error("native_code/native_code.milone", 32, 2);
    return;
}

void native_code_native_code_nativeStmtWithTyPlaceholder(void) {
    uintptr_t call_;
    uintptr_t call_1;
    uintptr_t call_2;
    call_ = native_code_native_code_CharMutPtrUIntPtrFun1_alignOf(((char *)NULL));
    if ((call_ != (size_t)1ULL)) milone_assert_error("native_code/native_code.milone", 40, 2);
    call_1 = native_code_native_code_Int32MutPtrUIntPtrFun1_alignOf(((int32_t *)NULL));
    if ((call_1 != (size_t)4ULL)) milone_assert_error("native_code/native_code.milone", 41, 2);
    call_2 = native_code_native_code_Int32UnitFun1MutPtrUIntPtrFun1_alignOf(((struct Int32UnitFun1 *)NULL));
    if ((call_2 != (size_t)8ULL)) milone_assert_error("native_code/native_code.milone", 42, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_3;
    struct String call_4;
    int32_t call_5;
    struct String call_6;
    native_code_native_code_writeLine((struct String){.ptr = "HEY!", .len = 4});
    native_code_native_code_writeLine((struct String){.ptr = "YO!", .len = 3});
    call_3 = native_code_native_code_freshId();
    call_4 = string_of_int64(call_3);
    native_code_native_code_writeLine(call_4);
    call_5 = native_code_native_code_freshId();
    call_6 = string_of_int64(call_5);
    native_code_native_code_writeLine(call_6);
    native_code_native_code_nativeExprWithPlaceholder();
    native_code_native_code_nativeStmtWithTyPlaceholder();
    return 0;
}
