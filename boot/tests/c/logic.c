int main() {
    int if_3;
    int if_4;
    int if_5;
    if ((1 <= 2)) {
        if_5 = (2 < 3);
    } else {
        if_5 = 0;
    }
    if (if_5) {
        if_4 = 1;
    } else {
        int if_6;
        if ((2 < 3)) {
            if_6 = (1 <= 2);
        } else {
            if_6 = 0;
        }
        if_4 = if_6;
    }
    if (if_4) {
        if_3 = 0;
    } else {
        if_3 = 1;
    }
    return if_3;
}
