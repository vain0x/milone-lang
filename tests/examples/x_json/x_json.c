#include "milone.h"

struct StringList;

struct StringList;

struct StringList const* go_(struct StringList const* acc_, struct StringList const* xs_1);

struct StringList const* listRev_(struct StringList const* xs_);

char printList_(struct StringList const* xs_3);

bool isDigit_(char c_);

int readInt_(struct String s_, int i_);

struct StringList const* go_1(struct String s_, struct StringList const* acc_1, int i_1);

struct StringList const* tokenize_(struct String s_);

int milone_main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct StringList const* go_(struct StringList const* acc_, struct StringList const* xs_1) {
tailrec_1:;
    struct StringList const* match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    struct String x_ = xs_1->head;
    struct StringList const* xs_2 = xs_1->tail;
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = (struct StringList){.head = x_, .tail = acc_};
    struct StringList const* arg_ = list_;
    struct StringList const* arg_1 = xs_2;
    acc_ = arg_;
    xs_1 = arg_1;
    goto tailrec_1;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct StringList const* listRev_(struct StringList const* xs_) {
    struct StringList const* call_ = go_(NULL, xs_);
    return call_;
}

char printList_(struct StringList const* xs_3) {
tailrec_5:;
    char match_1;
    if ((!((!(xs_3))))) goto next_7;
    match_1 = 0;
    goto end_match_6;
next_7:;
    if ((!(xs_3))) goto next_8;
    struct String x_1 = xs_3->head;
    struct StringList const* xs_4 = xs_3->tail;
    printf("%s\n", str_to_c_str(x_1));
    struct StringList const* arg_2 = xs_4;
    xs_3 = arg_2;
    goto tailrec_5;
next_8:;
    exit(1);
end_match_6:;
    return 0;
}

bool isDigit_(char c_) {
    bool if_;
    if ((c_ >= '0')) {
        goto then_10;
    } else {
        goto else_11;
    }
then_10:;
    if_ = ('9' >= c_);
    goto if_next_9;
else_11:;
    if_ = false;
    goto if_next_9;
if_next_9:;
    return if_;
}

int readInt_(struct String s_, int i_) {
tailrec_12:;
    bool if_1;
    if ((i_ >= s_.len)) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_1 = true;
    goto if_next_13;
else_15:;
    bool call_1 = isDigit_(s_.str[i_]);
    if_1 = (!(call_1));
    goto if_next_13;
if_next_13:;
    int if_2;
    if (if_1) {
        goto then_17;
    } else {
        goto else_18;
    }
then_17:;
    if_2 = i_;
    goto if_next_16;
else_18:;
    struct String arg_3 = s_;
    int arg_4 = (i_ + 1);
    s_ = arg_3;
    i_ = arg_4;
    goto tailrec_12;
if_next_16:;
    return if_2;
}

struct StringList const* go_1(struct String s_, struct StringList const* acc_1, int i_1) {
tailrec_19:;
    struct StringList const* if_3;
    if ((i_1 >= s_.len)) {
        goto then_21;
    } else {
        goto else_22;
    }
then_21:;
    struct StringList const* call_2 = listRev_(acc_1);
    if_3 = call_2;
    goto if_next_20;
else_22:;
    struct StringList const* if_4;
    if ((s_.str[i_1] == ' ')) {
        goto then_24;
    } else {
        goto else_25;
    }
then_24:;
    struct String arg_5 = s_;
    struct StringList const* arg_6 = acc_1;
    int arg_7 = (i_1 + 1);
    s_ = arg_5;
    acc_1 = arg_6;
    i_1 = arg_7;
    goto tailrec_19;
else_25:;
    bool if_5;
    if ((s_.str[i_1] == '[')) {
        goto then_27;
    } else {
        goto else_28;
    }
then_27:;
    if_5 = true;
    goto if_next_26;
else_28:;
    if_5 = (s_.str[i_1] == ']');
    goto if_next_26;
if_next_26:;
    bool if_6;
    if (if_5) {
        goto then_30;
    } else {
        goto else_31;
    }
then_30:;
    if_6 = true;
    goto if_next_29;
else_31:;
    if_6 = (s_.str[i_1] == ',');
    goto if_next_29;
if_next_29:;
    struct StringList const* if_7;
    if (if_6) {
        goto then_33;
    } else {
        goto else_34;
    }
then_33:;
    struct String slice_ = str_get_slice(i_1, i_1, s_);
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = str_add((struct String){.str = "punct ", .len = 6}, slice_), .tail = acc_1};
    struct StringList const* acc_2 = list_1;
    struct String arg_8 = s_;
    struct StringList const* arg_9 = acc_2;
    int arg_10 = (i_1 + 1);
    s_ = arg_8;
    acc_1 = arg_9;
    i_1 = arg_10;
    goto tailrec_19;
else_34:;
    bool call_3 = isDigit_(s_.str[i_1]);
    struct StringList const* if_8;
    if (call_3) {
        goto then_36;
    } else {
        goto else_37;
    }
then_36:;
    int call_4 = readInt_(s_, i_1);
    int r_ = call_4;
    struct String slice_1 = str_get_slice(i_1, (r_ - 1), s_);
    struct StringList const* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_2))) = (struct StringList){.head = str_add((struct String){.str = "int ", .len = 4}, slice_1), .tail = acc_1};
    struct StringList const* acc_3 = list_2;
    struct String arg_11 = s_;
    struct StringList const* arg_12 = acc_3;
    int arg_13 = r_;
    s_ = arg_11;
    acc_1 = arg_12;
    i_1 = arg_13;
    goto tailrec_19;
else_37:;
    printf("ERROR: Unknown Token \'%c\'\n", s_.str[i_1]);
    exit(1);
if_next_35:;
    if_7 = if_8;
    goto if_next_32;
if_next_32:;
    if_4 = if_7;
    goto if_next_23;
if_next_23:;
    if_3 = if_4;
    goto if_next_20;
if_next_20:;
    return if_3;
}

struct StringList const* tokenize_(struct String s_) {
    struct StringList const* call_5 = go_1(s_, NULL, 0);
    return call_5;
}

int milone_main() {
    struct String source_ = (struct String){.str = "[0, 1000000007, 314159]", .len = 23};
    struct StringList const* call_6 = tokenize_(source_);
    struct StringList const* tokens_ = call_6;
    char call_7 = printList_(tokens_);
    return 0;
}
