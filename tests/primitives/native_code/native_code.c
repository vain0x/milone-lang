#include <milone.h>

struct IntUnitFun1;

uintptr_t native_code_native_code_nativeStmtWithTyPlaceholder_IntUnitFun1MutPtrUIntPtrFun1_alignOf(struct IntUnitFun1* arg_);

uintptr_t native_code_native_code_nativeStmtWithTyPlaceholder_IntMutPtrUIntPtrFun1_alignOf(int* arg_1);

uintptr_t native_code_native_code_nativeStmtWithTyPlaceholder_CharMutPtrUIntPtrFun1_alignOf(char* arg_2);


      // Embedded by __nativeDecl.
      #include <stdio.h>
  
void native_code_Program_writeLine(struct String msg_);

int native_code_Program_freshId(void);

void native_code_native_code_nativeExprWithPlaceholder(void);

void native_code_native_code_nativeStmtWithTyPlaceholder(void);

int main(int argc, char** argv);

struct IntUnitFun1 {
    void(*fun)(void const*, int);
    void const* env;
};

uintptr_t native_code_native_code_nativeStmtWithTyPlaceholder_IntUnitFun1MutPtrUIntPtrFun1_alignOf(struct IntUnitFun1* arg_) {
typedef struct IntUnitFun1 T;    return _Alignof(T);
}

uintptr_t native_code_native_code_nativeStmtWithTyPlaceholder_IntMutPtrUIntPtrFun1_alignOf(int* arg_1) {
typedef int T;    return _Alignof(T);
}

uintptr_t native_code_native_code_nativeStmtWithTyPlaceholder_CharMutPtrUIntPtrFun1_alignOf(char* arg_2) {
typedef char T;    return _Alignof(T);
}


void native_code_Program_writeLine(struct String msg_) {

      fprintf(stdout, "%s\n", str_to_c_str(msg_));
        return;
}

int native_code_Program_freshId(void) {

    static int s_last;
      return ++s_last;
}

void native_code_native_code_nativeExprWithPlaceholder(void) {
    struct String s_ = (struct String){.str = "hello", .len = 5};
    int n_ = s_.len;
    milone_assert((n_ == 5), (struct String){.str = "native_code/native_code.milone", .len = 30}, 29, 2);
    return;
}

void native_code_native_code_nativeStmtWithTyPlaceholder(void) {
    uintptr_t call_ = native_code_native_code_nativeStmtWithTyPlaceholder_CharMutPtrUIntPtrFun1_alignOf(((char*)0LL));
    milone_assert((call_ == (size_t)1ULL), (struct String){.str = "native_code/native_code.milone", .len = 30}, 37, 2);
    uintptr_t call_1 = native_code_native_code_nativeStmtWithTyPlaceholder_IntMutPtrUIntPtrFun1_alignOf(((int*)0LL));
    milone_assert((call_1 == (size_t)4ULL), (struct String){.str = "native_code/native_code.milone", .len = 30}, 38, 2);
    uintptr_t call_2 = native_code_native_code_nativeStmtWithTyPlaceholder_IntUnitFun1MutPtrUIntPtrFun1_alignOf(((struct IntUnitFun1*)0LL));
    milone_assert((call_2 == (size_t)8ULL), (struct String){.str = "native_code/native_code.milone", .len = 30}, 39, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    native_code_Program_writeLine((struct String){.str = "HEY!", .len = 4});
    native_code_Program_writeLine((struct String){.str = "YO!", .len = 3});
    int call_3 = native_code_Program_freshId();
    struct String call_4 = str_of_int64(call_3);
    native_code_Program_writeLine(call_4);
    int call_5 = native_code_Program_freshId();
    struct String call_6 = str_of_int64(call_5);
    native_code_Program_writeLine(call_6);
    native_code_native_code_nativeExprWithPlaceholder();
    native_code_native_code_nativeStmtWithTyPlaceholder();
    return 0;
}
