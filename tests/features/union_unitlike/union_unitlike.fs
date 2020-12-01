module rec union_unitlike.Program

// Variant is *unit-like* if it's exactly-one variant and has no payload (`of` clause).

type MyUnit = | MyUnit

let basicCase () =
  // Creation.
  let myUnit = MyUnit

  // Consumption.
  match myUnit with
  | MyUnit -> ()

// Unit-like variant is used in other types.
type MyBool =
  | MyFalse of MyUnit
  | MyTrue of MyUnit

let usedInOtherSumTypeCase () =
  let myBool = MyTrue MyUnit

  let toBool myBool =
    match myBool with
    | MyFalse MyUnit -> false
    | MyTrue MyUnit -> true

  assert (toBool myBool)

// Unit-like variant in records.
type RecordUsingMyUnit = { First: MyUnit; Second: MyUnit list }

let usedInRecordTypeCase () =
  let record: RecordUsingMyUnit = { First = MyUnit; Second = [ MyUnit ] }

  match record.Second with
  | [ MyUnit ] -> ()
  | _ -> assert false

let main _ =
  basicCase ()
  usedInOtherSumTypeCase ()
  usedInRecordTypeCase ()
  0
