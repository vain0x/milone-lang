struct List_1 {
    struct String head;
    struct List_1* tail;
};

struct List_1* go_3(struct List_1* acc_4, struct List_1* xs_5) {
    struct List_1* match_28;
    if (!(!(xs_5))) goto next_2;
    match_28 = acc_4;
    goto end_match_1;
next_2:;
    if (!(!(!(xs_5)))) goto next_3;
    struct String x_6 = xs_5->head;
    struct List_1* xs_7 = xs_5->tail;
    struct List_1* list_29 = (struct List_1*)malloc(sizeof(struct List_1));
    list_29->head = x_6;
    list_29->tail = acc_4;
    struct List_1* call_30 = go_3(list_29, xs_7);
    match_28 = call_30;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_28;
}

struct List_1* listRev_1(struct List_1* xs_2) {
    struct List_1* call_31 = go_3(NULL, xs_2);
    return call_31;
}

int printList_8(struct List_1* xs_9) {
    int match_32;
    if (!(!(xs_9))) goto next_5;
    match_32 = 0;
    goto end_match_4;
next_5:;
    if (!(!(!(xs_9)))) goto next_6;
    struct String x_10 = xs_9->head;
    struct List_1* xs_11 = xs_9->tail;
    printf("%s\n", x_10.str);
    int call_33 = 0;
    int call_34 = printList_8(xs_11);
    match_32 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}

int isDigit_12(char c_13) {
    int if_35;
    if (!(('0' <= c_13))) goto else_7;
    if_35 = (c_13 <= '9');
    goto end_if_8;
else_7:;
    if_35 = 0;
end_if_8:;
    return if_35;
}

struct Tuple_2 {
    struct String t0;
};

int readInt_16(struct Tuple_2 caps_61, int i_17) {
    struct String s_15 = caps_61.t0;
    int if_36;
    int if_37;
    if (!((s_15.len <= i_17))) goto else_11;
    if_37 = 1;
    goto end_if_12;
else_11:;
    int call_38 = isDigit_12(s_15.str[i_17]);
    if_37 = !(call_38);
end_if_12:;
    if (!(if_37)) goto else_9;
    if_36 = i_17;
    goto end_if_10;
else_9:;
    struct Tuple_2 caps_60;
    caps_60.t0 = s_15;
    int call_39 = readInt_16(caps_60, (i_17 + 1));
    if_36 = call_39;
end_if_10:;
    return if_36;
}

struct List_1* go_18(struct Tuple_2 caps_67, struct List_1* acc_19, int i_20) {
    struct String s_15 = caps_67.t0;
    struct List_1* if_40;
    if (!((s_15.len <= i_20))) goto else_13;
    struct List_1* call_41 = listRev_1(acc_19);
    if_40 = call_41;
    goto end_if_14;
else_13:;
    struct List_1* if_42;
    if (!((s_15.str[i_20] == ' '))) goto else_15;
    struct Tuple_2 caps_63;
    caps_63.t0 = s_15;
    struct List_1* call_43 = go_18(caps_63, acc_19, (i_20 + 1));
    if_42 = call_43;
    goto end_if_16;
else_15:;
    struct List_1* if_44;
    int if_45;
    int if_46;
    if (!((s_15.str[i_20] == '['))) goto else_21;
    if_46 = 1;
    goto end_if_22;
else_21:;
    if_46 = (s_15.str[i_20] == ']');
end_if_22:;
    if (!(if_46)) goto else_19;
    if_45 = 1;
    goto end_if_20;
else_19:;
    if_45 = (s_15.str[i_20] == ',');
end_if_20:;
    if (!(if_45)) goto else_17;
    struct String slice_48 = str_slice(s_15, i_20, i_20);
    struct List_1* list_47 = (struct List_1*)malloc(sizeof(struct List_1));
    list_47->head = str_add((struct String){.str = "punct ", .len = 6}, slice_48);
    list_47->tail = acc_19;
    struct List_1* acc_21 = list_47;
    struct Tuple_2 caps_64;
    caps_64.t0 = s_15;
    struct List_1* call_49 = go_18(caps_64, acc_21, (i_20 + 1));
    if_44 = call_49;
    goto end_if_18;
else_17:;
    struct List_1* if_50;
    int call_51 = isDigit_12(s_15.str[i_20]);
    if (!(call_51)) goto else_23;
    struct Tuple_2 caps_65;
    caps_65.t0 = s_15;
    int call_52 = readInt_16(caps_65, i_20);
    int r_22 = call_52;
    struct String slice_54 = str_slice(s_15, i_20, (r_22 - 1));
    struct List_1* list_53 = (struct List_1*)malloc(sizeof(struct List_1));
    list_53->head = str_add((struct String){.str = "int ", .len = 4}, slice_54);
    list_53->tail = acc_19;
    struct List_1* acc_23 = list_53;
    struct Tuple_2 caps_66;
    caps_66.t0 = s_15;
    struct List_1* call_55 = go_18(caps_66, acc_23, r_22);
    if_50 = call_55;
    goto end_if_24;
else_23:;
    printf("ERROR: Unknown Token '%c'\n", s_15.str[i_20]);
    int call_56 = 0;
    exit(1);
    if_50 = NULL;
end_if_24:;
    if_44 = if_50;
end_if_18:;
    if_42 = if_44;
end_if_16:;
    if_40 = if_42;
end_if_14:;
    return if_40;
}

struct List_1* tokenize_14(struct String s_15) {
    struct Tuple_2 caps_69;
    caps_69.t0 = s_15;
    struct List_1* call_57 = go_18(caps_69, NULL, 0);
    return call_57;
}

int main() {
    struct String source_26 = (struct String){.str = "[0, 1000000007, 314159]", .len = 23};
    struct List_1* call_58 = tokenize_14(source_26);
    struct List_1* tokens_27 = call_58;
    int call_59 = printList_8(tokens_27);
    return 0;
}
