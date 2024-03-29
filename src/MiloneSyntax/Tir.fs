/// # Tir
///
/// Provides functions for Tir.
module rec MiloneSyntax.Tir

open Std.StdError
open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open Std.StdMap
open MiloneSyntax.TirTypes

module S = Std.StdString

// -----------------------------------------------
// Ty
// -----------------------------------------------

let tyError loc = Ty(ErrorTk loc, [])

let tyInt = Ty(IntTk I32, [])
let tyByte = Ty(IntTk U8, [])
let tyNativeInt = Ty(IntTk IPtr, [])
let tyUNativeInt = Ty(IntTk UPtr, [])
let tyFloat = Ty(FloatTk F64, [])
let tyBool = Ty(BoolTk, [])
let tyChar = Ty(CharTk, [])
let tyString = Ty(StringTk, [])
let tyNever = Ty(NeverTk, [])
let tyObj = Ty(ObjTk, [])

let tyFun sourceTy targetTy = Ty(FunTk, [ sourceTy; targetTy ])
let tyList itemTy = Ty(ListTk, [ itemTy ])
let tyTuple itemTys = Ty(TupleTk, itemTys)
let tyUnit = tyTuple []

let tyOwn itemTy = Ty(OwnTk, [ itemTy ])
let tyVoidInPtr = Ty(VoidPtrTk IsConst, [])
let tyVoidPtr = Ty(VoidPtrTk IsMut, [])

let tyNativePtr itemTy =
  Ty(NativePtrTk RefMode.ReadWrite, [ itemTy ])

let tyInPtr itemTy =
  Ty(NativePtrTk RefMode.ReadOnly, [ itemTy ])

let tyOutPtr itemTy =
  Ty(NativePtrTk RefMode.WriteOnly, [ itemTy ])

let tyNativeFun paramTys resultTy =
  Ty(FunPtrTk, List.append paramTys [ resultTy ])

let tyUniv serial info = Ty(UnivTk(serial, info), [])
let tyMeta serial loc = Ty(MetaTk(serial, loc), [])
let tySynonym tySerial tyArgs info = Ty(SynonymTk(tySerial, info), tyArgs)
let tyUnion tySerial tyArgs info = Ty(UnionTk(tySerial, info), tyArgs)
let tyRecord tySerial tyArgs info = Ty(RecordTk(tySerial, info), tyArgs)

/// Converts meta type constructor to name.
let debugMetaTk (tySerial: TySerial) (loc: Loc) : string =
  // __trace ("def meta#" + string tySerial + " @" + Loc.toString loc)
  "?" + string tySerial

// -----------------------------------------------
// TyDef
// -----------------------------------------------

let tyDefToName tyDef =
  match tyDef with
  | UnivTyDef(name, _) -> name
  | SynonymTyDef(name, _, _, _) -> name
  | UnionTyDef(name, _, _, _) -> name
  | RecordTyDef(name, _, _, _, _) -> name
  | OpaqueTyDef(name, _) -> name

// -----------------------------------------------
// VarDef
// -----------------------------------------------

let varSerialToInt (VarSerial serial) = serial

let varSerialCompare l r =
  compare (varSerialToInt l) (varSerialToInt r)

let funSerialToInt (FunSerial serial) = serial

let funSerialCompare l r =
  compare (funSerialToInt l) (funSerialToInt r)

let variantSerialToInt (VariantSerial serial) = serial

let variantSerialCompare l r =
  compare (variantSerialToInt l) (variantSerialToInt r)

// -----------------------------------------------
// Lit
// -----------------------------------------------

let litToTy (lit: Lit) : Ty =
  match lit with
  | BoolLit _ -> tyBool
  | IntLit _ -> tyInt
  | IntLitWithFlavor(_, flavor) -> Ty(IntTk flavor, [])
  | FloatLit _ -> tyFloat
  | CharLit _ -> tyChar
  | ByteLit _ -> tyByte
  | StringLit _ -> tyString

// -----------------------------------------------
// TPat
// -----------------------------------------------

let tpAbort ty loc = TNodePat(TAbortPN, [], ty, loc)

let patExtract (pat: TPat) : Ty * Loc =
  match pat with
  | TLitPat(lit, a) -> litToTy lit, a
  | TDiscardPat(ty, a) -> ty, a
  | TVarPat(_, _, ty, a) -> ty, a
  | TVariantPat(_, ty, a) -> ty, a

  | TNodePat(_, _, ty, a) -> ty, a
  | TAsPat(bodyPat, _, a) -> patToTy bodyPat, a
  | TOrPat(l, _, a) -> patToTy l, a

let patToTy pat = pat |> patExtract |> fst

let patToLoc pat = pat |> patExtract |> snd

let patMap (f: Ty -> Ty) (pat: TPat) : TPat =
  let rec go pat =
    match pat with
    | TLitPat(lit, a) -> TLitPat(lit, a)
    | TDiscardPat(ty, a) -> TDiscardPat(f ty, a)
    | TVarPat(vis, serial, ty, a) -> TVarPat(vis, serial, f ty, a)
    | TVariantPat(serial, ty, a) -> TVariantPat(serial, f ty, a)

    | TNodePat(kind, args, ty, a) -> TNodePat(kind, List.map go args, f ty, a)
    | TAsPat(bodyPat, serial, a) -> TAsPat(go bodyPat, serial, a)
    | TOrPat(l, r, a) -> TOrPat(go l, go r, a)

  go pat

/// Folds all variables in a pattern. This skips right-hand side of OR patterns.
let patFoldVars (folder: 'S -> VarSerial * Loc -> 'S) (state: 'S) (pat: TPat) : 'S =
  let rec patRec state pat =
    match pat with
    | TLitPat _
    | TDiscardPat _
    | TVariantPat _ -> state

    | TVarPat(_, varSerial, _, loc) -> folder state (varSerial, loc)
    | TAsPat(argPat, varSerial, loc) -> folder (patRec state argPat) (varSerial, loc)
    | TNodePat(_, argPats, _, _) -> List.fold patRec state argPats
    | TOrPat(lPat, _, _) -> patRec state lPat

  patRec state pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | TLitPat _
    | TDiscardPat _
    | TVarPat _
    | TVariantPat _ -> [ pat ]

    | TNodePat(kind, argPats, ty, loc) ->
      argPats
      |> doNormalizePats
      |> List.map (fun itemPats -> TNodePat(kind, itemPats, ty, loc))

    | TAsPat(bodyPat, serial, loc) -> go bodyPat |> List.map (fun bodyPat -> TAsPat(bodyPat, serial, loc))

    | TOrPat(l, r, _) -> List.append (go l) (go r)

  go pat

let private doNormalizePats pats =
  match pats with
  | [] -> [ [] ]

  | headPat :: tailPats ->
    let headPats = patNormalize headPat

    doNormalizePats tailPats
    |> List.collect (fun tailPats -> headPats |> List.map (fun headPat -> headPat :: tailPats))

/// Gets whether a pattern is clearly exhaustive, that is,
/// pattern matching on it always succeeds (assuming type check is passing).
let patIsClearlyExhaustive isNewtypeVariant pat =
  let rec go pat =
    match pat with
    | TLitPat _ -> false

    | TDiscardPat _
    | TVarPat _ -> true

    | TVariantPat(variantSerial, _, _) -> isNewtypeVariant variantSerial

    | TNodePat(kind, argPats, _, _) ->
      match kind, argPats with
      | TVariantAppPN variantSerial, [ payloadPat ] -> isNewtypeVariant variantSerial && go payloadPat

      | TAbortPN, _ -> true

      | TNilPN, _
      | TConsPN, _
      | TVariantAppPN _, _
      | TNavPN _, _ -> false

      | TTuplePN, _
      | TAscribePN, _ -> argPats |> List.forall go

    | TAsPat(bodyPat, _, _) -> go bodyPat
    | TOrPat(l, r, _) -> go l || go r

  go pat

// -----------------------------------------------
// TExpr
// -----------------------------------------------

let txLetIn stmt next = TBlockExpr([ stmt ], next)

let txTuple items loc =
  TNodeExpr(TTupleEN, items, tyTuple (List.map exprToTy items), loc)

let txUnit loc = txTuple [] loc

let exprExtract (expr: TExpr) : Ty * Loc =
  match expr with
  | TLitExpr(lit, a) -> litToTy lit, a
  | TVarExpr(_, ty, a) -> ty, a
  | TFunExpr(_, ty, a) -> ty, a
  | TVariantExpr(_, ty, a) -> ty, a
  | TPrimExpr(_, ty, a) -> ty, a
  | TRecordExpr(_, _, ty, a) -> ty, a
  | TMatchExpr(_, _, ty, a) -> ty, a
  | TNavExpr(_, _, ty, a) -> ty, a
  | TNodeExpr(_, _, ty, a) -> ty, a
  | TBlockExpr(_, last) -> exprExtract last

let exprMap (f: Ty -> Ty) (expr: TExpr) : TExpr =
  let goPat pat = patMap f pat

  let rec go expr =
    match expr with
    | TLitExpr(lit, a) -> TLitExpr(lit, a)
    | TVarExpr(serial, ty, a) -> TVarExpr(serial, f ty, a)
    | TFunExpr(serial, ty, a) -> TFunExpr(serial, f ty, a)
    | TVariantExpr(serial, ty, a) -> TVariantExpr(serial, f ty, a)
    | TPrimExpr(prim, ty, a) -> TPrimExpr(prim, f ty, a)

    | TRecordExpr(baseOpt, fields, ty, a) ->
      let baseOpt = baseOpt |> Option.map go

      let fields = fields |> List.map (fun (name, init, a) -> name, go init, a)

      TRecordExpr(baseOpt, fields, f ty, a)

    | TMatchExpr(cond, arms, ty, a) ->
      let arms = arms |> List.map (fun (pat, guard, body) -> goPat pat, go guard, go body)

      TMatchExpr(go cond, arms, f ty, a)
    | TNavExpr(sub, mes, ty, a) -> TNavExpr(go sub, mes, f ty, a)
    | TNodeExpr(kind, args, resultTy, a) -> TNodeExpr(kind, List.map go args, f resultTy, a)
    | TBlockExpr(stmts, last) -> TBlockExpr(List.map (stmtMap f) stmts, go last)

  go expr

let exprToTy expr = exprExtract expr |> fst

let exprToLoc expr = exprExtract expr |> snd

// -----------------------------------------------
// TStmt
// -----------------------------------------------

// let stmtToLoc (stmt: TStmt) : Loc =
//   match stmt with
//   | TExprStmt expr -> exprToLoc expr
//   | TLetValStmt (_, _, loc) -> loc
//   | TLetFunStmt (_, _, _, _, _, loc) -> loc

let stmtMap (onTy: Ty -> Ty) (stmt: TStmt) : TStmt =
  let onPat pat = patMap onTy pat
  let onPats pats = List.map (patMap onTy) pats
  let onExpr expr = exprMap onTy expr
  let onStmt stmt = stmtMap onTy stmt
  let onStmts stmts = List.map (stmtMap onTy) stmts

  match stmt with
  | TExprStmt expr -> TExprStmt(onExpr expr)
  | TLetValStmt(pat, init, loc) -> TLetValStmt(onPat pat, onExpr init, loc)
  | TLetFunStmt f -> TLetFunStmt { f with Params = onPats f.Params; Body = onExpr f.Body }
  | TBlockStmt(isRec, stmts) -> TBlockStmt(isRec, onStmts stmts)

// -----------------------------------------------
// TModule
// -----------------------------------------------

let emptyVars: TreeMap<VarSerial, VarDef> = TMap.empty varSerialCompare

// -----------------------------------------------
// TProgram
// ----------------------------------------------

module TProgram =
  let mapStmt (mapping: TStmt -> TStmt) (modules: TProgram) : TProgram =
    modules
    |> List.map (fun (m: TModule) -> { m with Stmts = m.Stmts |> List.map mapping })

  let foldStmt (folder: 'S -> TStmt -> 'S) (state: 'S) (modules: TProgram) : 'S =
    modules
    |> List.fold (fun state (m: TModule) -> m.Stmts |> List.fold folder state) state

// -----------------------------------------------
// Print Formats
// -----------------------------------------------

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      tyUnit
    else if i + 1 < format.Length && format.[i] = '%' then
      match format.[i + 1] with
      | 's' -> tyFun tyString (go (i + 2))
      | 'd' -> tyFun tyInt (go (i + 2))
      | 'f' -> tyFun tyFloat (go (i + 2))
      | 'c' -> tyFun tyChar (go (i + 2))
      | _ -> go (i + 2)
    else
      go (i + 1)

  tyFun tyString (go 0)

// -----------------------------------------------
// Logs
// -----------------------------------------------

let nameResLogToString log =
  match log with
  | UndefinedValueError name -> "The name '" + name + "' here should denote to some value; but not found."

  | TyUsedAsValueError -> "This is a type. A value is expected here."

  | UndefinedTyError name -> "The name '" + name + "' here should denote to some type; but not found."

  | VarNameConflictError -> "Variable name conflicts"

  | VariantAppPatArityError -> "Pattern can apply to a variant that takes a payload."

  | UnresolvedNavPatError -> "Couldn't resolve nav pattern."

  | IllegalOrPatError -> "OR pattern is disallowed in let expressions."

  | OrPatInconsistentBindingError -> "OR pattern binds different set of variables"

  | TyArityError("_", _, _) -> "'_' can't have type arguments."

  | TyArityError(name, actual, expected) ->
    "Type arity mismatch. The type '"
    + name
    + "' expected "
    + string expected
    + " arguments; but given "
    + string actual
    + "."

  | ModuleUsedAsTyError name -> "The name '" + name + "' here should denote to some type; but is a module name."

  | ModulePathNotFoundError -> "Module not found for this path"

  | UnimplOrPatBindingError -> "OR pattern including some bindings is unimplemented."
  | UnimplTyArgListError -> "Type argument list is unimplemented."

let private traitBoundErrorToString tyDisplay (t: Trait) =
  match t with
  | Trait.Unary(unary, ty) ->
    let message =
      match unary with
      | UnaryTrait.Add -> "Operator (+) is not supported for the type"
      | UnaryTrait.Equal -> "Operator (=) is not supported for the type"
      | UnaryTrait.Compare -> "The compare function is not supported for the type"
      | UnaryTrait.IntLike -> "Expected int or some integer type but was"
      | UnaryTrait.NumberLike -> "Expected int, float or some number type but was"
      | UnaryTrait.ToInt flavor -> ("Cannot convert to " + fsharpIntegerTyName flavor + " from")
      | UnaryTrait.ToFloat -> "Cannot convert to float type from"
      | UnaryTrait.ToChar -> "Cannot convert to char type from"
      | UnaryTrait.ToString -> "Cannot convert to string type from"
      | UnaryTrait.PtrLike -> "Expected a pointer type but was"
      | UnaryTrait.PtrSize -> "Expected a pointer-sized type but was"

    message + ": " + tyDisplay ty

  | Trait.Index(lTy, rTy, _) ->
    "Index expression (say, l.[r]) is not supported for the combination of types (lhs: "
    + tyDisplay lTy
    + ", rhs: "
    + tyDisplay rTy
    + ".)"

  | Trait.PtrCast(lTy, rTy) ->
    "Pointer cast operation is not allowed between the two types (from: "
    + tyDisplay lTy
    + ", to: "
    + tyDisplay rTy
    + ".)"

let logToString tyDisplay log =
  match log with
  | Log.NameResLog log -> nameResLogToString log

  | Log.LiteralRangeError -> "This type of literal can't represent the value."

  | Log.IrrefutablePatNonExhaustiveError ->
    "Let expressions cannot contain refutable patterns, which could fail to match for now."

  | Log.TyUnify(TyUnifyLog.SelfRec, lTy, rTy) ->
    "Recursive type occurred while unifying '"
    + tyDisplay lTy
    + "' to '"
    + tyDisplay rTy
    + "'."

  | Log.TyUnify(TyUnifyLog.Mismatch, lTy, rTy) -> "Type mismatch: '" + tyDisplay lTy + "' <> '" + tyDisplay rTy + "'."

  | Log.TyBoundError it -> traitBoundErrorToString tyDisplay it

  | Log.TySynonymCycleError -> "Cyclic type synonym is forbidden."

  | Log.RedundantFieldError(recordName, fieldName) ->
    "The field '" + fieldName + "' is redundant for record '" + recordName + "'."

  | Log.MissingFieldsError(recordName, fieldNames) ->
    let fields = fieldNames |> S.concat ", "

    "Record '" + recordName + "' must have fields: " + fields

  | Log.RecordTypeNotInferred ->
    "Record type is not inferred. Record type must be known at the point. Hint: Consider add a type ascription."

  | Log.RecordFieldNotFound(field, ty) -> "Field " + tyDisplay ty + "." + field + " is not found here."

  | Log.FieldNotFound field -> "Field " + field + " is not found here."

  | Log.MissingPayloadPat -> "Variant with payload must be used in the form of: `Variant pattern`."

  | Log.ArityMismatch(actual, expected) -> "Arity mismatch: expected " + expected + ", but was " + actual + "."

  | Log.UseOfDiscriminant -> "Illegal use of __discriminant. Hint: `__discriminant Variant`."
  | Log.UseOfPrintfn ->
    "Illegal use of printfn. printfn must have string literal as first argument; e.g. `printfn \"%s\" s`."
  | Log.UseOfNativeFun -> "Illegal use of __nativeFun. Hint: `__nativeFun (\"funName\", arg1, arg2, ...): ResultType`."
  | Log.UseOfNativeExpr -> "Illegal use of __nativeExpr. Hint: `__nativeExpr \"Some C code here.\"`."
  | Log.UseOfNativeStmt -> "Illegal use of __nativeStmt. Hint: `__nativeStmt \"Some C code here.\"`."
  | Log.UseOfNativeDecl -> "Illegal use of __nativeDecl. Hint: `__nativeDecl \"Some C code here.\"`."
  | Log.PrimRequireParam -> "This primitive misses some argument."

  | Log.Error msg -> msg
