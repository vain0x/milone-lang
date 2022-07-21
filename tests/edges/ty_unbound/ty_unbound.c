#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct UnitCons;

bool MiloneCore_List_UnitListBoolFun1_isEmpty(struct UnitCons const *);

void ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(struct UnitCons const *xs_);

int main(int argc, char **argv);

void ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(struct UnitCons const *xs_) {
    bool call_;
    call_ = MiloneCore_List_UnitListBoolFun1_isEmpty(xs_);
    if ((!(call_))) milone_assert_error("ty_unbound/ty_unbound.milone", 4, 23);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    ty_unbound_ty_unbound_UnitListUnitFun1_assertIsEmpty(NULL);
    return 0;
}
