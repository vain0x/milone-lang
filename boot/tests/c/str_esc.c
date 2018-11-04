int f_1(char __2) {
    return 0;
}

int g_3(struct String __4) {
    return 0;
}

int main() {
    int call_7 = f_1('\'');
    int call_8 = f_1('\\');
    int call_9 = f_1('\0');
    int call_10 = g_3((struct String){.str = "\"HELLO\n WORLD\"", .len = 14});
    return 0;
}
