#include <milone.h>


      // Embedded by __nativeDecl.
      #include <stdio.h>
  
void native_code_Program_writeLine(struct String msg_);

int native_code_Program_freshId(void);

void native_code_native_code_nativeExprWithPlaceholder(void);

int main(int argc, char** argv);


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

int main(int argc, char** argv) {
    milone_start(argc, argv);
    native_code_Program_writeLine((struct String){.str = "HEY!", .len = 4});
    native_code_Program_writeLine((struct String){.str = "YO!", .len = 3});
    int call_ = native_code_Program_freshId();
    struct String call_1 = str_of_int64(call_);
    native_code_Program_writeLine(call_1);
    int call_2 = native_code_Program_freshId();
    struct String call_3 = str_of_int64(call_2);
    native_code_Program_writeLine(call_3);
    native_code_native_code_nativeExprWithPlaceholder();
    return 0;
}
