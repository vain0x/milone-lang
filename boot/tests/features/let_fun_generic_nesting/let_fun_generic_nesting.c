struct IntTuple1;

int aux_(struct IntTuple1 arg_, int arg_1);

int id_1(int x_);

int gooAux_(struct IntTuple1 arg_2, int arg_3);

int goo_1(int x_1);

int main();

struct IntTuple1 {
    int t0;
};

int aux_(struct IntTuple1 arg_, int arg_1) {
    int x_ = arg_.t0;
    return x_;
}

int id_1(int x_) {
    struct IntTuple1 tuple_;
    tuple_.t0 = x_;
    int call_ = aux_(tuple_, 0);
    return call_;
}

int gooAux_(struct IntTuple1 arg_2, int arg_3) {
    int x_1 = arg_2.t0;
    int call_3 = id_1(x_1);
    return call_3;
}

int goo_1(int x_1) {
    struct IntTuple1 tuple_1;
    tuple_1.t0 = x_1;
    int call_4 = gooAux_(tuple_1, 0);
    return call_4;
}

int main() {
    int call_1 = id_1(1);
    milone_assert((call_1 == 1));
    int call_2 = 0;
    int call_5 = goo_1(1);
    milone_assert((call_5 == 1));
    int call_6 = 0;
    return 0;
}
