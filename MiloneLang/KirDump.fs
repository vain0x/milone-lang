/// # KirDump
///
/// Converts KIR to TypeScript-like code for debugging.
/// Generated code doesn't compile nor run.

module rec MiloneLang.KirDump

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers
open MiloneLang.TySystem

let private deeper indent = indent + "    "

let private getVarName varSerial ctx =
  match ctx |> kirGenCtxGetVars |> mapTryFind varSerial with
  | None -> "UNDEFINED_VAR_" + string varSerial
  | Some varDef -> varDefToIdent varDef + "_" + string varSerial

let private getTyName tySerial ctx =
  match ctx |> kirGenCtxGetTys |> mapTryFind tySerial with
  | None -> "UNDEFINED_TY_" + string tySerial
  | Some tyDef -> tyDefToIdent tyDef

let private kdPath path ctx =
  match path with
  | KSelfPath -> ""
  | KHeadPath _ -> ".head"
  | KTailPath _ -> ".tail"
  | KFieldPath (i, _) -> "[" + string i + "]"
  | KTagPath _ -> ".tag"
  | KPayloadPath (variantSerial, _) -> "." + getVarName variantSerial ctx

let private litToDebugString lit =
  match lit with
  | BoolLit false -> "false"
  | BoolLit true -> "true"
  | IntLit value -> string value
  | CharLit value -> "'" + charEscape value + "'"
  | StrLit value -> "\"" + strEscape value + "\""

let private tsConstStmt indent pat init =
  indent + "const " + pat + " = " + init + "\n"

// -----------------------------------------------
// ty
// -----------------------------------------------

let private tyCtorToDebugString tyCtor ctx =
  tyCtor
  |> tyCtorDisplay (fun tySerial -> getTyName tySerial ctx)

let private tyToDebugString ty ctx =
  match ty with
  | ErrorTy loc -> "/* ERROR @" + locToString loc + " */ any"

  | MetaTy (tySerial, loc) ->
      "/* ?"
      + string tySerial
      + " @"
      + locToString loc
      + "*/ any"

  | AppTy (tyCtor, args) ->
      match tyCtor, args with
      | FunTyCtor, [ sTy; tTy ] ->
          "(_: "
          + tyToDebugString sTy ctx
          + ") => "
          + tyToDebugString tTy ctx

      | TupleTyCtor, [] -> "unit"

      | TupleTyCtor, _ ->
          "["
          + strConcat
              (args
               |> listMapWithIndex (fun i ty ->
                    (if i = 0 then "" else ", ")
                    + tyToDebugString ty ctx))
          + "]"

      | ListTyCtor, [ itemTy ] -> "Array<" + tyToDebugString itemTy ctx + ">"

      | _, [] -> tyCtorToDebugString tyCtor ctx

      | _ ->
          tyCtorToDebugString tyCtor ctx
          + "<"
          + strConcat
              (args
               |> listMapWithIndex (fun i ty ->
                    (if i = 0 then "" else ", ")
                    + tyToDebugString ty ctx))
          + ">"

let private kdVarAsTy varSerial ctx =
  match ctx |> kirGenCtxGetVars |> mapTryFind varSerial with
  | None -> "/* ?" + string varSerial + " */ unknown"

  | Some (VarDef (_, _, ty, _))
  | Some (FunDef (_, _, TyScheme (_, ty), _))
  | Some (VariantDef (_, _, _, _, ty, _)) -> tyToDebugString ty ctx

// -----------------------------------------------
// term
// -----------------------------------------------

let private kdTerm term ctx =
  match term with
  | KLitTerm (lit, _) -> lit |> litToDebugString

  | KVarTerm (varSerial, _, _)
  | KFunTerm (varSerial, _, _)
  | KVariantTerm (varSerial, _, _)
  | KLabelTerm (varSerial, _, _) -> getVarName varSerial ctx

  | KTagTerm (variantSerial, _) -> getVarName variantSerial ctx + ".tag"

  | KNilTerm _ -> "[]"
  | KNoneTerm _ -> "None"
  | KUnitTerm _ -> "Unit"

let private kdArgsAsParamList args ctx =
  "("
  + (args
     |> listMapWithIndex (fun i arg ->
          (if i = 0 then "" else ", ")
          + getVarName arg ctx
          + ": "
          + kdVarAsTy arg ctx)
     |> strConcat)
  + ")"

let private kdTermsAsArgList args ctx =
  "("
  + (args
     |> listMapWithIndex (fun i arg -> (if i = 0 then "" else ", ") + kdTerm arg ctx)
     |> strConcat)
  + ")"

// -----------------------------------------------
// prim
// -----------------------------------------------

let private kdPrim prim =
  match prim with
  | KAddPrim -> "Add"
  | KSubPrim -> "Sub"
  | KMulPrim -> "Mul"
  | KDivPrim -> "Div"
  | KModPrim -> "Mod"
  | KEqualPrim -> "Equal"
  | KLessPrim -> "Less"
  | KNotPrim -> "Not"
  | KStrAddPrim -> "StrAdd"
  | KStrComparePrim -> "StrCompare"
  | KStrIndexPrim -> "StrIndex"
  | KStrLengthPrim -> "StrLength"
  | KStrGetSlicePrim -> "StrGetSlice"
  | KConsPrim -> "Cons"
  | KSomePrim -> "Some"
  | KTuplePrim -> "Tuple"
  | KVariantPrim -> "Variant"
  | KClosurePrim -> "Closure"
  | KCallProcPrim -> "CallProc"
  | KCallClosurePrim -> "CallClosure"
  | KBoxPrim -> "Box"
  | KUnboxPrim -> "Unbox"
  | KExitPrim -> "Exit"
  | KAssertPrim -> "Assert"
  | KCharPrim -> "Char"
  | KIntPrim -> "Int"
  | KUIntPrim -> "UInt"
  | KStringPrim -> "String"
  | KPrintfnPrim -> "Printfn"
  | KInRegionPrim -> "InRegion"
  | KNativeFunPrim (ident, arity) -> ident + "/" + string arity

let private kdPrimNode indent prim args results conts ctx =
  // basic prim operation. compute an expression and bind the result to a var, and then continue.
  let basic init result cont =
    tsConstStmt indent (getVarName result ctx) init
    + kdNode indent cont ctx

  let prefix op arg = basic (op + kdTerm arg ctx)

  let binary op l r =
    basic (kdTerm l ctx + " " + op + " " + kdTerm r ctx)

  let call callee args =
    basic (callee + kdTermsAsArgList args ctx)

  // property
  let prop dotName arg = basic (kdTerm arg ctx + dotName)

  let index l r =
    basic (kdTerm l ctx + "[" + kdTerm r ctx + "]")

  let methodCall dotName l args =
    basic (kdTerm l ctx + dotName + kdTermsAsArgList args ctx)

  // conditional branching
  let br op l r thenCl elseCl =
    (indent
     + "if (!("
     + (kdTerm l ctx + " " + op + " " + kdTerm r ctx)
     + ")) {\n")
    + kdNode (deeper indent) elseCl ctx
    + (indent + "}\n\n")
    + kdNode indent thenCl ctx

  let other () =
    let argList = kdTermsAsArgList args ctx

    let resultList =
      results
      |> listMapWithIndex (fun i result ->
           (if i = 0 then "" else ", ")
           + getVarName result ctx)
      |> strConcat

    match conts with
    | [] -> indent + "throw " + kdPrim prim + argList + "\n"

    | [ cont ] ->
        tsConstStmt indent ("[" + resultList + "]") (kdPrim prim + argList)
        + kdNode indent cont ctx

    | _ ->
        tsConstStmt indent ("[" + resultList + "]") (kdPrim prim + argList)
        + (conts
           |> listMapWithIndex (fun (i: int) cont ->
                (indent
                 + "// "
                 + (kdPrim prim + ".cont#" + string i)
                 + "\n")
                + (indent + "{\n")
                + kdNode (deeper indent) cont ctx
                + (indent + "}\n"))
           |> strConcat)

  match prim, args, results, conts with
  | KAddPrim, [ l; r ], [ result ], [ cont ] -> binary "+" l r result cont
  | KSubPrim, [ l; r ], [ result ], [ cont ] -> binary "-" l r result cont
  | KMulPrim, [ l; r ], [ result ], [ cont ] -> binary "*" l r result cont
  | KDivPrim, [ l; r ], [ result ], [ cont ] -> binary "/" l r result cont
  | KModPrim, [ l; r ], [ result ], [ cont ] -> binary "%" l r result cont

  | KEqualPrim, [ l; r ], [], [ thenCl; elseCl ] -> br "===" l r thenCl elseCl
  | KLessPrim, [ l; r ], [], [ thenCl; elseCl ] -> br "<" l r thenCl elseCl

  | KNotPrim, [ arg ], [ result ], [ cont ] -> prefix "!" arg result cont

  | KStrAddPrim, [ l; r ], [ result ], [ cont ] -> methodCall ".concat" l [ r ] result cont
  | KStrComparePrim, [ l; r ], [ result ], [ cont ] -> methodCall ".compare" l [ r ] result cont
  | KStrIndexPrim, [ l; r ], [ result ], [ cont ] -> index l r result cont
  | KStrLengthPrim, [ arg ], [ result ], [ cont ] -> prop ".length" arg result cont
  | KStrGetSlicePrim, [ l; r; s ], [ result ], [ cont ] -> methodCall ".slice" s [ l; r ] result cont

  | KConsPrim, [ l; r ], [ result ], [ cont ] -> basic ("[" + kdTerm l ctx + ", ..." + kdTerm r ctx + "]") result cont

  | KSomePrim, [ arg ], [ result ], [ cont ] -> call "Some" [ arg ] result cont

  | KTuplePrim, [], [ result ], [ cont ] -> basic "Unit" result cont
  | KTuplePrim, _, [ result ], [ cont ] ->
      basic
        ("["
         + (args
            |> listMapWithIndex (fun i arg -> (if i = 0 then "" else ", ") + kdTerm arg ctx)
            |> strConcat)
         + "]")
        result
        cont

  | KCallProcPrim, callee :: args, [ result ], [ cont ] ->
      basic (kdTerm callee ctx + kdTermsAsArgList args ctx) result cont

  | KCallClosurePrim, callee :: args, [ result ], [ cont ] ->
      basic
        (kdTerm callee ctx
         + ".call"
         + kdTermsAsArgList args ctx)
        result
        cont

  | _ -> other ()

// -----------------------------------------------
// node
// -----------------------------------------------

let private kdNode indent node ctx =
  match node with
  | KJumpNode (jointSerial, args, loc) ->
      (indent + "// " + locToString loc + "\n")
      + (indent
         + "return "
         + getVarName jointSerial ctx
         + kdTermsAsArgList args ctx
         + "\n")

  | KReturnNode (_funSerial, [], _) -> indent + "return\n"

  | KReturnNode (_funSerial, [ arg ], _) -> indent + "return " + kdTerm arg ctx + "\n"

  | KReturnNode (_funSerial, args, _) ->
      // unlikely happen
      indent
      + "return "
      + kdTermsAsArgList args ctx
      + "\n"

  | KSelectNode (term, path, result, cont, _) ->
      tsConstStmt indent (getVarName result ctx) (kdTerm term ctx + kdPath path ctx)
      + kdNode indent cont ctx

  | KPrimNode (prim, args, results, conts, _) -> kdPrimNode indent prim args results conts ctx

  | KJointNode ([], cont, _) -> kdNode indent cont ctx

  | KJointNode (joints, cont, _) ->
      kdNode indent cont ctx
      + (joints
         |> List.map (fun joint -> kdJointBinding indent false joint ctx)
         |> strConcat)

let private kdJointBinding indent isEntryPoint jointBinding ctx =
  let (KJointBinding (jointSerial, args, body, loc)) = jointBinding

  if isEntryPoint then
    kdNode indent body ctx
  else
    "\n"
    + (indent + "// @" + locToString loc + "\n")
    + (indent
       + "function "
       + getVarName jointSerial ctx
       + kdArgsAsParamList args ctx
       + " {\n")
    + kdNode (deeper indent) body ctx
    + (indent + "}\n")

let private kdFunBinding indent funBinding ctx =
  let (KFunBinding (funSerial, args, body, loc)) = funBinding

  let isEntryPoint i = i = 0

  "\n"
  + (indent + "// @" + locToString loc + "\n")
  + (indent
     + "const "
     + getVarName funSerial ctx
     + " = "
     + kdArgsAsParamList args ctx
     + " => {\n")
  + kdNode (deeper indent) body ctx
  + ("}\n")

let kirHeader () = """
type unit = undefined
type bool = boolean
type int = number
type char = string
type obj = unknown

declare const Unit: unit
declare const Some: <T>(_: T) => [T]
declare const None: never[]
declare const Box: (_: unknown) => unknown
declare const Unbox: (_: unknown) => any
declare const Exit: (code: number) => never
declare const Assert: (cond: boolean) => void
declare const Char: (value: unknown) => char
declare const Int: (value: unknown) => int
declare const Printfn: (fmt: string, ...args: unknown[]) => void
declare const InRegion: <T>(f: (_: unit) => T) => T
"""

let kirDump hint indent (kRoot: KRoot, ctx: KirGenCtx): string =
  let (KRoot funBindings) = kRoot

  "// "
  + hint
  + "\n"
  + (funBindings
     |> List.map (fun funBinding -> kdFunBinding indent funBinding ctx)
     |> strConcat)
