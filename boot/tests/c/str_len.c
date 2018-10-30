int main() {
    char* hello_3 = "hello";
    char* world_4 = "world";
    int if_6;
    if (!((strlen(hello_3) != 5))) goto else_1;
    exit(1);
    if_6 = 0;
    goto end_if_2;
else_1:;
    if_6 = 0;
end_if_2:;
    char* message_5 = str_add(hello_3, world_4);
    int if_7;
    if (!((strlen(message_5) != 10))) goto else_3;
    exit(1);
    if_7 = 0;
    goto end_if_4;
else_3:;
    if_7 = 0;
end_if_4:;
    return 0;
}
