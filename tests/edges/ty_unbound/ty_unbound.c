#include "milone.h"

struct UnitList;

bool MiloneCore_List_UnitListBoolFun1_isEmpty(struct UnitList const* );

void ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(struct UnitList const* xs_);

int milone_main(void);

void ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(struct UnitList const* xs_) {
    bool call_ = MiloneCore_List_UnitListBoolFun1_isEmpty(xs_);
    milone_assert(call_, 4, 23);
    return;
}

int milone_main(void) {
    ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(NULL);
    return 0;
}
