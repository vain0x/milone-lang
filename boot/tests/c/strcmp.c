int main() {
    int le_2 = (strcmp("a", "b") < 0);
    int eq_3 = (strcmp("o", "o") == 0);
    int if_5;
    int if_6;
    if (le_2) {
        if_6 = eq_3;
    } else {
        if_6 = 0;
    }
    if (if_6) {
        if_5 = 0;
    } else {
        if_5 = 1;
    }
    return if_5;
}
