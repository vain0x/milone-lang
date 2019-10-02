module rec Program

let stateMap f (x, s) =
  f x, s

let pairMap f (x, s) =
  let t = f s
  x, t

let pairThen f (x, s) =
  let y, t = f s
  (x, y), t

let cons head tail =
  head :: tail

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] ->
      acc

    | x :: xs ->
      go (x :: acc) xs

  go [] xs

let strConcat (xs: string list) =
  match xs with
  | [] ->
    ""

  | x :: xs ->
    x + strConcat xs

let charToLower (c: char) =
  assert ('A' <= c && c <= 'Z')
  char (int c - int 'A' + int 'a')

let toLowerCamel (str: string) =
  string (charToLower str.[0]) + str.[1..str.Length - 1]

// -----------------------------------------------
// Yaml parser
// -----------------------------------------------

type RowIndex = int

type ColumnIndex = int

type Loc = RowIndex * ColumnIndex

type Yaml =
  | Str
    of string
  | Table
    of (string * Yaml) list

let charIsSpace (c: char): bool =
  c = ' ' || c = '\t' || c = '\r' || c = '\n'

let charIsDigit (c: char): bool =
  '0' <= c && c <= '9'

let charIsAlpha (c: char): bool =
  ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')

let pError msg (_, _, y, x) =
  printfn "ERROR: %s (%d:%d)" msg (y + 1) (x + 1)
  assert false
  exit 1

let pBump (text: string, i: int, y, x) =
  assert (i < text.Length)
  if text.[i] = '\n' then
    text, i + 1, y + 1, 0
  else
    text, i + 1, y, x + 1

let pWhile pred p =
  let rec go p =
    if pLook p <> '\x00' && pred (pLook p) then
      p |> pBump |> go
    else
      p

  go p

let pLook (text: string, i: int, _, _) =
  if i < text.Length then
    text.[i]
  else
    '\x00'

let pSlice (text: string, l: int, _, _) (_, r: int, _, _) =
  assert (0 <= l && l <= r && r <= text.Length)
  if l = r then
    ""
  else
    text.[l..r - 1]

let pToLoc (_, _, y, x) =
  y, x

let pIsAligned (_, locX: int) (_, _, _, x: int) =
  x = locX

let pIsDeeper (_, locX: int)(_, _, _, x: int) =
  x > locX

let pExpect (str: string) p =
  let rec go count p =
    if count = 0 || pLook p = '\x00' then
      p
    else
      go (count - 1) (p |> pBump)

  let q = go str.Length p
  if pSlice p q <> str then
    pError ("Expected `" + str + "`") p
  q

let pLine p =
  p |> pWhile (fun c -> c <> '\r' && c <> '\n')

let pBlank p =
  let p = p |> pWhile (fun c -> c = ' ' || c = '\r')
  if pLook p = '#' then
    p |> pLine
  else
    p

let rec pSpace p =
  let p = p |> pBlank
  if pLook p |> charIsSpace then
    p |> pBump |> pSpace
  else
    p

let pIdent p =
  let q = p |> pWhile (fun c -> c = '_' || charIsDigit c || charIsAlpha c)
  pSlice p q, q

let pEof p =
  if pLook p <> '\x00' then
    pError "Expected EOF" p

let pTable baseLoc p =
  let rec go (entries, p) =
    let q = p |> pSpace
    if q |> pIsAligned baseLoc && q |> pIdent |> fst <> "" then
      q
      |> pIdent
      |> pairMap pBlank
      |> pairMap (pExpect ":")
      |> pairMap pSpace
      |> pairThen (pItem baseLoc)
      |> stateMap (fun entry -> entry :: entries)
      |> go
    else
      Yaml.Table (listRev entries), p

  go ([], p)

let pItem baseLoc p =
  if p |> pIsDeeper baseLoc then
    let loc = p |> pToLoc
    let _, q = p |> pIdent |> pairMap pBlank
    if pLook q = ':' then
      pTable loc p
    else
      let q = p |> pLine
      let text = pSlice p q
      Yaml.Str text, q
  else
    pError "Expected a value" p

let parseYaml (text: string) =
  let p = text, 0, 0, 0
  let baseLoc = 0, 0

  p
  |> pTable baseLoc
  |> pairMap pSpace
  |> pairMap pEof
  |> fst

// -----------------------------------------------
// Generator
// -----------------------------------------------

type Ident = string

type Field = Ident * string

type Record = Ident * Field list

let lowerFields fields =
  match fields with
  | [] ->
    []

  | (ident, Yaml.Str ty) :: fields ->
    (ident, ty) :: lowerFields fields

  | _ ->
    printfn "ERROR: invalid structure of field"
    exit 1

let lowerRecords entries =
  match entries with
  | [] ->
    []

  | (ident, Yaml.Table fields) :: entries ->
    (ident, lowerFields fields) :: lowerRecords entries

  | _ ->
    printfn "ERROR: invalid structure of record"
    exit 1

let lower (yaml: Yaml) =
  match yaml with
  | Yaml.Table entries ->
    lowerRecords entries

  | _ ->
    printfn "ERROR: Top level must be a table"
    exit 1

let generateRecordDecl ident fields acc =
  let rec go i fields acc =
    match fields with
    | [] ->
      acc

    | (_, ty) :: fields ->
      acc
      |> cons (if i = 0 then "\n    of " else "\n      * ")
      |> cons ty
      |> go (i + 1) fields

  acc
  |> cons "\ntype " |> cons ident |> cons " ="
  |> cons "\n  | " |> cons ident
  |> go 0 fields
  |> cons "\n"

let generateGetters ident fields acc =
  let rec genPats i j fields acc =
    match fields with
    | [] ->
      acc

    | (fieldIdent, _) :: fields ->
      let acc = if i > 0 then acc |> cons ", " else acc
      let ident = if i = j then toLowerCamel fieldIdent else "_"
      acc |> cons ident |> genPats (i + 1) j fields

  let rec genLets i otherFields acc =
    match otherFields with
    | [] ->
      acc

    | (fieldIdent, _) :: otherFields ->
      acc
      |> cons "\nlet " |> cons (toLowerCamel ident) |> cons "Get" |> cons fieldIdent
      |> cons " (" |> cons ident |> cons " ("
      |> genPats 0 i fields
      |> cons ")) =\n  " |> cons (toLowerCamel fieldIdent) |> cons "\n"
      |> genLets (i + 1) otherFields

  acc |> genLets 0 fields

let generateSetters ident fields acc =
  let rec genPats i j fields acc =
    match fields with
    | [] ->
      acc

    | (fieldIdent, _) :: fields ->
      let acc = if i > 0 then acc |> cons ", " else acc
      let ident = if i <> j then toLowerCamel fieldIdent else "_"
      acc |> cons ident |> genPats (i + 1) j fields

  let rec genExprs i j fields acc =
    match fields with
    | [] ->
      acc

    | (fieldIdent, _) :: fields ->
      let acc = if i > 0 then acc |> cons ", " else acc
      let ident = toLowerCamel fieldIdent
      acc |> cons ident |> genExprs (i + 1) j fields

  let rec go i otherFields acc =
    match otherFields with
    | [] ->
      acc

    | (fieldIdent, _) :: otherFields ->
      acc
      |> cons "\nlet "
      |> cons (toLowerCamel ident) |> cons "With" |> cons fieldIdent
      |> cons " " |> cons (toLowerCamel fieldIdent)
      |> cons " (" |> cons ident |> cons " ("
      |> genPats 0 i fields
      |> cons ")): " |> cons ident
      |> cons " =\n  " |> cons ident
      |> cons " (" |> genExprs 0 i fields |> cons ")\n"
      |> go (i + 1) otherFields

  acc |> go 0 fields

let generateRecords records acc =
  match records with
  | [] ->
    acc

  | (ident, fields) :: records ->
    acc
    |> generateRecordDecl ident fields
    |> generateGetters ident fields
    |> generateSetters ident fields
    |> generateRecords records

let generate (records: Record list): string =
  []
  |> cons "/// ## Records\n"
  |> cons "///\n"
  |> cons "/// Generated by scripts/RecordGen from `Records.yml`.\n"
  |> cons "/// Run `./records` to regenerate.\n"
  |> cons "///\n"
  |> cons "/// Defines some types as synonym of tuple with getter/setter functions\n"
  |> cons "/// because record types are unimplemented in milone-lang.\n"
  |> cons "module rec MiloneLang.Records\n\n"
  |> cons "open MiloneLang.Types\n"
  |> generateRecords records
  |> listRev
  |> strConcat

[<EntryPoint>]
let main _ =
  stdin.ReadToEnd() |> parseYaml |> lower |> generate |> stdout.Write
  0
