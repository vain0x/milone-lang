int main() {
    int l0;
    if (1) {
        printf("then");
        printf("\n");
        char* hello = "hello";
        int l1;
        if (1) {
            l1 = 0;
        } else {
            char* message = hello;
            l1 = 1;
        }
        l0 = l1;
    } else {
        printf("else");
        printf("\n");
        l0 = 1;
    }
    return l0;
}
