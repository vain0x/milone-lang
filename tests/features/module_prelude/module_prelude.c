#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

bool MiloneCore_Prelude_BoolBoolFun1_id(bool );

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t );

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    bool call_;
    int32_t call_1;
    call_ = MiloneCore_Prelude_BoolBoolFun1_id(true);
    milone_assert(call_, (struct String){.ptr = "module_prelude/module_prelude.milone", .len = 36}, 6, 2);
    call_1 = MiloneCore_Prelude_Int32Int32Fun1_id(42);
    milone_assert((call_1 == 42), (struct String){.ptr = "module_prelude/module_prelude.milone", .len = 36}, 7, 2);
    return 0;
}
