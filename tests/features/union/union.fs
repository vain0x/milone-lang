module rec union.Program

// Discriminated union types.

type Ok = | Ok

type Status =
  | Ok
  | Err of string

type Limit =
  | LimitVal of int
  | LimitDiv

type ApiResponse =
  | ARJson of string
  | ARError of code: int * msg: string
  | ARCancel

type OkWrapper = T of Ok // use another union types

let main _ =
  let () =
    let ok = Ok
    let err1 = Err "No such file or directory."
    let err2 = Err "Access denied."

    match err1 with
    | Ok -> assert false
    | Err e -> assert (e = "No such file or directory.")

  let () =
    match LimitVal 1 with
    | LimitVal x -> assert (x = 1)
    | LimitDiv -> exit 2

  let () =
    match ARCancel with
    | ARCancel -> ()
    | _ -> assert false

  let () =
    match ARError(404, "Not Found") with
    | ARError (statusCode, statusText) -> assert (statusCode = 404 && statusText = "Not Found")
    | _ -> assert false

  // Type ascriptions should work.
  let ok: Status = Ok: Status

  // Variants can have the same name with others. Distinct by qualification.
  let okOk: Ok = Ok.Ok
  let statusOk: Status = Status.Ok

  match Status.Ok with
  | Status.Ok -> ()
  | Status.Err _ -> assert false

  let okWrapper = OkWrapper.T Ok.Ok

  0
