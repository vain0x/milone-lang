#include "milone.h"

struct DayRange_;

int newtype_in_records_Program_newDay(int value_);

int newtype_in_records_Program_dayToInt(int value_1);

struct DayRange_ newtype_in_records_Program_newDayRange(int start_, int endDay_);

bool newtype_in_records_Program_between(int day_, struct DayRange_ range_);

int milone_main(void);

struct DayRange_ {
    int t0;
    int t1;
};

int newtype_in_records_Program_newDay(int value_) {
    bool if_;
    if ((value_ >= 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (31 >= value_);
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 10, 2);
    return value_;
}

int newtype_in_records_Program_dayToInt(int value_1) {
    return value_1;
}

struct DayRange_ newtype_in_records_Program_newDayRange(int start_, int endDay_) {
    int call_ = newtype_in_records_Program_dayToInt(endDay_);
    int call_1 = newtype_in_records_Program_dayToInt(start_);
    milone_assert((call_ >= call_1), 16, 2);
    struct DayRange_ DayRange_ = (struct DayRange_){.t0 = start_, .t1 = endDay_};
    return DayRange_;
}

bool newtype_in_records_Program_between(int day_, struct DayRange_ range_) {
    int call_2 = newtype_in_records_Program_dayToInt(day_);
    int call_3 = newtype_in_records_Program_dayToInt(range_.t0);
    bool if_1;
    if ((call_2 >= call_3)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    int call_4 = newtype_in_records_Program_dayToInt(range_.t1);
    int call_5 = newtype_in_records_Program_dayToInt(day_);
    if_1 = (call_4 >= call_5);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int milone_main(void) {
    int call_6 = newtype_in_records_Program_newDay(13);
    int call_7 = newtype_in_records_Program_newDay(10);
    int call_8 = newtype_in_records_Program_newDay(20);
    struct DayRange_ call_9 = newtype_in_records_Program_newDayRange(call_7, call_8);
    bool call_10 = newtype_in_records_Program_between(call_6, call_9);
    milone_assert(call_10, 24, 2);
    return 0;
}
