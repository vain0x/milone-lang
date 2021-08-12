#include "milone.h"

void str_literal_escape_Program_f(char arg_);

void str_literal_escape_Program_g(struct String arg_1);

int milone_main(void);

void str_literal_escape_Program_f(char arg_) {
    return;
}

void str_literal_escape_Program_g(struct String arg_1) {
    return;
}

int milone_main(void) {
    str_literal_escape_Program_f('\'');
    str_literal_escape_Program_f('\\');
    str_literal_escape_Program_f('\0');
    str_literal_escape_Program_g((struct String){.str = "\"HELLO\n WORLD\"", .len = 14});
    return 0;
}
