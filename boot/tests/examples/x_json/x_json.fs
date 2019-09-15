// Incomplete.

let listRev xs =
  let rec go acc (xs : string list) =
    match xs with
    | [] ->
      acc
    | x :: xs ->
      go (x :: acc) xs
  go [] xs

let rec printList xs =
  match xs with
  | [] ->
    ()
  | x :: xs ->
    printfn "%s" x
    printList xs

let isDigit c =
  '0' <= c && c <= '9'

let strSlice (l: int) (r: int) (s: string) =
  String.substring l (r - 1) s

let tokenize (s : string) =
  let rec readInt i =
    if i >= s.Length || not (isDigit s.[i]) then
      i
    else
      readInt (i + 1)

  let rec go acc i =
    if i >= s.Length then
      listRev acc
    else if s.[i] = ' ' then
      go acc (i + 1)
    else if s.[i] = '[' || s.[i] = ']' || s.[i] = ',' then
      let acc = "punct " + (s |> strSlice i (i + 1)) :: acc
      go acc (i + 1)
    else if isDigit s.[i] then
      let r = readInt i
      let acc = "int " + (s |> strSlice i r) :: acc
      go acc r
    else
      printfn "ERROR: Unknown Token '%c'" s.[i]
      exit 1
  go [] 0

let main _ =
  let source = "[0, 1000000007, 314159]"
  let tokens = tokenize source
  printList tokens
  0
