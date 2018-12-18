struct IntIntTuple2;

struct IntIntTuple2IntTuple2;

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct IntIntTuple2IntTuple2 {
    struct IntIntTuple2 t0;
    int t1;
};

int main() {
    int match_;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    struct IntIntTuple2IntTuple2 tuple_;
    tuple_.t0 = tuple_1;
    tuple_.t1 = 3;
    if (!((tuple_.t0.t0 == 1))) goto next_2;
    if (!((str_cmp(tuple_.t0.t1, (struct String){.str = "type error", .len = 10}) == 0))) goto next_2;
    if (!((tuple_.t1 == 3))) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    exit(1);
end_match_1:;
    int deepUnificationError_ = 0;
    return 0;
}

#line 5
#error 5:7 While unifying 'Tuple [Tuple [Int; Int]; Int]' and 'Tuple [Tuple [Int; Str]; Int]', failed to unify 'Int' and 'Str'.

#line 7
#error 7:3 While unifying 'Int' and 'Tuple []', failed to unify 'Int' and 'Tuple []'.
