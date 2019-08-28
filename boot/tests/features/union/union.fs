type Ok =
  | Ok

type Status =
  | Ok
  | Err of string

type Limit =
  | LimitVal of int
  | LimitDiv

type ApiResponse =
  | ARJson
    of string
  | ARError
    of code:int * msg:string
  | ARCancel

type OkWrapper =
  | T
    of Ok // use another union types

let main _ =
  let () =
    let ok = Ok
    let err1 = Err "No such file or directory."
    let err2 = Err "Access denied."

    match err1 with
    | Ok ->
      exit 1
    | Err e ->
      if e <> "No such file or directory." then exit 2

  let () =
    match LimitVal 1 with
    | LimitVal x ->
      if x <> 1 then exit 1
    | LimitDiv ->
      exit 2

  let () =
    match ARCancel with
    | ARCancel ->
      ()
    | _ ->
      exit 1

  let () =
    match ARError (404, "Not Found") with
    | ARError (statusCode, statusText) ->
      if statusCode <> 404 || statusText <> "Not Found" then exit 1
    | _ ->
      exit 1

  // Type annotations should work.
  let ok: Status = Ok: Status

  // Variants can have the same name with others. Distinct by qualification.
  let okOk: Ok = Ok.Ok
  let statusOk: Status = Status.Ok

  match Status.Ok with
  | Status.Ok ->
    ()
  | Status.Err _ ->
    exit 1

  let okWrapper = OkWrapper.T Ok.Ok

  0