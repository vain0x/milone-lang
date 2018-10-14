int main() {
    int l3 = (1 <= 2);
    int l2;
    if (l3) {
        int l4 = (2 < 3);
        l2 = l4;
    } else {
        l2 = 0;
    }
    int l1;
    if (l2) {
        l1 = 1;
    } else {
        int l6 = (3 > 2);
        int l5;
        if (l6) {
            int l7 = (2 >= 1);
            l5 = l7;
        } else {
            l5 = 0;
        }
        l1 = l5;
    }
    int l0;
    if (l1) {
        l0 = 0;
    } else {
        l0 = 1;
    }
    return l0;
}
