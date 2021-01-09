#include "milone.h"

struct String str_of_raw_parts(char const*, int);

struct String strOfRawParts_(char const* p_, int len_);

int milone_main();

struct String strOfRawParts_(char const* p_, int len_) {
    struct String str_of_raw_parts_result_ = str_of_raw_parts(p_, len_);
    return str_of_raw_parts_result_;
}

int milone_main() {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void const* intBox_ = box_;
    (*(((int*)intBox_))) = 42;
    milone_assert(((*(((int const*)intBox_))) == 42), 10, 2);
    void const* box_1 = milone_mem_alloc(1, sizeof(uint64_t));
    (*(((uint64_t*)box_1))) = ((uint64_t)0);
    char* buf_ = ((char*)box_1);
    (*(buf_)) = 'H';
    buf_[1] = 'i';
    struct String call_ = strOfRawParts_(((char const*)buf_), 2);
    struct String s_ = call_;
    milone_assert((str_cmp(s_, (struct String){.str = "Hi", .len = 2}) == 0), 17, 2);
    return 0;
}
