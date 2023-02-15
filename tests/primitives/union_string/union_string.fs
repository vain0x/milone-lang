module rec union_string.Program

type private MyUnion =
  | UnitLike
  | CarryingInt of label: int
  | CarryingOther of OtherUnion

type private OtherUnion = private | OtherUnion

let main _ =
  assert (string UnitLike = "MyUnion.UnitLike")
  assert (string (CarryingInt 1) = "MyUnion.CarryingInt(1)")

  // #erase_enum_like unfortunately changes semantics
  assert (string (CarryingOther OtherUnion) = "MyUnion.CarryingOther(0)")
  0
