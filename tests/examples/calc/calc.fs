module rec calc.Program

// Arithmetic expression evaluator.

type Token =
  | TkInt of int
  | TkOp of char

let charEqual (l: char) (r: char) = l = r

let strContains (c: char) (s: string) =
  let rec go i =
    i < s.Length && (s.[i] = c || go (i + 1))

  go 0

let strStartsWith (prefix: string) (s: string) =
  let rec go i =
    i >= prefix.Length
    || (s.[i] = prefix.[i] && go (i + 1))

  s.Length >= prefix.Length && go 0

let strConcat (xs: string list) =
  let rec go (xs: string list) =
    match xs with
    | [] -> ""
    | x :: xs -> x + go xs

  go xs

let strListRev (xs: string list) =
  let rec go acc (xs: string list) =
    match xs with
    | [] -> acc
    | x :: xs -> go (x :: acc) xs

  go [] xs

let tokenListRev (xs: Token list) =
  let rec go acc (xs: Token list) =
    match xs with
    | [] -> acc
    | x :: xs -> go (x :: acc) xs

  go [] xs

let isDigit c = '0' <= c && c <= '9'

let takeWhile (pred: char -> bool) (source: string, i) =
  let rec go r =
    if r < source.Length && pred source.[r] then
      go (r + 1)
    else
      r

  go i

let private readSpace (source: string) (acc: Token list, i) =
  assert (source.[i] = ' ')

  let r =
    takeWhile (charEqual ' ') (source, i + 1)

  acc, r

let private readEol (source: string) (acc: Token list, i) =
  assert (source.[i] = '\r' || source.[i] = '\n')

  let r =
    if i + 1 < source.Length
       && source.[i] = '\r'
       && source.[i + 1] = '\n' then
      i + 2
    else
      i + 1

  acc, r

let private readInt (source: string) (acc: Token list, i) =
  assert (isDigit source.[i])
  let r = takeWhile isDigit (source, i)
  let n = source.[i..r - 1] |> int
  TkInt n :: acc, r

let tokenize (source: string) : Token list =
  let at i =
    if i < source.Length then
      source.[i]
    else
      '\x00'

  let rec go (acc, i) =
    if i >= source.Length then
      acc |> tokenListRev
    else
      match source.[i] with
      | ' ' -> (acc, i) |> readSpace source |> go
      | '\r' -> (acc, i) |> readEol source |> go
      | '\n' -> (acc, i) |> readEol source |> go
      | c ->
          if isDigit c then
            (acc, i) |> readInt source |> go
          else
            (TkOp c :: acc, i + 1) |> go

  go ([], 0)

let rec tokenListPrint tokens =
  match tokens with
  | [] -> ()
  | TkInt n :: tokens ->
      printfn "int %d" n
      tokenListPrint tokens
  | TkOp c :: tokens ->
      printfn "op %c" c
      tokenListPrint tokens

let rec evalExpr tokens =
  let evalTerm tokens =
    match tokens with
    | TkInt n :: tokens -> n, tokens
    | TkOp '(' :: tokens ->
        match evalExpr tokens with
        | value, TkOp ')' :: tokens -> value, tokens
        | _ ->
            printfn "expected ')'"
            exit 1
    | _ ->
        printfn "expected an int"
        exit 1

  let evalMul tokens =
    let rec go acc tokens =
      match tokens with
      | TkOp '*' :: tokens ->
          let r, tokens = evalTerm tokens
          go (acc * r) tokens
      | _ -> acc, tokens

    let l, tokens = evalTerm tokens
    go l tokens

  let evalAdd tokens =
    let rec go acc tokens =
      match tokens with
      | TkOp '+' :: tokens ->
          let r, tokens = evalMul tokens
          go (acc + r) tokens
      | TkOp '-' :: tokens ->
          let r, tokens = evalMul tokens
          go (acc - r) tokens
      | _ -> acc, tokens

    let l, tokens = evalMul tokens
    go l tokens

  evalAdd tokens

let eval str =
  match str |> tokenize |> evalExpr with
  | value, [] -> value
  | _, tokens ->
      printfn "ERROR: couldn't parse tokens:"
      tokenListPrint tokens
      exit 1

let main _ =
  assert (strContains '+' "+-*/")
  assert (strStartsWith "hell" "hello")
  assert (strStartsWith "heaven" "hello" |> not)
  assert (strConcat [ "a"; ","; "b" ] = "a,b")
  assert ([ "a"; ","; "b" ] |> strListRev |> strConcat = "b,a")

  let source = "2 + 3\r\n    - 4"
  source |> tokenize |> tokenListPrint

  assert (eval source = 2 + 3 - 4)
  assert (eval "2 - 3 * 4 + 5" = 2 - 3 * 4 + 5)
  assert (eval "(2 - 3) * 4 + (1 + (2 + 2))" = (2 - 3) * 4 + (1 + (2 + 2)))

  0
