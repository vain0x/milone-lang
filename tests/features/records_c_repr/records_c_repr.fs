module rec records_c_repr.Program

// Repr(C) attribute on record type prevents from transforming
// such as AutoBoxing.

[<Repr("C")>]
type Int32X4 = { N1: int; N2: int; N3: int; N4: int }

let int32X4Zero: Int32X4 = { N1 = 0; N2 = 0; N3 = 0; N4 = 0 }

[<Repr("C")>]
type Int32X32 =
  { M1: Int32X4
    M2: Int32X4
    M3: Int32X4
    M4: Int32X4 }

let int32X32Zero: Int32X32 =
  { M1 = int32X4Zero
    M2 = int32X4Zero
    M3 = int32X4Zero
    M4 = int32X4Zero }

let main _ =
  assert (int32X32Zero.M1.N1 = 0)
  0
