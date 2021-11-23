#include <milone.h>

struct UnitList;

bool MiloneCore_List_UnitListBoolFun1_isEmpty(struct UnitList const* );

void ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(struct UnitList const* xs_);

int main(int argc, char** argv);

void ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(struct UnitList const* xs_) {
    bool call_ = MiloneCore_List_UnitListBoolFun1_isEmpty(xs_);
    milone_assert(call_, (struct String){.str = "ty_unbound/ty_unbound.milone", .len = 28}, 4, 23);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(NULL);
    return 0;
}
