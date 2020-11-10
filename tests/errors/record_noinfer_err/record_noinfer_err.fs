module rec record_noinfer_err.Program

// Without type ascription, record type cannot be inferred.

type IntWrapper = { Value: int }

let main _ =
  let _wrapper = { Value = 42 }
  //             ^ Record expr of unknown type.

  // Correct:
  //    let _wrapper: IntWrapper = { Value = 42 }
  0
