#include "milone.h"


      // Embedded by __nativeDecl.
      #include <stdio.h>
  
char writeLine_(struct String msg_);

int freshId_(char arg_);

int milone_main();


char writeLine_(struct String msg_) {

      fprintf(stdout, "%s\n", str_to_c_str(msg_));
        return 0;
}

int freshId_(char arg_) {

    static int s_last;
      return ++s_last;
}

int milone_main() {
    char call_ = writeLine_((struct String){.str = "HEY!", .len = 4});
    char call_1 = writeLine_((struct String){.str = "YO!", .len = 3});
    int call_2 = freshId_(0);
    struct String call_3 = str_of_int64(call_2);
    char call_4 = writeLine_(call_3);
    int call_5 = freshId_(0);
    struct String call_6 = str_of_int64(call_5);
    char call_7 = writeLine_(call_6);
    return 0;
}
