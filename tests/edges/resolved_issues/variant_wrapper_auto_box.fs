// Fixed.

// When value-carrying variant is used as a function,
// due to interaction with auto boxing,
// invalid code was generated.

type private BoxedVariant = A of BoxedVariant option

let private feedNil (f: BoxedVariant option -> BoxedVariant) : BoxedVariant = f None

let private test () =
  // Variant is here converted to a function object.
  // Auto boxing phase doesn't insert `box` for the object unfortunately.
  // Generated code is illegal.
  let result = feedNil A
  ()

test ()
