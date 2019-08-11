struct UnitUnitFun1;

struct IntIntTuple2;

struct IntIntTuple2IntTuple2;

int main();

struct UnitUnitFun1 {
    int(*fun)(void*, int);
    void* env;
};

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
    if (!((0 == 1))) goto next_2;
    exit(1);
    int app_ = ((struct UnitUnitFun1){}).fun(((struct UnitUnitFun1){}).env, 0);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!((0 == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_1;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    struct IntIntTuple2IntTuple2 tuple_;
    tuple_.t0 = tuple_1;
    tuple_.t1 = 3;
    if (!((tuple_.t0.t0 == 1))) goto next_5;
    if (!((str_cmp(tuple_.t0.t1, (struct String){.str = "type error", .len = 10}) == 0))) goto next_5;
    if (!((tuple_.t1 == 3))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    exit(1);
end_match_4:;
    int deepUnificationError_ = 0;
    exit(1);
    return 0;
}

#line 3
#error 3:5 Undefined variable f

#line 7
#error 7:7 While unifying 'Con (Tuple,[Con (Tuple,[Con (Int,[]); Con (Int,[])]); Con (Int,[])])' and 'Con (Tuple,[Con (Tuple,[Con (Int,[]); Con (Str,[])]); Con (Int,[])])', failed to unify 'Con (Int,[])' and 'Con (Str,[])'.

#line 10
#error 10:6 Type: Index not supported

#line 13
#error 13:17 Couldn't unify 'Meta 42' and 'Con (Fun,[Con (Fun,[Meta 42; Meta 40]); Meta 40])' due to self recursion.

#line 15
#error 15:3 While unifying 'Con (Int,[])' and 'Con (Tuple,[])', failed to unify 'Con (Int,[])' and 'Con (Tuple,[])'.
