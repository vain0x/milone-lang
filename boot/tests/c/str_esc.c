int f_1(char __2) {
    return 0;
}

int g_3(char* __4) {
    return 0;
}

int main() {
    int call_7 = f_1('\'');
    int call_8 = f_1('\\');
    int call_9 = f_1('\0');
    int call_10 = g_3("\"HELLO\n WORLD\"");
    return 0;
}
