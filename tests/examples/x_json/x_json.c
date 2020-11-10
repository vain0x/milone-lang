#include "milone.h"

struct StringList;

struct StringList* go_(struct StringList* acc_, struct StringList* xs_1);

struct StringList* listRev_(struct StringList* xs_);

int printList_(struct StringList* xs_3);

int isDigit_(char c_);

int readInt_(struct String s_, int i_);

struct StringList* go_1(struct String s_, struct StringList* acc_1, int i_1);

struct StringList* tokenize_(struct String s_);

int main();

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* go_(struct StringList* acc_, struct StringList* xs_1) {
tailrec_1:;
    struct StringList* match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct StringList* list_ = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_->head = x_;
    list_->tail = acc_;
    struct StringList* arg_ = list_;
    struct StringList* arg_1 = xs_2;
    acc_ = arg_;
    xs_1 = arg_1;
    goto tailrec_1;
    match_ = NULL;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct StringList* listRev_(struct StringList* xs_) {
    struct StringList* call_ = go_(NULL, xs_);
    return call_;
}

int printList_(struct StringList* xs_3) {
tailrec_5:;
    int match_1;
    if ((!((!(xs_3))))) goto next_7;
    match_1 = 0;
    goto end_match_6;
next_7:;
    if ((!(xs_3))) goto next_8;
    struct String x_1 = xs_3->head;
    struct StringList* xs_4 = xs_3->tail;
    printf("%s\n", x_1.str);
    int call_1 = 0;
    struct StringList* arg_2 = xs_4;
    xs_3 = arg_2;
    goto tailrec_5;
    match_1 = 0;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    return 0;
}

int isDigit_(char c_) {
    int match_2;
    if ((c_ < '0')) goto next_10;
    match_2 = ('9' >= c_);
    goto end_match_9;
next_10:;
    if ((c_ >= '0')) goto next_11;
    match_2 = 0;
    goto end_match_9;
next_11:;
    exit(1);
end_match_9:;
    return match_2;
}

int readInt_(struct String s_, int i_) {
tailrec_12:;
    int match_3;
    int match_4;
    if ((i_ < s_.len)) goto next_15;
    match_4 = 1;
    goto end_match_14;
next_15:;
    if ((i_ >= s_.len)) goto next_16;
    int call_2 = isDigit_(s_.str[i_]);
    match_4 = (!(call_2));
    goto end_match_14;
next_16:;
    exit(1);
end_match_14:;
    if ((!(match_4))) goto next_17;
    match_3 = i_;
    goto end_match_13;
next_17:;
    if (match_4) goto next_18;
    struct String arg_3 = s_;
    int arg_4 = (i_ + 1);
    s_ = arg_3;
    i_ = arg_4;
    goto tailrec_12;
    match_3 = 0;
    goto end_match_13;
next_18:;
    exit(1);
end_match_13:;
    return match_3;
}

struct StringList* go_1(struct String s_, struct StringList* acc_1, int i_1) {
tailrec_19:;
    struct StringList* match_5;
    if ((i_1 < s_.len)) goto next_21;
    struct StringList* call_3 = listRev_(acc_1);
    match_5 = call_3;
    goto end_match_20;
next_21:;
    if ((i_1 >= s_.len)) goto next_22;
    struct StringList* match_6;
    if ((s_.str[i_1] != ' ')) goto next_24;
    struct String arg_5 = s_;
    struct StringList* arg_6 = acc_1;
    int arg_7 = (i_1 + 1);
    s_ = arg_5;
    acc_1 = arg_6;
    i_1 = arg_7;
    goto tailrec_19;
    match_6 = NULL;
    goto end_match_23;
next_24:;
    if ((s_.str[i_1] == ' ')) goto next_25;
    struct StringList* match_7;
    int match_8;
    int match_9;
    if ((s_.str[i_1] != '[')) goto next_29;
    match_9 = 1;
    goto end_match_28;
next_29:;
    if ((s_.str[i_1] == '[')) goto next_30;
    match_9 = (s_.str[i_1] == ']');
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    if ((!(match_9))) goto next_31;
    match_8 = 1;
    goto end_match_27;
next_31:;
    if (match_9) goto next_32;
    match_8 = (s_.str[i_1] == ',');
    goto end_match_27;
next_32:;
    exit(1);
end_match_27:;
    if ((!(match_8))) goto next_33;
    struct String call_4 = str_get_slice(i_1, i_1, s_);
    struct StringList* list_1 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_1->head = str_add((struct String){.str = "punct ", .len = 6}, call_4);
    list_1->tail = acc_1;
    struct StringList* acc_2 = list_1;
    struct String arg_8 = s_;
    struct StringList* arg_9 = acc_2;
    int arg_10 = (i_1 + 1);
    s_ = arg_8;
    acc_1 = arg_9;
    i_1 = arg_10;
    goto tailrec_19;
    match_7 = NULL;
    goto end_match_26;
next_33:;
    if (match_8) goto next_34;
    struct StringList* match_10;
    int call_5 = isDigit_(s_.str[i_1]);
    if ((!(call_5))) goto next_36;
    int call_6 = readInt_(s_, i_1);
    int r_ = call_6;
    struct String call_7 = str_get_slice(i_1, (r_ - 1), s_);
    struct StringList* list_2 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_2->head = str_add((struct String){.str = "int ", .len = 4}, call_7);
    list_2->tail = acc_1;
    struct StringList* acc_3 = list_2;
    struct String arg_11 = s_;
    struct StringList* arg_12 = acc_3;
    int arg_13 = r_;
    s_ = arg_11;
    acc_1 = arg_12;
    i_1 = arg_13;
    goto tailrec_19;
    match_10 = NULL;
    goto end_match_35;
next_36:;
    if (call_5) goto next_37;
    printf("ERROR: Unknown Token \'%c\'\n", s_.str[i_1]);
    int call_8 = 0;
    exit(1);
    match_10 = NULL;
    goto end_match_35;
next_37:;
    exit(1);
end_match_35:;
    match_7 = match_10;
    goto end_match_26;
next_34:;
    exit(1);
end_match_26:;
    match_6 = match_7;
    goto end_match_23;
next_25:;
    exit(1);
end_match_23:;
    match_5 = match_6;
    goto end_match_20;
next_22:;
    exit(1);
end_match_20:;
    return match_5;
}

struct StringList* tokenize_(struct String s_) {
    struct StringList* call_9 = go_1(s_, NULL, 0);
    return call_9;
}

int main() {
    struct String source_ = (struct String){.str = "[0, 1000000007, 314159]", .len = 23};
    struct StringList* call_10 = tokenize_(source_);
    struct StringList* tokens_ = call_10;
    int call_11 = printList_(tokens_);
    return 0;
}
