#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct DayRange_;

int newtype_in_records_newtype_in_records_newDay(int value_);

int newtype_in_records_newtype_in_records_dayToInt(int value_1);

struct DayRange_ newtype_in_records_newtype_in_records_newDayRange(int start_, int endDay_);

bool newtype_in_records_newtype_in_records_between(int day_, struct DayRange_ range_);

int main(int argc, char** argv);

struct DayRange_ {
    int t0;
    int t1;
};

int newtype_in_records_newtype_in_records_newDay(int value_) {
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
    milone_assert(if_, (struct String){.ptr = "newtype_in_records/newtype_in_records.milone", .len = 44}, 10, 2);
    return value_;
}

int newtype_in_records_newtype_in_records_dayToInt(int value_1) {
    return value_1;
}

struct DayRange_ newtype_in_records_newtype_in_records_newDayRange(int start_, int endDay_) {
    int call_;
    int call_1;
    struct DayRange_ DayRange_;
    call_ = newtype_in_records_newtype_in_records_dayToInt(endDay_);
    call_1 = newtype_in_records_newtype_in_records_dayToInt(start_);
    milone_assert((call_ >= call_1), (struct String){.ptr = "newtype_in_records/newtype_in_records.milone", .len = 44}, 16, 2);
    DayRange_ = (struct DayRange_){.t0 = start_, .t1 = endDay_};
    return DayRange_;
}

bool newtype_in_records_newtype_in_records_between(int day_, struct DayRange_ range_) {
    int call_2;
    int call_3;
    bool if_1;
    int call_4;
    int call_5;
    call_2 = newtype_in_records_newtype_in_records_dayToInt(day_);
    call_3 = newtype_in_records_newtype_in_records_dayToInt(range_.t0);
    if ((call_2 >= call_3)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    call_4 = newtype_in_records_newtype_in_records_dayToInt(range_.t1);
    call_5 = newtype_in_records_newtype_in_records_dayToInt(day_);
    if_1 = (call_4 >= call_5);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_6;
    int call_7;
    int call_8;
    struct DayRange_ call_9;
    bool call_10;
    call_6 = newtype_in_records_newtype_in_records_newDay(13);
    call_7 = newtype_in_records_newtype_in_records_newDay(10);
    call_8 = newtype_in_records_newtype_in_records_newDay(20);
    call_9 = newtype_in_records_newtype_in_records_newDayRange(call_7, call_8);
    call_10 = newtype_in_records_newtype_in_records_between(call_6, call_9);
    milone_assert(call_10, (struct String){.ptr = "newtype_in_records/newtype_in_records.milone", .len = 44}, 24, 2);
    return 0;
}
