module rec never_ty.Program

// FIXME: some of tests failing

open Std.Own

let private blackBox = id
let private opaqueStmt () = ()

let private graceful () : unit =
  match blackBox 0 with
  | 0 -> exit 0
  | _ -> ()

// Function result type can be never.
let private crash () : never =
  opaqueStmt ()
  exit 1

// Expression statement can be never.
let private testStmt () =
  crash ()
  ()

// Let-init can be never.
let private testLetInit () =
  let nothing: int = crash ()
  nothing |> ignore

// Match arm can be never.
let private testMatchArm () =
  ((match blackBox 0 with
    | 0 -> crash ()
    | _ -> 1)
   + 1)
  |> ignore

// Function object with result type never can be created and called.
let private testFunObj () =
  let crashFn: unit -> never = crash
  let callFnObj () = crashFn ()
  callFnObj () |> ignore

// Never can be replaced with an owned type. (Unlike generic returning function.)
let private testOwn () =
  let resource = Own.acquire ()

  let resource =
    match blackBox 1 with
    | 1 ->
      Own.release resource
      crash ()

    | _ -> resource

  Own.release resource

// Infinite loop can be never type.
let private testInfiniteLoop () =
  let rec diverge () : never = diverge ()
  ()

// Never can be used as values.
let private testNeverAsValue () =
  let opt: never option = None

  // (match opt with
  //  | Some n -> n
  //  | None -> crash ())

  let ok: Result<int, never> = Ok 0

  // let value =
  //   match ok with
  //   | Ok it -> it
  //   | Error n -> n

  // assert (value = 0)

// Result type of main can be never.
let main _ : never =
  // This actually exists with 0.
  graceful ()

  testStmt ()
  testLetInit ()
  testMatchArm ()
  testFunObj ()
  testOwn ()
  testInfiniteLoop ()
  testNeverAsValue ()

  crash ()
