int f_(char __);

int g_(struct String __1);

int main();

int f_(char __) {
    return 0;
}

int g_(struct String __1) {
    return 0;
}

int main() {
    int call_ = f_('\'');
    int call_1 = f_('\\');
    int call_2 = f_('\0');
    int call_3 = g_((struct String){.str = "\"HELLO\n WORLD\"", .len = 14});
    return 0;
}
