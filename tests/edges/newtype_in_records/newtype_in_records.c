#include "milone.h"

void* newDay_(int value_);

int dayToInt_(void* arg_);

struct ObjectObjectTuple2;

void* newDayRange_(void* start_, void* endDay_);

int between_(void* day_, void* range_);

int main();

void* newDay_(int value_) {
    int match_;
    if ((value_ < 1)) goto next_2;
    match_ = (31 >= value_);
    goto end_match_1;
next_2:;
    if ((value_ >= 1)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    milone_assert(match_, 10, 2);
    int call_ = 0;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = value_;
    return box_;
}

int dayToInt_(void* arg_) {
    int value_1 = (*(((int*)arg_)));
    return value_1;
}

struct ObjectObjectTuple2 {
    void* t0;
    void* t1;
};

void* newDayRange_(void* start_, void* endDay_) {
    int call_1 = dayToInt_(endDay_);
    int call_2 = dayToInt_(start_);
    milone_assert((call_1 >= call_2), 16, 2);
    int call_3 = 0;
    struct ObjectObjectTuple2 tuple_;
    tuple_.t0 = start_;
    tuple_.t1 = endDay_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct ObjectObjectTuple2));
    (*(((struct ObjectObjectTuple2*)box_1))) = tuple_;
    return box_1;
}

int between_(void* day_, void* range_) {
    int match_1;
    int call_4 = dayToInt_(day_);
    int call_5 = dayToInt_((*(((struct ObjectObjectTuple2*)range_))).t0);
    if ((call_4 < call_5)) goto next_5;
    int call_6 = dayToInt_((*(((struct ObjectObjectTuple2*)range_))).t1);
    int call_7 = dayToInt_(day_);
    match_1 = (call_6 >= call_7);
    goto end_match_4;
next_5:;
    if ((call_4 >= call_5)) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

int main() {
    void* call_8 = newDay_(13);
    void* call_9 = newDay_(10);
    void* call_10 = newDay_(20);
    void* call_11 = newDayRange_(call_9, call_10);
    int call_12 = between_(call_8, call_11);
    milone_assert(call_12, 25, 2);
    int call_13 = 0;
    return 0;
}
