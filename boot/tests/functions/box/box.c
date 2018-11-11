int printIntOrStr_2(int isInt_3, void* value_4) {
    int if_6;
    if (!(isInt_3)) goto else_1;
    printf("%d\n", *(((int*)value_4)));
    int call_7 = 0;
    if_6 = 0;
    goto end_if_2;
else_1:;
    printf("%s\n", *(((struct String*)value_4)).str);
    int call_8 = 0;
    if_6 = 0;
end_if_2:;
    return 0;
}

int main() {
    void* box_9 = (void*)malloc(sizeof(int));
    *(((int*)box_9)) = 2;
    int call_10 = printIntOrStr_2(1, box_9);
    void* box_11 = (void*)malloc(sizeof(struct String));
    *(((struct String*)box_11)) = (struct String){.str = "Fizz", .len = 4};
    int call_12 = printIntOrStr_2(0, box_11);
    return 0;
}
