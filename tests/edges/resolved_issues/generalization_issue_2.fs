// Fixed.

// Invalid C code was generated.
// The reason was unclear but seemed related to generalization of mutually recursive functions.

// ====

type private Tag = | Tag

// type Package<'T> = 'T * Tag

let private tag1 item = tag2 item

let private tag2 item = item, Tag

let private untag package =
  let item, (_: Tag) = package
  item

let private test () =
  let _ = untag (tag1 "anything")
  ()

test ()

// ============

// #include "milone.h"

// struct StringUnitTuple2_;

// struct UnitUnitTuple2_;

// struct StringUnitTuple2_ tag1_(struct String item_);

// struct StringUnitTuple2_ tag2_(struct String item_1);

// void untag_(struct UnitUnitTuple2_ package_);

// int milone_main(void);

// struct StringUnitTuple2_ {
//     struct String t0;
//     char t1;
// };

// struct UnitUnitTuple2_ {
//     char t0;
//     char t1;
// };

// struct StringUnitTuple2_ tag1_(struct String item_) {
//     struct StringUnitTuple2_ call_ = tag2_(item_);
//     return call_;
// }

// struct StringUnitTuple2_ tag2_(struct String item_1) {
//     struct StringUnitTuple2_ StringUnitTuple2_ = (struct StringUnitTuple2_){.t0 = item_1, .t1 = 0};
//     return StringUnitTuple2_;
// }

// void untag_(struct UnitUnitTuple2_ package_) {
//     char item_2 = package_.t0;
//     return;
// }

// int milone_main(void) {
//     struct UnitUnitTuple2_ call_1 = tag1_((struct String){.ptr = "anything", .len = 8});
//     untag_(call_1);
//     return 0;
// }
