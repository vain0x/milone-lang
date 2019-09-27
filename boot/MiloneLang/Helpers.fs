/// Defines the functions used in multiple modules.
module rec MiloneLang.Helpers

open MiloneLang.Types

/// `List.map`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
let stMap f (xs, ctx) =
  let rec go acc (xs, ctx) =
    match xs with
    | [] ->
      List.rev acc, ctx
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
      List.rev acc, ctx
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
      List.rev ys, acc, ctx
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

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] ->
      acc
    | x :: xs ->
      go (x :: acc) xs
  go [] xs

let listLength xs =
  let rec go len xs =
    match xs with
    | [] ->
      len
    | _ :: xs ->
      go (len + 1) xs
  go 0 xs

let listMap f xs =
  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc
    | x :: xs ->
      go (f x :: acc) xs
  go [] xs

let listTruncate count xs =
  let rec go count xs =
    match xs with
    | [] ->
      []

    | _ when count <= 0 ->
      []

    | x :: xs ->
      x :: go (count - 1) xs

  go count xs

let listUnique (xs: 'x list): 'x list =
  xs |> set |> Set.toList

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
// Int
// -----------------------------------------------

let intMin (x: int) (y: int) =
  if x > y then y else x

let intMax (x: int) (y: int) =
  if x < y then y else x

let intEq (x: int) (y: int) =
  x = y

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
  NameCtx (Map.empty, 0)

let nameCtxAdd ident (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> Map.add serial ident
  serial, NameCtx (map, serial)

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

  | "Map", [keyTy; _] ->
    // `Map<K, V>` ===> `assoc:(K * V) list * cmp:(K -> K -> int)`
    // because Map is not supported yet.
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

  go [] [ty] |> listUnique

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
      n, List.rev acc, tTy
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
    HPrim.None |> Some

  | "Some" ->
    HPrim.Some |> Some

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

  | HPrim.None ->
    let itemTy = meta 1
    poly (tyList itemTy) []

  | HPrim.Some ->
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
  | HPrim.None ->
    0
  | HPrim.Some
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
  | HPat.None (itemTy, a) ->
    tyList itemTy, a
  | HPat.Some (itemTy, a) ->
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
    | HPat.None (itemTy, a) ->
      HPat.None (f itemTy, g a)
    | HPat.Some (itemTy, a) ->
      HPat.Some (f itemTy, g a)
    | HPat.Discard (ty, a) ->
      HPat.Discard (f ty, g a)
    | HPat.Ref (serial, ty, a) ->
      HPat.Ref (serial, f ty, g a)
    | HPat.Nav (pat, ident, ty, a) ->
      HPat.Nav (pat, ident, f ty, g a)
    | HPat.Call (callee, args, ty, a) ->
      HPat.Call (go callee, List.map go args, f ty, g a)
    | HPat.Cons (l, r, itemTy, a) ->
      HPat.Cons (go l, go r, f itemTy, g a)
    | HPat.Tuple (itemPats, ty, a) ->
      HPat.Tuple (List.map go itemPats, f ty, g a)
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
    | HPat.None _
    | HPat.Some _ ->
      [pat]
    | HPat.Nav (pat, ident, ty, loc) ->
      go pat |> List.map
        (fun pat -> HPat.Nav (pat, ident, ty, loc))
    | HPat.Call (callee, [arg], ty, loc) ->
      go callee |> List.collect (fun callee ->
        go arg |> List.map (fun arg ->
          HPat.Call (callee, [arg], ty, loc)
        ))
    | HPat.Cons (l, r, ty, loc) ->
      go l |> List.collect (fun l ->
        go r |> List.map (fun r ->
          HPat.Cons (l, r, ty, loc)
        ))
    | HPat.Tuple (itemPats, ty, loc) ->
      let rec gogo itemPats =
        match itemPats with
        | [] -> [[]]
        | itemPat :: itemPats ->
          let itemPat = go itemPat
          gogo itemPats |> List.collect (fun itemPats ->
            itemPat |> List.map (fun itemPat ->
              itemPat :: itemPats
            ))
      gogo itemPats |> List.map
        (fun itemPats -> HPat.Tuple (itemPats, ty, loc))
    | HPat.As (innerPat, _, _) ->
      match go innerPat with
      | [_] ->
        [pat]
      | _ ->
        failwith "Unimpl: Can't use AS patterns conjunction with OR patterns"
    | HPat.Anno (pat, annoTy, loc) ->
      go pat |> List.map
        (fun pat -> HPat.Anno (pat, annoTy, loc))
    | HPat.Or (first, second, _, _) ->
      List.append (go first) (go second)
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
  HExpr.Inf (InfOp.Semi, items, exprToTy (List.last items), loc)

let hxCallProc callee args resultTy loc =
  HExpr.Inf (InfOp.CallProc, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HExpr.Inf (InfOp.CallClosure, callee :: args, resultTy, loc)

let hxTuple items loc =
  HExpr.Inf (InfOp.Tuple, items, tyTuple (List.map exprToTy items), loc)

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
        arms |> List.map (fun (pat, guard, body) ->
          goPat pat, go guard, go body)
      HExpr.Match (go target, arms, f ty, g a)
    | HExpr.Nav (sub, mes, ty, a) ->
      HExpr.Nav (go sub, mes, f ty, g a)
    | HExpr.Inf (infOp, args, resultTy, a) ->
      HExpr.Inf (infOp, List.map go args, f resultTy, g a)
    | HExpr.Let (pat, init, next, ty, a) ->
      HExpr.Let (goPat pat, go init, go next, f ty, g a)
    | HExpr.LetFun (serial, isMainFun, args, body, next, ty, a) ->
      HExpr.LetFun (serial, isMainFun, List.map goPat args, go body, go next, f ty, g a)
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

// -----------------------------------------------
// Binary Operators (MIR)
// -----------------------------------------------

let opIsComparison op =
  match op with
  | MOp.Eq
  | MOp.Lt ->
    true
  | _ ->
    false

// -----------------------------------------------
// Expressions (MIR)
// -----------------------------------------------

let mxNot expr loc =
  MExpr.Uni (MUniOp.Not, expr, tyBool, loc)

let mexprExtract expr =
  match expr with
  | MExpr.Default (ty, loc) -> ty, loc
  | MExpr.Lit (lit, loc) -> litToTy lit, loc
  | MExpr.Ref (_, ty, loc) -> ty, loc
  | MExpr.Proc (_, ty, loc) -> ty, loc
  | MExpr.Variant (_, _, ty, loc) -> ty, loc
  | MExpr.Uni (_, _, ty, loc) -> ty, loc
  | MExpr.Bin (_, _, _, ty, loc) -> ty, loc

let mexprToTy expr =
  let ty, _ = mexprExtract expr
  ty

// -----------------------------------------------
// Statements (MIR)
// -----------------------------------------------

let msGotoUnless pred label loc =
  let notPred = mxNot pred loc
  MStmt.GotoIf (notPred, label, loc)

// -----------------------------------------------
// Expression sugaring (MIR)
// -----------------------------------------------

let rec mxSugar expr =
  let mxSugarUni op l ty loc =
    match l with
    // SUGAR: `not true` ==> `false`
    // SUGAR: `not false` ==> `true`
    | MExpr.Lit (Lit.Bool value, loc) ->
      MExpr.Lit (Lit.Bool (not value), loc)

    // SUGAR: `not (not x)` ==> `x`
    | MExpr.Uni (MUniOp.Not, l, _, _) ->
      l

    // SUGAR: `not (x = y)` ==> `x <> y`
    | MExpr.Bin (MOp.Eq, l, r, ty, loc) ->
      MExpr.Bin (MOp.Ne, l, r, ty, loc)

    // SUGAR: `not (x <> y)` ==> `x = y`
    | MExpr.Bin (MOp.Ne, l, r, ty, loc) ->
      MExpr.Bin (MOp.Eq, l, r, ty, loc)

    // SUGAR: `not (x < y)` ==> `x >= y`
    | MExpr.Bin (MOp.Lt, l, r, ty, loc) ->
      MExpr.Bin (MOp.Ge, l, r, ty, loc)

    // SUGAR: `not (x >= y)` ==> `x < y`
    | MExpr.Bin (MOp.Ge, l, r, ty, loc) ->
      MExpr.Bin (MOp.Lt, l, r, ty, loc)

    | _ ->
      MExpr.Uni (op, l, ty, loc)

  let mxSugarBin op l r ty loc =
    match op, l, r with
    // SUGAR: `x = false` ==> `not x`
    | MOp.Eq, MExpr.Lit (Lit.Bool false, _), _ ->
      mxSugarUni MUniOp.Not r ty loc

    | MOp.Eq, _, MExpr.Lit (Lit.Bool false, _) ->
      mxSugarUni MUniOp.Not l ty loc

    // SUGAR: `x = true` ==> `x`
    | MOp.Eq, MExpr.Lit (Lit.Bool true, _), _ ->
      r

    | MOp.Eq, _, MExpr.Lit (Lit.Bool true, _) ->
      l

    | _ ->
      MExpr.Bin (op, l, r, ty, loc)

  match expr with
  // SUGAR: `x: unit` ==> `()`
  | MExpr.Ref (_, Ty.Con (TyCon.Tuple, []), loc) ->
    MExpr.Default (tyUnit, loc)

  | MExpr.Uni (op, l, ty, loc) ->
    let l = mxSugar l
    mxSugarUni op l ty loc

  | MExpr.Bin (op, l, r, ty, loc) ->
    let l = mxSugar l
    let r = mxSugar r
    mxSugarBin op l r ty loc

  | _ ->
    expr

// -----------------------------------------------
// Print Formats
// -----------------------------------------------

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      tyUnit
    else
      if i + 1 < format.Length && format.[i] = '%' then
        match format.[i + 1] with
        | 's' ->
          tyFun tyStr (go (i + 2))
        | 'd' ->
          tyFun tyInt (go (i + 2))
        | 'c' ->
          tyFun  tyChar (go (i + 2))
        | _ ->
          go (i + 2)
      else
        go (i + 1)
  tyFun tyStr (go 0)

// -----------------------------------------------
// Type inference algorithm (HIR)
// -----------------------------------------------

/// Adds type-var/type binding.
let typingBind (ctx: TyContext) tySerial ty loc =
  // FIXME: track identifier
  let noIdent = "unknown"

  // Don't bind itself.
  match typingSubst ctx ty with
  | Ty.Meta (s, _) when s = tySerial -> ctx
  | _ ->

  // Update depth of all related meta types to the minimum.
  let tyDepths =
    let tySerials = tySerial :: tyCollectFreeVars ty
    let depth =
      tySerials
      |> List.map (fun tySerial -> ctx.TyDepths |> Map.find tySerial)
      |> List.min
    tySerials |> List.fold (fun tyDepths tySerial -> tyDepths |> Map.add tySerial depth) ctx.TyDepths

  { ctx with
      Tys = ctx.Tys |> Map.add tySerial (TyDef.Meta (noIdent, ty, loc))
      TyDepths = tyDepths
  }

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let typingSubst (ctx: TyContext) ty: Ty =
  let substMeta tySerial =
    match ctx.Tys |> Map.tryFind tySerial with
    | Some (TyDef.Meta (_, ty, _)) ->
      Some ty
    | _ ->
      None

  tySubst substMeta ty

/// Solves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let typingUnify logAcc (ctx: TyContext) (lty: Ty) (rty: Ty) (loc: Loc) =
  let lRootTy, rRootTy = lty, rty

  let addLog kind lTy rTy logAcc ctx =
    let lRootTy = typingSubst ctx lRootTy
    let rRootTy = typingSubst ctx rRootTy
    (Log.TyUnify (kind, lRootTy, rRootTy, lTy, rTy), loc) :: logAcc, ctx

  let rec go lty rty (logAcc, ctx) =
    let lSubstTy = typingSubst ctx lty
    let rSubstTy = typingSubst ctx rty
    match lSubstTy, rSubstTy with
    | Ty.Meta (l, _), Ty.Meta (r, _) when l = r ->
      logAcc, ctx
    | Ty.Meta (lSerial, loc), _ when tyIsFreeIn rSubstTy lSerial ->
      let ctx = typingBind ctx lSerial rty loc
      logAcc, ctx
    | _, Ty.Meta _ ->
      go rty lty (logAcc, ctx)
    | Ty.Con (lTyCon, []), Ty.Con (rTyCon, []) when lTyCon = rTyCon ->
      logAcc, ctx
    | Ty.Con (lTyCon, lTy :: lTys), Ty.Con (rTyCon, rTy :: rTys) ->
      (logAcc, ctx) |> go lTy rTy |> go (Ty.Con (lTyCon, lTys)) (Ty.Con (rTyCon, rTys))
    | Ty.Error _, _
    | _, Ty.Error _ ->
      logAcc, ctx
    | Ty.Meta _, _ ->
      addLog TyUnifyLog.SelfRec lSubstTy rSubstTy logAcc ctx
    | Ty.Con _, _ ->
      addLog TyUnifyLog.Mismatch lSubstTy rSubstTy logAcc ctx

  go lty rty (logAcc, ctx)

let typingResolveTraitBound logAcc (ctx: TyContext) theTrait loc =
  let theTrait = theTrait |>  traitMapTys (typingSubst ctx)

  let expectScalar ty (logAcc, ctx) =
    match ty with
    | Ty.Error _
    | Ty.Con (TyCon.Bool, [])
    | Ty.Con (TyCon.Int, [])
    | Ty.Con (TyCon.Char, [])
    | Ty.Con (TyCon.Str, []) ->
      logAcc, ctx

    | _ ->
      (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  match theTrait with
  | Trait.Add ty ->
    match ty with
    | Ty.Error _
    | Ty.Con (TyCon.Str, []) ->
      logAcc, ctx

    | _ ->
      // Coerce to int by default.
      typingUnify logAcc ctx ty tyInt loc

  | Trait.Eq ty ->
    (logAcc, ctx) |> expectScalar ty

  | Trait.Cmp ty ->
    (logAcc, ctx) |> expectScalar ty

  | Trait.Index (lTy, rTy, resultTy) ->
    match lTy with
    | Ty.Error _ ->
      [], ctx

    | Ty.Con (TyCon.Str, []) ->
      let logAcc, ctx = typingUnify logAcc ctx rTy tyInt loc
      let logAcc, ctx = typingUnify logAcc ctx resultTy tyChar loc
      logAcc, ctx

    | _ ->
      (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | Trait.ToInt ty ->
    (logAcc, ctx) |> expectScalar ty

  | Trait.ToString ty ->
    (logAcc, ctx) |> expectScalar ty

// -----------------------------------------------
// Logs
// -----------------------------------------------

let logToString loc log =
  let loc =
    let y, x = loc
    sprintf "%d:%d" (y + 1) (x + 1)

  match log with
  | Log.TyUnify (TyUnifyLog.SelfRec, _, _, lTy, rTy) ->
    sprintf "%s Couldn't unify '%A' and '%A' due to self recursion." loc lTy rTy

  | Log.TyUnify (TyUnifyLog.Mismatch, lRootTy, rRootTy, lTy, rTy) ->
    sprintf "%s While unifying '%A' and '%A', failed to unify '%A' and '%A'." loc lRootTy rRootTy lTy rTy

  | Log.TyBoundError (Trait.Add ty) ->
    sprintf "%s No support (+) for '%A' yet" loc ty

  | Log.TyBoundError (Trait.Eq ty) ->
    sprintf "%s No support equality for '%A' yet" loc ty

  | Log.TyBoundError (Trait.Cmp ty) ->
    sprintf "%s No support comparison for '%A' yet" loc ty

  | Log.TyBoundError (Trait.Index (lTy, rTy, _)) ->
    sprintf "%s No support indexing operation (l = '%A', r = '%A')" loc lTy rTy

  | Log.TyBoundError (Trait.ToInt ty) ->
    sprintf "%s Can't convert to int from '%A'" loc ty

  | Log.TyBoundError (Trait.ToString ty) ->
    sprintf "%s Can't convert to string from '%A'" loc ty

  | Log.Error msg ->
    sprintf "%s %s" loc msg
