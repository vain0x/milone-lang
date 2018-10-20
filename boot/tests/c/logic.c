int main() {
    int if_3;
    int if_4;
    int if_5;
    int op_6 = (1 <= 2);
    if (op_6) {
        int op_7 = (2 < 3);
        if_5 = op_7;
    } else {
        if_5 = 0;
    }
    if (if_5) {
        if_4 = 1;
    } else {
        int if_8;
        int op_9 = (3 > 2);
        if (op_9) {
            int op_10 = (2 >= 1);
            if_8 = op_10;
        } else {
            if_8 = 0;
        }
        if_4 = if_8;
    }
    if (if_4) {
        if_3 = 0;
    } else {
        if_3 = 1;
    }
    return if_3;
}
