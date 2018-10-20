int main() {
    int if_5;
    if (1) {
        printf("then\n");
        int call_6 = 0;
        char* hello_2 = "hello";
        int if_7;
        if (1) {
            if_7 = 0;
        } else {
            char* message_3 = hello_2;
            if_7 = 1;
        }
        if_5 = if_7;
    } else {
        printf("else\n");
        int call_8 = 0;
        if_5 = 1;
    }
    return if_5;
}
