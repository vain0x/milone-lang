int main() {
    char* hello_2 = "hello";
    int if_4;
    int if_5;
    if (!((hello_2[0] == 104))) goto else_3;
    if_5 = (hello_2[4] == 111);
    goto end_if_4;
else_3:;
    if_5 = 0;
end_if_4:;
    if (!(if_5)) goto else_1;
    if_4 = 0;
    goto end_if_2;
else_1:;
    if_4 = 1;
end_if_2:;
    return if_4;
}
