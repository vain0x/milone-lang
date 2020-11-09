module rec MiloneCore.List

let isEmpty (xs: _ list): bool =
  match xs with
  | [] -> true
  | _ -> false
