#include "milone.h"


      // Embedded by __nativeDecl.
      #include <stdio.h>
  
void native_code_Program_writeLine(struct String msg_);

int native_code_Program_freshId(void);

void nativeExprWithPlaceholder_(void);

int milone_main(void);


void native_code_Program_writeLine(struct String msg_) {

      fprintf(stdout, "%s\n", str_to_c_str(msg_));
        return;
}

int native_code_Program_freshId(void) {

    static int s_last;
      return ++s_last;
}

void nativeExprWithPlaceholder_(void) {
    struct String s_ = (struct String){.str = "hello", .len = 5};
    int n_ = s_.len;
    milone_assert((n_ == 5), 29, 2);
    return;
}

int milone_main(void) {
    native_code_Program_writeLine((struct String){.str = "HEY!", .len = 4});
    native_code_Program_writeLine((struct String){.str = "YO!", .len = 3});
    int call_ = native_code_Program_freshId();
    struct String call_1 = str_of_int64(call_);
    native_code_Program_writeLine(call_1);
    int call_2 = native_code_Program_freshId();
    struct String call_3 = str_of_int64(call_2);
    native_code_Program_writeLine(call_3);
    nativeExprWithPlaceholder_();
    return 0;
}
