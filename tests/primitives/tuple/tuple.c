#include <milone.h>

struct IntStringTuple2_;

struct StringIntTuple2_;

struct StringStringTuple2_;

struct StringStringTuple2StringTuple2_;

int main(int argc, char** argv);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct StringIntTuple2_ {
    struct String t0;
    int t1;
};

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

struct StringStringTuple2StringTuple2_ {
    struct StringStringTuple2_ t0;
    struct String t1;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "snd", .len = 3}};
    struct IntStringTuple2_ a_ = IntStringTuple2_;
    int x_ = a_.t0;
    struct String _x = a_.t1;
    printf("%d\n", x_);
    struct StringIntTuple2_ StringIntTuple2_ = (struct StringIntTuple2_){.t0 = (struct String){.str = "fst", .len = 3}, .t1 = 2};
    struct StringIntTuple2_ b_ = StringIntTuple2_;
    struct String y_ = b_.t0;
    int _y = b_.t1;
    printf("%s\n", str_to_c_str(y_));
    struct StringStringTuple2_ StringStringTuple2_ = (struct StringStringTuple2_){.t0 = (struct String){.str = "z", .len = 1}, .t1 = (struct String){.str = "w", .len = 1}};
    struct String z_ = StringStringTuple2_.t0;
    struct String w_ = StringStringTuple2_.t1;
    printf("z=%s\n", str_to_c_str(z_));
    printf("w=%s\n", str_to_c_str(w_));
    struct StringStringTuple2_ StringStringTuple2_1 = (struct StringStringTuple2_){.t0 = (struct String){.str = "p", .len = 1}, .t1 = (struct String){.str = "q", .len = 1}};
    struct StringStringTuple2StringTuple2_ StringStringTuple2StringTuple2_ = (struct StringStringTuple2StringTuple2_){.t0 = StringStringTuple2_1, .t1 = (struct String){.str = "r", .len = 1}};
    struct String p_ = StringStringTuple2StringTuple2_.t0.t0;
    struct String q_ = StringStringTuple2StringTuple2_.t0.t1;
    struct String r_ = StringStringTuple2StringTuple2_.t1;
    printf("p=%s\n", str_to_c_str(p_));
    return 0;
}
