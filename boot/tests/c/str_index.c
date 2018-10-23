int main() {
    char* hello_2 = "hello";
    int if_4;
    int if_5;
    if ((hello_2[0] == 104)) {
        if_5 = (hello_2[4] == 111);
    } else {
        if_5 = 0;
    }
    if (if_5) {
        if_4 = 0;
    } else {
        if_4 = 1;
    }
    return if_4;
}
