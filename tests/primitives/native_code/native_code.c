#include "milone.h"


      // Embedded by __nativeDecl.
      #include <stdio.h>
  
char native_code_Program_writeLine(struct String msg_);

int native_code_Program_freshId(char arg_);

int milone_main();


char native_code_Program_writeLine(struct String msg_) {

      fprintf(stdout, "%s\n", str_to_c_str(msg_));
        return 0;
}

int native_code_Program_freshId(char arg_) {

    static int s_last;
      return ++s_last;
}

int milone_main() {
    char call_ = native_code_Program_writeLine((struct String){.str = "HEY!", .len = 4});
    char call_1 = native_code_Program_writeLine((struct String){.str = "YO!", .len = 3});
    int call_2 = native_code_Program_freshId(0);
    struct String call_3 = str_of_int64(call_2);
    char call_4 = native_code_Program_writeLine(call_3);
    int call_5 = native_code_Program_freshId(0);
    struct String call_6 = str_of_int64(call_5);
    char call_7 = native_code_Program_writeLine(call_6);
    return 0;
}
