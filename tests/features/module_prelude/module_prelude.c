#include <milone.h>

bool MiloneCore_Prelude_BoolBoolFun1_id(bool );

int MiloneCore_Prelude_IntIntFun1_id(int );

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    bool call_ = MiloneCore_Prelude_BoolBoolFun1_id(true);
    milone_assert(call_, (struct String){.str = "module_prelude/module_prelude.milone", .len = 36}, 6, 2);
    int call_1 = MiloneCore_Prelude_IntIntFun1_id(42);
    milone_assert((call_1 == 42), (struct String){.str = "module_prelude/module_prelude.milone", .len = 36}, 7, 2);
    return 0;
}
