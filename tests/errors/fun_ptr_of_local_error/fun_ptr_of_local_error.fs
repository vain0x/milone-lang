module rec fun_ptr_of_local_error.Program

// Pointer to a local function is unavailable
// since local functions might capture local variables.

ignore (
  let inExprStmt () = ()
  &&inExprStmt
)

let _ =
  let inVal () = ()
  &&inVal

let _f () =
  let inFun () = ()
  &&inFun

let main _ = 1
