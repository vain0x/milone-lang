#include "milone.h"


      // Embedded by __nativeDecl.
      #include <stdio.h>

      static int s_write_count;

      void write_line(struct String s) {
          fprintf(stdout, "%s\n", s.str);
      }
  
void write_line(struct String);

int writeLine_(struct String msg_);

int getWriteCount_(int arg_);

int milone_main();


int writeLine_(struct String msg_) {

      s_write_count++;
      write_line(msg_);
    return 0;
}

int getWriteCount_(int arg_) {
    return s_write_count;
}

int milone_main() {
    int call_ = writeLine_((struct String){.str = "HEY!", .len = 4});
    int call_1 = writeLine_((struct String){.str = "YO!", .len = 3});
    int call_2 = getWriteCount_(0);
    struct String call_3 = str_of_int64(call_2);
    int call_4 = writeLine_(call_3);
    return 0;
}
