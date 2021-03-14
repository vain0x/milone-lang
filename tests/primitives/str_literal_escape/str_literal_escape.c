#include "milone.h"

char f_(char arg_);

char g_(struct String arg_1);

int milone_main();

char f_(char arg_) {
    return 0;
}

char g_(struct String arg_1) {
    return 0;
}

int milone_main() {
    char call_ = f_('\'');
    char call_1 = f_('\\');
    char call_2 = f_('\0');
    char call_3 = g_((struct String){.str = "\"HELLO\n WORLD\"", .len = 14});
    return 0;
}
