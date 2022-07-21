module rec MiloneCore.Option

type option<'T> =
  | None
  | Some of 'T

let isNone opt =
  match opt with
  | None -> true
  | Some _ -> false

let isSome opt =
  match opt with
  | None -> false
  | Some _ -> true

let defaultValue alt opt =
  match opt with
  | Some x -> x
  | None -> alt

let defaultWith alt opt =
  match opt with
  | Some x -> x
  | None -> alt ()

let map f opt =
  match opt with
  | Some x -> Some(f x)
  | None -> None

let bind f opt =
  match opt with
  | Some x -> f x
  | None -> None

let fold folder state opt =
  match opt with
  | Some x -> folder state x
  | None -> state

let forall pred opt =
  match opt with
  | Some x -> pred x
  | None -> true

let exists pred opt =
  match opt with
  | Some x -> pred x
  | None -> false
