#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

bool MiloneCore_Prelude_BoolBoolFun1_id(bool);

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t);

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    bool call_;
    int32_t call_1;
    call_ = MiloneCore_Prelude_BoolBoolFun1_id(true);
    if ((!(call_))) milone_assert_error("module_prelude/module_prelude.milone", 6, 2);
    call_1 = MiloneCore_Prelude_Int32Int32Fun1_id(42);
    if ((call_1 != 42)) milone_assert_error("module_prelude/module_prelude.milone", 7, 2);
    return 0;
}
