struct List_1 {
    struct String head;
    struct List_1* tail;
};

struct List_1* go_(struct List_1* acc_, struct List_1* xs_1) {
    struct List_1* match_;
    if (!(!(xs_1))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if (!(!(!(xs_1)))) goto next_3;
    struct String x_ = xs_1->head;
    struct List_1* xs_2 = xs_1->tail;
    struct List_1* list_ = (struct List_1*)malloc(sizeof(struct List_1));
    list_->head = x_;
    list_->tail = acc_;
    struct List_1* call_ = go_(list_, xs_2);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct List_1* listRev_(struct List_1* xs_) {
    struct List_1* call_1 = go_(NULL, xs_);
    return call_1;
}

int printList_(struct List_1* xs_3) {
    int match_1;
    if (!(!(xs_3))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(!(!(xs_3)))) goto next_6;
    struct String x_1 = xs_3->head;
    struct List_1* xs_4 = xs_3->tail;
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
    int if_;
    if (!(('0' <= c_))) goto else_7;
    if_ = (c_ <= '9');
    goto end_if_8;
else_7:;
    if_ = 0;
end_if_8:;
    return if_;
}

struct Tuple_2 {
    struct String t0;
};

int readInt_(struct Tuple_2 caps_1, int i_) {
    struct String s_ = caps_1.t0;
    int if_1;
    int if_2;
    if (!((s_.len <= i_))) goto else_11;
    if_2 = 1;
    goto end_if_12;
else_11:;
    int call_4 = isDigit_(s_.str[i_]);
    if_2 = !(call_4);
end_if_12:;
    if (!(if_2)) goto else_9;
    if_1 = i_;
    goto end_if_10;
else_9:;
    struct Tuple_2 caps_;
    caps_.t0 = s_;
    int call_5 = readInt_(caps_, (i_ + 1));
    if_1 = call_5;
end_if_10:;
    return if_1;
}

struct List_1* go_1(struct Tuple_2 caps_7, struct List_1* acc_1, int i_1) {
    struct String s_ = caps_7.t0;
    struct List_1* if_3;
    if (!((s_.len <= i_1))) goto else_13;
    struct List_1* call_6 = listRev_(acc_1);
    if_3 = call_6;
    goto end_if_14;
else_13:;
    struct List_1* if_4;
    if (!((s_.str[i_1] == ' '))) goto else_15;
    struct Tuple_2 caps_3;
    caps_3.t0 = s_;
    struct List_1* call_7 = go_1(caps_3, acc_1, (i_1 + 1));
    if_4 = call_7;
    goto end_if_16;
else_15:;
    struct List_1* if_5;
    int if_6;
    int if_7;
    if (!((s_.str[i_1] == '['))) goto else_21;
    if_7 = 1;
    goto end_if_22;
else_21:;
    if_7 = (s_.str[i_1] == ']');
end_if_22:;
    if (!(if_7)) goto else_19;
    if_6 = 1;
    goto end_if_20;
else_19:;
    if_6 = (s_.str[i_1] == ',');
end_if_20:;
    if (!(if_6)) goto else_17;
    struct String slice_ = str_slice(s_, i_1, i_1);
    struct List_1* list_1 = (struct List_1*)malloc(sizeof(struct List_1));
    list_1->head = str_add((struct String){.str = "punct ", .len = 6}, slice_);
    list_1->tail = acc_1;
    struct List_1* acc_2 = list_1;
    struct Tuple_2 caps_4;
    caps_4.t0 = s_;
    struct List_1* call_8 = go_1(caps_4, acc_2, (i_1 + 1));
    if_5 = call_8;
    goto end_if_18;
else_17:;
    struct List_1* if_8;
    int call_9 = isDigit_(s_.str[i_1]);
    if (!(call_9)) goto else_23;
    struct Tuple_2 caps_5;
    caps_5.t0 = s_;
    int call_10 = readInt_(caps_5, i_1);
    int r_ = call_10;
    struct String slice_1 = str_slice(s_, i_1, (r_ - 1));
    struct List_1* list_2 = (struct List_1*)malloc(sizeof(struct List_1));
    list_2->head = str_add((struct String){.str = "int ", .len = 4}, slice_1);
    list_2->tail = acc_1;
    struct List_1* acc_3 = list_2;
    struct Tuple_2 caps_6;
    caps_6.t0 = s_;
    struct List_1* call_11 = go_1(caps_6, acc_3, r_);
    if_8 = call_11;
    goto end_if_24;
else_23:;
    printf("ERROR: Unknown Token '%c'\n", s_.str[i_1]);
    int call_12 = 0;
    exit(1);
    if_8 = NULL;
end_if_24:;
    if_5 = if_8;
end_if_18:;
    if_4 = if_5;
end_if_16:;
    if_3 = if_4;
end_if_14:;
    return if_3;
}

struct List_1* tokenize_(struct String s_) {
    struct Tuple_2 caps_9;
    caps_9.t0 = s_;
    struct List_1* call_13 = go_1(caps_9, NULL, 0);
    return call_13;
}

int main() {
    struct String source_ = (struct String){.str = "[0, 1000000007, 314159]", .len = 23};
    struct List_1* call_14 = tokenize_(source_);
    struct List_1* tokens_ = call_14;
    int call_15 = printList_(tokens_);
    return 0;
}
