/// Defines the functions used in multiple modules.
module rec MiloneLang.Helpers

open MiloneLang.Types

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

/// `listMap`, modifying context.
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
  NameCtx ([], 0)

let nameCtxAdd ident (NameCtx (map, serial)) =
  let serial = serial + 1
  // let map = map |> Map.add serial ident
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

  | "list", [itemTy] ->
    tyList itemTy

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
  HExpr.Inf (InfOp.Semi, items, noTy, loc)

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
