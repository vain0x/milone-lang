int main() {
    int l0;
    if (1) {
        printf("then\n");
        char* hello_2 = "hello";
        int l1;
        if (1) {
            l1 = 0;
        } else {
            char* message_3 = hello_2;
            l1 = 1;
        }
        l0 = l1;
    } else {
        printf("else\n");
        l0 = 1;
    }
    return l0;
}
