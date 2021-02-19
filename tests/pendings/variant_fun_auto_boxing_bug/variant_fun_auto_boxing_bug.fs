module rec variant_fun_auto_boxing_bug.Program

type BoxedVariant = A of BoxedVariant option

let feedNil (f: BoxedVariant option -> BoxedVariant): BoxedVariant = f None

let main _ =
  // Variant is here converted to a function object.
  // Auto boxing phase doesn't insert `box` for the object unfortunately.
  // Generated code is illegal.
  // let result = feedNil A
  0
