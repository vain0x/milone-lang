module rec scope_undefined_ty_err.Program

// Use of undefined type name is error.

let f (_: NotExistingTy) = ()

let main _ = 0
