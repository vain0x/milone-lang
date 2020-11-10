module rec MiloneCore.Option

let isNone option =
  match option with
  | None -> true
  | Some _ -> false

let defaultValue alt option =
  match option with
  | Some x -> x
  | None -> alt

let map f option =
  match option with
  | Some x -> Some(f x)
  | None -> None

let forall pred option =
  match option with
  | Some x -> pred x
  | None -> true
