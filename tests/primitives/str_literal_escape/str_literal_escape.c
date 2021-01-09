#include "milone.h"

int f_(char arg_);

int g_(struct String arg_1);

int milone_main();

int f_(char arg_) {
    return 0;
}

int g_(struct String arg_1) {
    return 0;
}

int milone_main() {
    int call_ = f_('\'');
    int call_1 = f_('\\');
    int call_2 = f_('\0');
    int call_3 = g_((struct String){.str = "\"HELLO\n WORLD\"", .len = 14});
    return 0;
}
