#include "milone.h"

struct StringList;

struct StringList* go_(struct StringList* acc_, struct StringList* xs_1);

struct StringList* listRev_(struct StringList* xs_);

int printList_(struct StringList* xs_3);

int isDigit_(char c_);

struct String strSlice_(int l_, int r_, struct String s_);

struct StringTuple1;

int readInt_(struct StringTuple1 arg_, int i_);

struct StringList* go_1(struct StringTuple1 arg_1, struct StringList* acc_1, int i_1);

struct StringList* tokenize_(struct String s_1);

int main();

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* go_(struct StringList* acc_, struct StringList* xs_1) {
    struct StringList* match_;
    if (!((!(xs_1)))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if (!((!((!(xs_1)))))) goto next_3;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = x_;
    list_->tail = acc_;
    struct StringList* call_ = go_(list_, xs_2);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct StringList* listRev_(struct StringList* xs_) {
    struct StringList* call_1 = go_(NULL, xs_);
    return call_1;
}

int printList_(struct StringList* xs_3) {
    int match_1;
    if (!((!(xs_3)))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!((!((!(xs_3)))))) goto next_6;
    struct String x_1 = xs_3->head;
    struct StringList* xs_4 = xs_3->tail;
    printf("%s\n", x_1.str);
    int call_2 = 0;
    int call_3 = printList_(xs_4);
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}

int isDigit_(char c_) {
    int match_2;
    if (!((('0' <= c_) == 1))) goto next_8;
    match_2 = (c_ <= '9');
    goto end_match_7;
next_8:;
    if (!((('0' <= c_) == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

struct String strSlice_(int l_, int r_, struct String s_) {
    struct String call_4 = str_substring(l_, (r_ - 1), s_);
    return call_4;
}

struct StringTuple1 {
    struct String t0;
};

int readInt_(struct StringTuple1 arg_, int i_) {
    struct String s_1 = arg_.t0;
    int match_3;
    int match_4;
    if (!(((s_1.len <= i_) == 1))) goto next_12;
    match_4 = 1;
    goto end_match_11;
next_12:;
    if (!(((s_1.len <= i_) == 0))) goto next_13;
    int call_5 = isDigit_(s_1.str[i_]);
    match_4 = (!(call_5));
    goto end_match_11;
next_13:;
    exit(1);
end_match_11:;
    if (!((match_4 == 1))) goto next_14;
    match_3 = i_;
    goto end_match_10;
next_14:;
    if (!((match_4 == 0))) goto next_15;
    struct StringTuple1 tuple_;
    tuple_.t0 = s_1;
    int call_6 = readInt_(tuple_, (i_ + 1));
    match_3 = call_6;
    goto end_match_10;
next_15:;
    exit(1);
end_match_10:;
    return match_3;
}

struct StringList* go_1(struct StringTuple1 arg_1, struct StringList* acc_1, int i_1) {
    struct String s_1 = arg_1.t0;
    struct StringList* match_5;
    if (!(((s_1.len <= i_1) == 1))) goto next_17;
    struct StringList* call_7 = listRev_(acc_1);
    match_5 = call_7;
    goto end_match_16;
next_17:;
    if (!(((s_1.len <= i_1) == 0))) goto next_18;
    struct StringList* match_6;
    if (!(((s_1.str[i_1] == ' ') == 1))) goto next_20;
    struct StringTuple1 tuple_1;
    tuple_1.t0 = s_1;
    struct StringList* call_8 = go_1(tuple_1, acc_1, (i_1 + 1));
    match_6 = call_8;
    goto end_match_19;
next_20:;
    if (!(((s_1.str[i_1] == ' ') == 0))) goto next_21;
    struct StringList* match_7;
    int match_8;
    int match_9;
    if (!(((s_1.str[i_1] == '[') == 1))) goto next_25;
    match_9 = 1;
    goto end_match_24;
next_25:;
    if (!(((s_1.str[i_1] == '[') == 0))) goto next_26;
    match_9 = (s_1.str[i_1] == ']');
    goto end_match_24;
next_26:;
    exit(1);
end_match_24:;
    if (!((match_9 == 1))) goto next_27;
    match_8 = 1;
    goto end_match_23;
next_27:;
    if (!((match_9 == 0))) goto next_28;
    match_8 = (s_1.str[i_1] == ',');
    goto end_match_23;
next_28:;
    exit(1);
end_match_23:;
    if (!((match_8 == 1))) goto next_29;
    struct String call_9 = strSlice_(i_1, (i_1 + 1), s_1);
    struct StringList* list_1 = (struct StringList*)malloc(sizeof(struct StringList));
    list_1->head = str_add((struct String){.str = "punct ", .len = 6}, call_9);
    list_1->tail = acc_1;
    struct StringList* acc_2 = list_1;
    struct StringTuple1 tuple_2;
    tuple_2.t0 = s_1;
    struct StringList* call_10 = go_1(tuple_2, acc_2, (i_1 + 1));
    match_7 = call_10;
    goto end_match_22;
next_29:;
    if (!((match_8 == 0))) goto next_30;
    struct StringList* match_10;
    int call_11 = isDigit_(s_1.str[i_1]);
    if (!((call_11 == 1))) goto next_32;
    struct StringTuple1 tuple_3;
    tuple_3.t0 = s_1;
    int call_12 = readInt_(tuple_3, i_1);
    int r_1 = call_12;
    struct String call_13 = strSlice_(i_1, r_1, s_1);
    struct StringList* list_2 = (struct StringList*)malloc(sizeof(struct StringList));
    list_2->head = str_add((struct String){.str = "int ", .len = 4}, call_13);
    list_2->tail = acc_1;
    struct StringList* acc_3 = list_2;
    struct StringTuple1 tuple_4;
    tuple_4.t0 = s_1;
    struct StringList* call_14 = go_1(tuple_4, acc_3, r_1);
    match_10 = call_14;
    goto end_match_31;
next_32:;
    if (!((call_11 == 0))) goto next_33;
    printf("ERROR: Unknown Token '%c'\n", s_1.str[i_1]);
    int call_15 = 0;
    exit(1);
    match_10 = NULL;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    match_7 = match_10;
    goto end_match_22;
next_30:;
    exit(1);
end_match_22:;
    match_6 = match_7;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    match_5 = match_6;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
}

struct StringList* tokenize_(struct String s_1) {
    struct StringTuple1 tuple_5;
    tuple_5.t0 = s_1;
    struct StringList* call_16 = go_1(tuple_5, NULL, 0);
    return call_16;
}

int main() {
    struct String source_ = (struct String){.str = "[0, 1000000007, 314159]", .len = 23};
    struct StringList* call_17 = tokenize_(source_);
    struct StringList* tokens_ = call_17;
    int call_18 = printList_(tokens_);
    return 0;
}
