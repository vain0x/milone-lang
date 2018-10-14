int main() {
    int op_5 = (1 <= 2);
    int if_4;
    if (op_5) {
        int op_6 = (2 < 3);
        if_4 = op_6;
    } else {
        if_4 = 0;
    }
    int if_3;
    if (if_4) {
        if_3 = 1;
    } else {
        int op_8 = (3 > 2);
        int if_7;
        if (op_8) {
            int op_9 = (2 >= 1);
            if_7 = op_9;
        } else {
            if_7 = 0;
        }
        if_3 = if_7;
    }
    int if_2;
    if (if_3) {
        if_2 = 0;
    } else {
        if_2 = 1;
    }
    return if_2;
}
