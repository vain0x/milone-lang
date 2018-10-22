int add_2(Box arg_6) {
    int x_3 = arg_6.t[0].i;
    int y_4 = arg_6.t[1].i;
    return (x_3 + y_4);
}

int main() {
    Box tuple_7 = {.t = malloc(2 * sizeof(Box))};
    tuple_7.t[0] = (Box){.i = 2};
    tuple_7.t[1] = (Box){.i = 3};
    int call_8 = add_2(tuple_7);
    return (call_8 - 5);
}
