#include "milone.h"

char str_literal_escape_Program_f(char arg_);

char str_literal_escape_Program_g(struct String arg_1);

int milone_main();

char str_literal_escape_Program_f(char arg_) {
    return 0;
}

char str_literal_escape_Program_g(struct String arg_1) {
    return 0;
}

int milone_main() {
    char call_ = str_literal_escape_Program_f('\'');
    char call_1 = str_literal_escape_Program_f('\\');
    char call_2 = str_literal_escape_Program_f('\0');
    char call_3 = str_literal_escape_Program_g((struct String){.str = "\"HELLO\n WORLD\"", .len = 14});
    return 0;
}
