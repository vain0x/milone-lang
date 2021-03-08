module rec MiloneLang.UtilStrictYaml

let private stateMap f (x, s) = f x, s

let private pairMap f (x, s) =
  let t = f s
  x, t

let private pairThen f (x, s) =
  let y, t = f s
  (x, y), t

let private cons head tail = head :: tail

let private listRev xs =
  let rec go acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> go (x :: acc) xs

  go [] xs

// -----------------------------------------------
// char
// -----------------------------------------------

let private charIsSpace (c: char): bool =
  c = ' ' || c = '\t' || c = '\r' || c = '\n'

let private charIsDigit (c: char): bool = '0' <= c && c <= '9'

let private charIsAlpha (c: char): bool =
  ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')

let private charToLower (c: char) =
  assert ('A' <= c && c <= 'Z')
  char (int c - int 'A' + int 'a')

// -----------------------------------------------
// string
// -----------------------------------------------

let private strConcat (xs: string list) =
  match xs with
  | [] -> ""
  | x :: xs -> x + strConcat xs

let private toLowerCamel (str: string) =
  string (charToLower str.[0])
  + str.[1..str.Length - 1]

// -----------------------------------------------
// YamlValue
// -----------------------------------------------

[<NoEquality; NoComparison>]
type YamlValue =
  | YamlStr of string
  | YamlTable of (string * YamlValue) list

// -----------------------------------------------
// Yaml parser
// -----------------------------------------------

type RowIndex = int

type ColumnIndex = int

type Pos = RowIndex * ColumnIndex

let private pError msg (_, _, y, x) =
  printfn "ERROR: %s (%d:%d)" msg (y + 1) (x + 1)
  assert false
  exit 1

let private pBump (text: string, i: int, y, x) =
  assert (i < text.Length)
  if text.[i] = '\n' then text, i + 1, y + 1, 0 else text, i + 1, y, x + 1

let private pWhile pred p =
  let rec go p =
    if pLook p <> '\x00' && pred (pLook p) then p |> pBump |> go else p

  go p

let private pLook (text: string, i: int, _, _) =
  if i < text.Length then text.[i] else '\x00'

let private pSlice (text: string, l: int, _, _) (_, r: int, _, _) =
  assert (0 <= l && l <= r && r <= text.Length)
  if l = r then "" else text.[l..r - 1]

let private pToPos (_, _, y, x) = y, x

let private pIsAligned (_, posX: int) (_, _, _, x: int) = x = posX

let private pIsDeeper (_, posX: int) (_, _, _, x: int) = x > posX

let private pExpect (str: string) p =
  let rec go count p =
    if count = 0 || pLook p = '\x00' then p else go (count - 1) (p |> pBump)

  let q = go str.Length p
  if pSlice p q <> str then pError ("Expected `" + str + "`") p
  q

let private pLine p =
  p |> pWhile (fun c -> c <> '\r' && c <> '\n')

let private pBlank p =
  let p =
    p |> pWhile (fun c -> c = ' ' || c = '\r')

  if pLook p = '#' then p |> pLine else p

let private pSpace p =
  let p = p |> pBlank
  if pLook p |> charIsSpace then p |> pBump |> pSpace else p

let private pIdent p =
  let q =
    p
    |> pWhile (fun c -> c = '_' || charIsDigit c || charIsAlpha c)

  pSlice p q, q

let private pEof p =
  if pLook p <> '\x00' then pError "Expected EOF" p

let private pTable basePos p =
  let rec go (entries, p) =
    let q = p |> pSpace
    if q
       |> pIsAligned basePos
       && q |> pIdent |> fst <> "" then
      q
      |> pIdent
      |> pairMap pBlank
      |> pairMap (pExpect ":")
      |> pairMap pSpace
      |> pairThen (pItem basePos)
      |> stateMap (fun entry -> entry :: entries)
      |> go
    else
      YamlTable(listRev entries), p

  go ([], p)

let private pItem basePos p =
  if p |> pIsDeeper basePos then
    let pos = p |> pToPos
    let _, q = p |> pIdent |> pairMap pBlank
    if pLook q = ':' then
      pTable pos p
    else
      let q = p |> pLine
      let text = pSlice p q
      YamlStr text, q
  else
    pError "Expected a value" p

let parseYaml (text: string): YamlValue =
  let p = text, 0, 0, 0
  let basePos = 0, 0

  p
  |> pTable basePos
  |> pairMap pSpace
  |> pairMap pEof
  |> fst
