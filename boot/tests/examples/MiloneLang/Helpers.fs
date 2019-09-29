/// Defines the functions used in multiple modules.
module rec MiloneLang.Helpers

open MiloneLang.Types
open MiloneLang.Records

/// `List.map`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
let stMap f (xs, ctx) =
  let rec go acc (xs, ctx) =
    match xs with
    | [] ->
      listRev acc, ctx
    | x :: xs ->
      let y, ctx = f (x, ctx)
      go (y :: acc) (xs, ctx)
  go [] (xs, ctx)

/// `List.bind`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stFlatMap (fun (x, ctx) -> ys, ctx)
let stFlatMap f (xs, ctx) =
  let rec go acc xs ctx =
    match xs with
    | [] ->
      listRev acc, ctx
    | x :: xs ->
      let acc, ctx = f (x, acc, ctx)
      go acc xs ctx
  go [] xs ctx

/// `Option.map`, modifying context.
let stOptionMap f (x, ctx) =
  match x with
  | Some x ->
    let x, ctx = f (x, ctx)
    Some x, ctx
  | None ->
    None, ctx

/// Maps over a list, collecting things, mutating context.
let exMap f (xs, acc, ctx) =
  let rec go ys xs acc ctx =
    match xs with
    | [] ->
      listRev ys, acc, ctx
    | x :: xs ->
      let y, acc, ctx = f (x, acc, ctx)
      go (y :: ys) xs acc ctx
  go [] xs acc ctx

// -----------------------------------------------
// List
// -----------------------------------------------

let cons head tail = head :: tail

let listIsEmpty xs =
  match xs with
  | [] ->
    true

  | _ ->
    false

let listLength xs =
  let rec go len xs =
    match xs with
    | [] ->
      len

    | _ :: xs ->
      go (len + 1) xs

  go 0 xs

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] ->
      acc

    | x :: xs ->
      go (x :: acc) xs

  go [] xs

let rec listIter f xs =
  match xs with
  | [] ->
    ()

  | x :: xs ->
    f x
    listIter f xs

let listMap f xs =
  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc

    | x :: xs ->
      go (f x :: acc) xs

  go [] xs

let listMapWithIndex f xs =
  let rec go acc i xs =
    match xs with
    | [] ->
      listRev acc

    | x :: xs ->
      go (f i x :: acc) (i + 1) xs

  go [] 0 xs

let listFilter pred xs =
  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc

    | x :: xs ->
      let acc = if pred x then x :: acc else acc
      go acc xs

  go [] xs

let listChoose f xs =
  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc

    | x :: xs ->
      let acc =
        match f x with
        | Some y ->
          y :: acc

        | None ->
          acc

      go acc xs

  go [] xs

let listCollect f xs =
  let rec gogo acc ys =
    match ys with
    | [] ->
      acc

    | y :: ys ->
      gogo (y :: acc) ys

  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc

    | x :: xs ->
      let acc = gogo acc (f x)
      go acc xs

  go [] xs

let listForAll pred xs =
  let rec go xs =
    match xs with
    | [] ->
      true

    | x :: xs ->
      pred x && go xs

  go xs

let listExists pred xs =
  let rec go xs =
    match xs with
    | [] ->
      false

    | x :: xs ->
      pred x || go xs

  go xs

/// USAGE: `items |> listFold (fun state item -> nextState) initialState`
let listFold folder state xs =
  let rec go state xs =
    match xs with
    | [] ->
      state

    | x :: xs ->
      go (folder state x) xs

  go state xs

let listReduce reducer xs =
  match xs with
  | [] ->
    failwith "listReduce: empty"

  | x :: xs ->
    listFold reducer x xs

let listLast xs =
  let rec go xs =
    match xs with
    | [] ->
      failwith "listLast: empty"

    | [x] ->
      x

    | _ :: xs ->
      go xs

  go xs

let listSkip count xs =
  let rec go count xs =
    match xs with
    | [] ->
      []

    | _ when count <= 0 ->
      xs

    | _ :: xs ->
      go (count - 1) xs

  go count xs

let listTruncate count xs =
  let rec go acc count xs =
    match xs with
    | [] ->
      listRev acc

    | _ when count <= 0 ->
      listRev acc

    | x :: xs ->
      go (x :: acc) (count - 1) xs

  go [] count xs

let listAppend xs ys =
  let rec go acc xs =
    match xs with
    | [] ->
      acc

    | x :: xs ->
      go (x :: acc) xs

  go ys (listRev xs)

let listSortCore unique cmp xs =
  // `merge (xs, xn) (ys, yn) = (zs, zn), d` where
  // `zs.[0..zn - 1]` is the merge of `xs.[0..xn - 1]` and `ys.[0..yn - 1]`,
  // and `d` is the number of duplicated items.
  let rec merge (xs, xn) (ys, yn) =
    if xn = 0 then
      (ys, yn), 0
    else if yn = 0 then
      (xs, xn), 0
    else
      match xs, ys with
      | [], _
      | _, [] ->
        failwith "NEVER: wrong list length"

      | x :: xs1, y :: ys1 ->
        let c = cmp x y
        if c > 0 then
          let (zs, zn), d = merge (xs, xn) (ys1, yn - 1)
          assert (zn + d = xn + (yn - 1))
          (y :: zs, zn + 1), d
        else if c = 0 && unique then
          let (zs, zn), d = merge (xs, xn) (ys1, yn - 1)
          assert (zn + d = xn + (yn - 1))
          (zs, zn), d + 1
        else
          let (zs, zn), d = merge (xs1, xn - 1) (ys, yn)
          assert (zn + d = (xn - 1) + yn)
          (x :: zs, zn + 1), d

  // `go (xs, xn) = (zs, zn), xs1, d` where
  // `zs.[0..xn - 1]` is the sort of `xs.[0..xn - 1]`,
  // `xs1 = xs.[xn..]`,
  // and `d` is the number of duplicated items.
  let rec go (xs, n) =
    if n <= 1 then
      (xs, n), listSkip n xs, 0
    else
      let m = n / 2
      let (xs, xn), xs1, d1 = go (xs, m)
      let (ys, yn), ys1, d2 = go (xs1, n - m)
      let (zs, zn), d3 = merge (xs, xn) (ys, yn)
      (zs, zn), ys1, d1 + d2 + d3

  let xn = listLength xs
  let (zs, zn), ws, d = go (xs, xn)
  assert (zn + d = xn)
  assert (ws |> listIsEmpty)
  listTruncate zn zs

let listSort cmp xs =
  listSortCore false cmp xs

let listUnique cmp xs =
  listSortCore true cmp xs

// -----------------------------------------------
// Assoc
// -----------------------------------------------

let assocFind eq key assoc =
  let rec go assoc =
    match assoc with
    | [] ->
      None

    | (firstKey, firstValue) :: _
      when eq key firstKey ->
      Some firstValue

    | _ :: assoc ->
      go assoc

  go assoc

// -----------------------------------------------
// AssocMap
// -----------------------------------------------

let mapEmpty cmp: AssocMap<_, _> =
  [], cmp

let mapAdd key value (assoc, cmp): AssocMap<_, _> =
  (key, value) :: assoc, cmp

let mapRemove key (assoc, cmp): AssocMap<_, _> =
  assoc |> listFilter (fun (k, _) -> cmp k key <> 0), cmp

let mapTryFind key ((assoc, cmp): AssocMap<_, _>) =
  let rec go assoc =
    match assoc with
    | [] ->
      None

    | (k, v) :: _
      when cmp k key = 0 ->
      Some v

    | _ :: assoc ->
      go assoc

  go assoc

let mapFind key map =
  match mapTryFind key map with
  | Some value ->
    value

  | None ->
    failwithf "mapFind: missing key (%A)" key

let mapContainsKey key map =
  match mapTryFind key map with
  | Some _ ->
    true

  | None ->
    false

let mapFold folder state (map: AssocMap<_, _>) =
  let rec go state assoc =
    match assoc with
    | [] ->
      state

    | (k, v) :: assoc ->
      go (folder state k v) assoc

  let _, cmp = map
  go state (mapToList map)

let mapMap f map: AssocMap<_, _> =
  let _, cmp = map
  map |> mapToList |> listMap (fun (k, v) -> k, f k v), cmp

let mapToList ((assoc, cmp): AssocMap<_, _>) =
  listUnique (fun (lk, _) (rk, _) -> cmp lk rk) assoc

let mapOfList cmp assoc: AssocMap<_, _> =
  listRev assoc, cmp

// -----------------------------------------------
// Int
// -----------------------------------------------

let intMin (x: int) (y: int) =
  if x > y then y else x

let intMax (x: int) (y: int) =
  if x < y then y else x

let intEq (x: int) (y: int) =
  x = y

let intCmp (x: int) (y: int) =
  if y < x then
    1
  else if y = x then
    0
  else
    -1

let intToHexWithPadding (len: int) (value: int) =
  if value < 0 then
    failwith "intToHexWithPadding: unimplemented negative"
  else

  assert (len >= 0)

  let rec go acc len (n: int) =
    if n = 0 && len <= 0 then
      acc
    else
      let d = n % 16
      let s = "0123456789abcdef" |> strSlice d (d + 1)
      go (s + acc) (len - 1) (n / 16)

  if value = 0 && len = 0 then
    "0"
  else
    go "" len value

let intFromHex (l: int) (r: int) (s: string) =
  assert (0 <= l && l < r && r <= s.Length)

  let hexDigitToInt (c: char) =
    if '0' <= c && c <= '9' then
      charSub c '0'
    else if 'A' <= c && c <= 'F' then
      charSub c 'A' + 10
    else if 'a' <= c && c <= 'f' then
      charSub c 'a' + 10
    else
      assert false
      0

  let rec go (acc: int) (i: int) =
    if i = r then
      acc
    else
      let d = hexDigitToInt s.[i]
      go (acc * 16 + d) (i + 1)

  go 0 l

// -----------------------------------------------
// Char
// -----------------------------------------------

let charSub (x: char) (y: char) =
  int x - int y

let charIsControl (c: char) =
  let n = int c
  0 <= n && n < 32 || n = 127

let charIsSpace (c: char): bool =
  c = ' ' || c = '\t' || c = '\r' || c = '\n'

let charIsDigit (c: char): bool =
  '0' <= c && c <= '9'

let charIsAlpha (c: char): bool =
  ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')

let charNeedsEscaping (c: char) =
  charIsControl c || c = '\\' || c = '"' || c = '\''

let charEscape (c: char) =
  assert (c |> charNeedsEscaping)

  match c with
  | '\x00' ->
    // C-style.
    "\\0"

  | '\t' ->
    "\\t"

  | '\n' ->
    "\\n"

  | '\r' ->
    "\\r"

  | '\'' ->
    "\\\'"

  | '\"' ->
    "\\\""

  | '\\' ->
    "\\\\"

  | c ->
    let h = c |> int |> intToHexWithPadding 2
    "\\x" + h

// -----------------------------------------------
// String
// -----------------------------------------------

let strCmp (x: string) (y: string) =
  if y < x then
    1
  else if y = x then
    0
  else
    -1

let strSlice (start: int) (endIndex: int) (s: string): string =
  assert (start <= endIndex && endIndex <= s.Length)
  if start >= endIndex then
    ""
  else
    s.[start..endIndex - 1]

let strConcat (xs: string list) =
  /// Get (str, ys) where
  /// `str` is the concatenation of first `xn` items in `xs`
  /// `ys` is a list of the other items
  let rec go xs xn =
    // assert (xn <= listLength xs)
    match xs with
    | [] ->
      assert (xn = 0)
      "", []
    | x :: xs when xn = 1 ->
      x, xs
    | x :: y :: xs when xn = 2 ->
      x + y, xs
    | xs ->
      let m = xn / 2
      let l, xs = go xs m
      let r, xs = go xs (xn - m)
      l + r, xs
  let n = xs |> listLength
  let s, xs = go xs n
  assert (xs |> listIsEmpty)
  s

  // let rec go (xs: string list) =
  //   match xs with
  //   | [] ->
  //     ""
  //   | x :: xs ->
  //     x + go xs
  // go xs

let strNeedsEscaping (str: string) =
  let rec go i = i < str.Length && (charNeedsEscaping str.[i] || go (i + 1))
  go 0

let strEscape (str: string) =
  let rec go acc i =
    /// Finds the end index of the maximum non-escaping segment
    /// that starts at `l`.
    let rec raw i =
      if i = str.Length || charNeedsEscaping str.[i] then
        i
      else
        raw (i + 1)

    // Skip the non-escape segment that starts at `i`.
    let i, acc =
      let r = raw i
      r, (str |> strSlice i r) :: acc

    if i = str.Length then
      acc
    else
      let t = str.[i] |> charEscape
      go (t :: acc) (i + 1)

  if str |> strNeedsEscaping |> not then
    str
  else
    go [] 0 |> listRev |> strConcat

// -----------------------------------------------
// Location
// -----------------------------------------------

/// No location information. Should be fixed.
let noLoc = -1, -1

let locX ((_, x): Loc) = x

let locY ((y, _): Loc) = y

let locIsSameRow first second =
  locY first = locY second

let locIsSameColumn first second =
  locX first = locX second

/// Gets if `secondLoc` is inside of the block of `firstLoc`.
let locInside (firstLoc: Loc) (secondLoc: Loc) =
  locX firstLoc <= locX secondLoc

let locAddX dx ((y, x): Loc) =
  y, x + dx

let locMax ((firstY, firstX): Loc) ((secondY, secondX): Loc) =
  intMax firstY secondY, intMax firstX secondX

let locToString ((y, x): Loc) =
  string (y + 1) + ":" + string (x + 1)

// -----------------------------------------------
// Token
// -----------------------------------------------

/// Gets if a token is in the first set of expressions/patterns,
/// i.e. whether it can be the first token of an expression or pattern.
let tokenIsExprOrPatFirst (token: Token) =
  match token with
  | Token.Bool _
  | Token.Int _
  | Token.Char _
  | Token.Str _
  | Token.Ident _
  | Token.ParenL
  | Token.BracketL ->
    true

  | _ ->
    false

/// Gets if a token is in the first set of expressions.
let tokenIsExprFirst (token: Token) =
  match token with
  | _ when tokenIsExprOrPatFirst token ->
    true

  | Token.Minus
  | Token.If
  | Token.Match
  | Token.Fun
  | Token.Do
  | Token.Let
  | Token.Type
  | Token.Open ->
    true

  | _ ->
    false

/// In the first set of arguments?
let tokenIsArgFirst (token: Token) =
  match token with
  | Token.Minus ->
    false

  | _ ->
    tokenIsExprFirst token

let tokenIsPatFirst (token: Token) =
  tokenIsExprOrPatFirst token

let tokenIsAccessModifier token =
  match token with
  | Token.Private
  | Token.Internal
  | Token.Public ->
    true

  | _ ->
    false

// -----------------------------------------------
// OpLevel
// -----------------------------------------------

let opLevelToNext level =
  match level with
  | OpLevel.Or ->
    OpLevel.And

  | OpLevel.And ->
    OpLevel.Cmp

  | OpLevel.Cmp ->
    OpLevel.Pipe

  | OpLevel.Pipe ->
    OpLevel.Cons

  | OpLevel.Cons ->
    OpLevel.Add

  | OpLevel.Add ->
    OpLevel.Mul

  | OpLevel.Mul
  | OpLevel.Prefix ->
    OpLevel.Prefix

// -----------------------------------------------
// APat
// -----------------------------------------------

let apFalse loc =
  APat.Lit (litFalse, loc)

let apTrue loc =
  APat.Lit (litTrue, loc)

// -----------------------------------------------
// AExpr
// -----------------------------------------------

let axUnit loc =
  AExpr.TupleLit ([], loc)

let axFalse loc =
  AExpr.Lit (litFalse, loc)

let axTrue loc =
  AExpr.Lit (litTrue, loc)

let axNil loc =
  AExpr.ListLit ([], loc)

let axApp3 f x1 x2 x3 loc =
  let app x f = AExpr.Bin (Op.App, f, x, loc)
  f |> app x1 |> app x2 |> app x3

/// `not x` ==> `x = false`
let axNot arg loc =
  let falseExpr = axFalse loc
  AExpr.Bin (Op.Eq, arg, falseExpr, loc)

// -----------------------------------------------
// DumpTree (for debugging)
// -----------------------------------------------

let dumpTreeNew text children =
  DumpTree (text, children, [])

let dumpTreeNewLeaf text =
  DumpTree (text, [], [])

let dumpTreeAttachNext next tree =
  match tree with
  | DumpTree (text, children, oldNext) ->
    assert (children |> listIsEmpty |> not)
    assert (oldNext |> listIsEmpty)
    DumpTree (text, children, [next])

let dumpTreeFromError (msg: string) (y, x) =
  let y = string (y + 1)
  let x = string (x + 1)
  dumpTreeNew "ERROR" [
    dumpTreeNewLeaf msg
    dumpTreeNewLeaf ("(" + y + ":" + x + ")")
  ]

let dumpTreeToString (node: DumpTree) =
  let rec go eol node acc =
    let rec goChildren eol children acc =
      match children with
      | [] ->
        acc

      | child :: children ->
        acc
        |> cons eol |> cons "- " |> go (eol + "  ") child
        |> goChildren eol children

    let goNext eol next acc =
      match next with
      | [] ->
        acc

      | [next] ->
        acc |> cons eol |> go eol next

      | _ ->
        failwith "NEVER: DumpTree.next never empty"

    match node with
    | DumpTree (text, [], []) ->
      acc |> cons (strEscape text)

    | DumpTree (text, [DumpTree (childText, [], [])], next) ->
      acc
      |> cons (strEscape text)
      |> cons ": "
      |> cons (strEscape childText)
      |> goNext eol next

    | DumpTree (text, children, next) ->
      acc
      |> cons (strEscape text)
      |> cons ":"
      |> goChildren eol children
      |> goNext eol next

  let eol = "\n"
  [] |> go eol node |> listRev |> strConcat

// -----------------------------------------------
// Name context
// -----------------------------------------------

let nameCtxEmpty () =
  NameCtx (mapEmpty intCmp, 0)

let nameCtxAdd ident (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> mapAdd serial ident
  serial, NameCtx (map, serial)

let nameCtxFind serial (NameCtx (map, _)) =
  map |> mapFind serial

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

let traitMapTys f it =
  match it with
  | Trait.Add ty ->
    Trait.Add (f ty)

  | Trait.Eq ty ->
    Trait.Eq (f ty)

  | Trait.Cmp ty ->
    Trait.Cmp (f ty)

  | Trait.Index (lTy, rTy, outputTy) ->
    Trait.Index (f lTy, f rTy, f outputTy)

  | Trait.ToInt ty ->
    Trait.ToInt (f ty)

  | Trait.ToString ty ->
    Trait.ToString (f ty)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

/// Placeholder. No type info in the parsing phase.
let noTy = Ty.Error noLoc

let tyBool = Ty.Con (TyCon.Bool, [])

let tyInt = Ty.Con (TyCon.Int, [])

let tyChar = Ty.Con (TyCon.Char, [])

let tyStr = Ty.Con (TyCon.Str, [])

let tyObj = Ty.Con (TyCon.Obj, [])

let tyTuple tys =
  Ty.Con (TyCon.Tuple, tys)

let tyList ty =
  Ty.Con (TyCon.List, [ty])

let tyFun sourceTy targetTy =
  Ty.Con (TyCon.Fun, [sourceTy; targetTy])

let tyUnit =
  tyTuple []

let tyRef serial tys =
  Ty.Con (TyCon.Ref serial, tys)

let tyPrimFromIdent ident tys loc =
  match ident, tys with
  | "unit", [] ->
    tyUnit

  | "bool", [] ->
    tyBool

  | "int", [] ->
    tyInt

  | "char", [] ->
    tyChar

  | "string", [] ->
    tyStr

  | "obj", [] ->
    tyObj

  | "option", [itemTy] ->
    // FIXME: option is just an alias of list for now
    tyList itemTy

  | "list", [itemTy] ->
    tyList itemTy

  | "AssocMap", [keyTy; _] ->
    tyTuple [tyList (tyTuple tys); tyFun keyTy (tyFun keyTy tyInt)]

  | _ ->
    Ty.Error loc

/// Gets if the specified type variable doesn't appear in a type.
let tyIsFreeIn ty tySerial: bool =
  let rec go ty =
    match ty with
    | Ty.Error _
    | Ty.Con (_, []) ->
      true

    | Ty.Con (tyCon, ty :: tys) ->
      go ty && go (Ty.Con (tyCon, tys))

    | Ty.Meta (s, _) ->
      s <> tySerial

  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are substituted.
let tyIsMonomorphic ty: bool =
  let rec go tys =
    match tys with
    | [] ->
      true

    | Ty.Meta _ :: _ ->
      false

    | Ty.Error _ :: tys ->
      go tys

    | Ty.Con (_, tys1) :: tys2 ->
      go tys1 && go tys2

  go [ty]

/// Gets a list of type variables.
/// Assume all bound type variables are substituted.
let tyCollectFreeVars ty =
  let rec go fvAcc tys =
    match tys with
    | [] ->
      fvAcc

    | Ty.Error _ :: tys
    | Ty.Con (_, []) :: tys ->
      go fvAcc tys

    | Ty.Con (_, tys1) :: tys2 ->
      let acc = go fvAcc tys1
      let acc = go acc tys2
      acc

    | Ty.Meta (serial, _) :: tys ->
      let acc = serial :: fvAcc
      go acc tys

  go [] [ty] |> listUnique intCmp

let rec tyToArity ty =
  match ty with
  | Ty.Con (TyCon.Fun, [_; ty]) ->
    1 + tyToArity ty
  | _ ->
    0

/// Converts nested function type to multi-arguments function type.
let rec tyToArgList ty =
  let rec go n acc ty =
    match ty with
    | Ty.Con (TyCon.Fun, [sTy; tTy]) ->
      go (n + 1) (sTy :: acc) tTy
    | tTy ->
      n, listRev acc, tTy
  go 0 [] ty

/// Substitutes meta types in a type as possible.
let tySubst (substMeta: TySerial -> Ty option) ty =
  let rec go ty =
    match ty with
    | Ty.Error _
    | Ty.Con (_, []) ->
      ty

    | Ty.Con (tyCon, tys) ->
      Ty.Con (tyCon, listMap go tys)

    | Ty.Meta (tySerial, _) ->
      match substMeta tySerial with
      | Some ty ->
        go ty

      | None ->
        ty

  go ty

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let tyDefToIdent tyDef =
  match tyDef with
  | TyDef.Meta (ident, _, _) -> ident
  | TyDef.Union (ident, _, _) -> ident

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varDefToIdent varDef =
  match varDef with
  | VarDef.Var (ident, _, _) -> ident
  | VarDef.Fun (ident, _, _, _) -> ident
  | VarDef.Variant (ident, _, _, _, _, _) -> ident

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litTrue = Lit.Bool true

let litFalse = Lit.Bool false

let litToTy (lit: Lit): Ty =
  match lit with
  | Lit.Bool _ -> tyBool
  | Lit.Int _ -> tyInt
  | Lit.Char _ -> tyChar
  | Lit.Str _ -> tyStr

// -----------------------------------------------
// Primitives (HIR)
// -----------------------------------------------

let primFromIdent ident =
  match ident with
  | "not" ->
    HPrim.Not |> Some

  | "exit" ->
    HPrim.Exit |> Some

  | "assert" ->
    HPrim.Assert |> Some

  | "box" ->
    HPrim.Box |> Some

  | "unbox" ->
    HPrim.Unbox |> Some

  | "printfn" ->
    HPrim.Printfn |> Some

  | "char" ->
    HPrim.Char |> Some

  | "int" ->
    HPrim.Int |> Some

  | "string" ->
    HPrim.String |> Some

  | "None" ->
    HPrim.OptionNone |> Some

  | "Some" ->
    HPrim.OptionSome |> Some

  | "__nativeFun" ->
    HPrim.NativeFun ("<native-fun>", -1) |> Some

  | _ ->
    None

let primToTySpec prim =
  let meta id = Ty.Meta (id, noLoc)
  let mono ty = TySpec (ty, [])
  let poly ty traits = TySpec (ty, traits)

  match prim with
  | HPrim.Add ->
    let addTy = meta 1
    poly (tyFun addTy (tyFun addTy addTy)) [Trait.Add addTy]

  | HPrim.Sub ->
    mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Mul ->
    mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Div ->
    mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Mod ->
    mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Eq ->
    let eqTy = meta 1
    poly (tyFun eqTy (tyFun eqTy tyBool)) [Trait.Eq eqTy]

  | HPrim.Lt ->
    let cmpTy = meta 1
    poly (tyFun cmpTy (tyFun cmpTy tyBool)) [Trait.Cmp cmpTy]

  | HPrim.Nil ->
    let itemTy = meta 1
    poly (tyList itemTy) []

  | HPrim.Cons ->
    let itemTy = meta 1
    let listTy = tyList itemTy
    poly (tyFun itemTy (tyFun listTy listTy)) []

  | HPrim.OptionNone ->
    let itemTy = meta 1
    poly (tyList itemTy) []

  | HPrim.OptionSome ->
    let itemTy = meta 1
    let listTy = tyList itemTy
    poly (tyFun itemTy listTy) []

  | HPrim.Index ->
    let lTy = meta 1
    let rTy = meta 2
    let resultTy = meta 3
    poly (tyFun lTy (tyFun rTy resultTy)) [Trait.Index (lTy, rTy, resultTy)]

  | HPrim.Not ->
    mono (tyFun tyBool tyBool)

  | HPrim.Exit ->
    let resultTy = meta 1
    poly (tyFun tyInt resultTy) []

  | HPrim.Assert ->
    mono (tyFun tyBool tyUnit)

  | HPrim.Box ->
    let itemTy = meta 1
    poly (tyFun itemTy tyObj) []

  | HPrim.Unbox ->
    let itemTy = meta 1
    poly (tyFun tyObj itemTy) []

  | HPrim.Char ->
    // FIXME: `char` can take non-int types.
    mono (tyFun tyInt tyChar)

  | HPrim.Int ->
    let toIntTy = meta 1
    poly (tyFun toIntTy tyInt) [Trait.ToInt toIntTy]

  | HPrim.String ->
    let toStrTy = meta 1
    poly (tyFun toStrTy tyStr) [Trait.ToString toStrTy]

  | HPrim.StrLength ->
    mono (tyFun tyStr tyInt)

  | HPrim.StrGetSlice ->
    mono (tyFun tyInt (tyFun tyInt (tyFun tyStr tyStr)))

  | HPrim.Printfn
  | HPrim.NativeFun _ ->
    poly (meta 1) []

let primToArity ty prim =
  match prim with
  | HPrim.Nil
  | HPrim.OptionNone ->
    0
  | HPrim.OptionSome
  | HPrim.Not
  | HPrim.Exit
  | HPrim.Assert
  | HPrim.Box
  | HPrim.Unbox
  | HPrim.StrLength
  | HPrim.Char
  | HPrim.Int
  | HPrim.String ->
    1
  | HPrim.Add
  | HPrim.Sub
  | HPrim.Mul
  | HPrim.Div
  | HPrim.Mod
  | HPrim.Eq
  | HPrim.Lt
  | HPrim.Cons
  | HPrim.Index ->
    2
  | HPrim.StrGetSlice ->
    3
  | HPrim.Printfn ->
    ty |> tyToArity
  | HPrim.NativeFun (_, arity) ->
    arity

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let patUnit loc =
  HPat.Tuple ([], tyUnit, loc)

let patNil itemTy loc =
  HPat.Nil (itemTy, loc)

let rec patExtract (pat: HPat): Ty * Loc =
  match pat with
  | HPat.Lit (lit, a) ->
    litToTy lit, a
  | HPat.Nil (itemTy, a) ->
    tyList itemTy, a
  | HPat.OptionNone (itemTy, a) ->
    tyList itemTy, a
  | HPat.OptionSome (itemTy, a) ->
    tyList itemTy, a
  | HPat.Discard (ty, a) ->
    ty, a
  | HPat.Ref (_, ty, a) ->
    ty, a
  | HPat.Nav (_, _, ty, a) ->
    ty, a
  | HPat.Call (_, _, ty, a) ->
    ty, a
  | HPat.Cons (_, _, itemTy, a) ->
    tyList itemTy, a
  | HPat.Tuple (_, ty, a) ->
    ty, a
  | HPat.As (pat, _, a) ->
    let ty, _ = patExtract pat
    ty, a
  | HPat.Anno (_, ty, a) ->
    ty, a
  | HPat.Or (_, _, ty, a) ->
    ty, a

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: HPat): HPat =
  let rec go pat =
    match pat with
    | HPat.Lit (lit, a) ->
      HPat.Lit (lit, g a)
    | HPat.Nil (itemTy, a) ->
      HPat.Nil (f itemTy, g a)
    | HPat.OptionNone (itemTy, a) ->
      HPat.OptionNone (f itemTy, g a)
    | HPat.OptionSome (itemTy, a) ->
      HPat.OptionSome (f itemTy, g a)
    | HPat.Discard (ty, a) ->
      HPat.Discard (f ty, g a)
    | HPat.Ref (serial, ty, a) ->
      HPat.Ref (serial, f ty, g a)
    | HPat.Nav (pat, ident, ty, a) ->
      HPat.Nav (pat, ident, f ty, g a)
    | HPat.Call (callee, args, ty, a) ->
      HPat.Call (go callee, listMap go args, f ty, g a)
    | HPat.Cons (l, r, itemTy, a) ->
      HPat.Cons (go l, go r, f itemTy, g a)
    | HPat.Tuple (itemPats, ty, a) ->
      HPat.Tuple (listMap go itemPats, f ty, g a)
    | HPat.As (pat, serial, a) ->
      HPat.As (go pat, serial, g a)
    | HPat.Anno (pat, ty, a) ->
      HPat.Anno (go pat, f ty, g a)
    | HPat.Or (first, second, ty, a) ->
      HPat.Or (go first, go second, f ty, g a)
  go pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | HPat.Lit _
    | HPat.Discard _
    | HPat.Ref _
    | HPat.Nil _
    | HPat.OptionNone _
    | HPat.OptionSome _ ->
      [pat]
    | HPat.Nav (pat, ident, ty, loc) ->
      go pat |> listMap (fun pat -> HPat.Nav (pat, ident, ty, loc))
    | HPat.Call (callee, [arg], ty, loc) ->
      go callee |> listCollect (fun callee ->
        go arg |> listMap (fun arg ->
          HPat.Call (callee, [arg], ty, loc)
        ))
    | HPat.Cons (l, r, ty, loc) ->
      go l |> listCollect (fun l ->
        go r |> listMap (fun r ->
          HPat.Cons (l, r, ty, loc)
        ))
    | HPat.Tuple (itemPats, ty, loc) ->
      let rec gogo itemPats =
        match itemPats with
        | [] -> [[]]
        | itemPat :: itemPats ->
          let itemPat = go itemPat
          gogo itemPats |> listCollect (fun itemPats ->
            itemPat |> listMap (fun itemPat ->
              itemPat :: itemPats
            ))
      gogo itemPats |> listMap (fun itemPats -> HPat.Tuple (itemPats, ty, loc))
    | HPat.As (innerPat, _, _) ->
      match go innerPat with
      | [_] ->
        [pat]
      | _ ->
        failwith "Unimpl: Can't use AS patterns conjunction with OR patterns"
    | HPat.Anno (pat, annoTy, loc) ->
      go pat |> listMap (fun pat -> HPat.Anno (pat, annoTy, loc))
    | HPat.Or (first, second, _, _) ->
      listAppend (go first) (go second)
    | HPat.Call _ ->
      failwith "Unimpl"
  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc =
  HExpr.Lit (litTrue, loc)

let hxFalse loc =
  HExpr.Lit (litFalse, loc)

let hxApp f x ty loc =
  HExpr.Inf (InfOp.App, [f; x], ty, loc)

let hxAnno expr ty loc =
  HExpr.Inf (InfOp.Anno, [expr], ty, loc)

let hxSemi items loc =
  HExpr.Inf (InfOp.Semi, items, exprToTy (listLast items), loc)

let hxCallProc callee args resultTy loc =
  HExpr.Inf (InfOp.CallProc, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HExpr.Inf (InfOp.CallClosure, callee :: args, resultTy, loc)

let hxTuple items loc =
  HExpr.Inf (InfOp.Tuple, items, tyTuple (listMap exprToTy items), loc)

let hxUnit loc =
  hxTuple [] loc

let hxNil itemTy loc =
  HExpr.Prim (HPrim.Nil, tyList itemTy, loc)

let hxIsUnitLit expr =
  match expr with
  | HExpr.Inf (InfOp.Tuple, [], _, _) ->
    true
  | _ ->
    false

let hxIsAlwaysTrue expr =
  match expr with
  | HExpr.Lit (Lit.Bool true, _) ->
    true
  | _ ->
    false

let exprExtract (expr: HExpr): Ty * Loc =
  match expr with
  | HExpr.Lit (lit, a) ->
    litToTy lit, a
  | HExpr.Ref (_, ty, a) ->
    ty, a
  | HExpr.Prim (_, ty, a) ->
    ty, a
  | HExpr.Match (_, _, ty, a) ->
    ty, a
  | HExpr.Nav (_, _, ty, a) ->
    ty, a
  | HExpr.Inf (_, _, ty, a) ->
    ty, a
  | HExpr.Let (_, _, _, ty, a) ->
    ty, a
  | HExpr.LetFun (_, _, _, _, _, ty, a) ->
    ty, a
  | HExpr.TyDecl (_, _, a) ->
    tyUnit, a
  | HExpr.Open (_, a) ->
    tyUnit, a
  | HExpr.Error (_, a) ->
    Ty.Error a, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: HExpr): HExpr =
  let goPat pat =
    patMap f g pat
  let rec go expr =
    match expr with
    | HExpr.Lit (lit, a) ->
      HExpr.Lit (lit, g a)
    | HExpr.Ref (serial, ty, a) ->
      HExpr.Ref (serial, f ty, g a)
    | HExpr.Prim (prim, ty, a) ->
      HExpr.Prim (prim, f ty, g a)
    | HExpr.Match (target, arms, ty, a) ->
      let arms =
        arms |> listMap (fun (pat, guard, body) ->
          goPat pat, go guard, go body)
      HExpr.Match (go target, arms, f ty, g a)
    | HExpr.Nav (sub, mes, ty, a) ->
      HExpr.Nav (go sub, mes, f ty, g a)
    | HExpr.Inf (infOp, args, resultTy, a) ->
      HExpr.Inf (infOp, listMap go args, f resultTy, g a)
    | HExpr.Let (pat, init, next, ty, a) ->
      HExpr.Let (goPat pat, go init, go next, f ty, g a)
    | HExpr.LetFun (serial, isMainFun, args, body, next, ty, a) ->
      HExpr.LetFun (serial, isMainFun, listMap goPat args, go body, go next, f ty, g a)
    | HExpr.TyDecl (serial, tyDef, a) ->
      HExpr.TyDecl (serial, tyDef, g a)
    | HExpr.Open (path, a) ->
      HExpr.Open (path, g a)
    | HExpr.Error (error, a) ->
      HExpr.Error (error, g a)
  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty
