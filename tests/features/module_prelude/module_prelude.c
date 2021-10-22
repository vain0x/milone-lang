#include "milone.h"

bool MiloneCore_Prelude_BoolBoolFun1_id(bool );

int MiloneCore_Prelude_IntIntFun1_id(int );

int milone_main(void);

int milone_main(void) {
    bool call_ = MiloneCore_Prelude_BoolBoolFun1_id(true);
    milone_assert(call_, 6, 2);
    int call_1 = MiloneCore_Prelude_IntIntFun1_id(42);
    milone_assert((call_1 == 42), 7, 2);
    return 0;
}
