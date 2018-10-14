int main() {
    int if_4;
    if (1) {
        printf("then\n");
        char* hello_2 = "hello";
        int if_5;
        if (1) {
            if_5 = 0;
        } else {
            char* message_3 = hello_2;
            if_5 = 1;
        }
        if_4 = if_5;
    } else {
        printf("else\n");
        if_4 = 1;
    }
    return if_4;
}
