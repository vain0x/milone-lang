int not_2(int arg_6) {
    printf("shadowing not\n");
    int call_7 = 0;
    return 0;
}

int main() {
    int if_4;
    if (!(0)) {
        printf("not false\n");
        int call_5 = 0;
        if_4 = 0;
    } else {
        if_4 = 0;
    }
    int call_8 = not_2(0);
    return 0;
}
