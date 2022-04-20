/// # CirDump
///
/// Converts CIR to C language source code.
module rec MiloneTranslation.CirDump

open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open Std.StdError
open MiloneTranslation.Cir

module C = Std.StdChar
module S = Std.StdString
module SB = Std.StdStringBase

let private eol = "\n"

let private deeper (indent: string) = "    " + indent

let private join sep xs f acc =
  let rec go xs acc =
    match xs with
    | [] -> acc
    | [ x ] -> acc |> f x
    | x :: xs -> acc |> f x |> cons sep |> go xs

  go xs acc

[<NoEquality; NoComparison>]
type private First =
  | First
  | NotFirst

let private isFirst first =
  match first with
  | First -> true
  | NotFirst -> false

let private declIsForwardOnly decl =
  match decl with
  | CFunPtrTyDef _
  | CStructForwardDecl _
  | CFunForwardDecl _ -> true
  | _ -> false

// -----------------------------------------------
// Operators
// -----------------------------------------------

let private unaryToString op =
  match op with
  | CMinusUnary -> "-"
  | CNotUnary -> "!"
  | CAddressOfUnary -> "&"
  | CDerefUnary -> "*"

let private binaryToString op =
  match op with
  | CAddBinary -> "+"
  | CSubBinary -> "-"
  | CMulBinary -> "*"
  | CDivBinary -> "/"
  | CModuloBinary -> "%"
  | CBitAndBinary -> "&"
  | CBitOrBinary -> "|"
  | CBitXorBinary -> "^"
  | CLeftShiftBinary -> "<<"
  | CRightShiftBinary -> ">>"
  | CEqualBinary -> "=="
  | CNotEqualBinary -> "!="
  | CLessBinary -> "<"
  | CLessEqualBinary -> "<="
  | CGreaterBinary -> ">"
  | CGreaterEqualBinary -> ">="

// -----------------------------------------------
// Types
// -----------------------------------------------

let private cTyIsPtrOrConstPtr ty =
  match ty with
  | CPtrTy _
  | CConstPtrTy _ -> true
  | _ -> false

let private cpTy ty acc : string list =
  match ty with
  | CVoidTy -> acc |> cons "void"
  | CIntTy flavor -> acc |> cons (cIntegerTyName flavor)
  | CFloatTy flavor -> acc |> cons (cFloatTyName flavor)
  | CBoolTy -> acc |> cons "bool"
  | CCharTy -> acc |> cons "char"

  | CPtrTy ty ->
    acc
    |> cpTy ty
    |> cons (
      if cTyIsPtrOrConstPtr ty then
        "*"
      else
        " *"
    )

  | CConstPtrTy ty ->
    acc
    |> cpTy ty
    |> cons (
      if cTyIsPtrOrConstPtr ty then
        "const *"
      else
        " const *"
    )

  | CStructTy name -> acc |> cons "struct " |> cons name
  | CEnumTy name -> acc |> cons "enum " |> cons name
  | CEmbedTy code -> acc |> cons code

/// `T x`. (CTy isn't a function pointer.)
let private cpTyWithName (name: string) ty acc =
  let acc = acc |> cpTy ty

  let acc =
    if not (cTyIsPtrOrConstPtr ty) && name.Length <> 0 then
      acc |> cons " "
    else
      acc

  acc |> cons name

let private cpParams ps acc : string list =
  let rec go ps acc =
    match ps with
    | [] -> acc

    | [ name, ty ] -> acc |> cpTyWithName name ty

    | (name, ty) :: ps -> acc |> cpTyWithName name ty |> cons ", " |> go ps

  match ps with
  | [] -> acc |> cons "void"
  | _ -> acc |> go ps

// -----------------------------------------------
// Literals
// -----------------------------------------------

let private uint64FromHex (l: int) (r: int) (s: string) =
  assert (0 <= l && l < r && r <= s.Length)

  S.parseHexAsUInt64 s.[l..r - 1]
  |> Option.defaultWith unreachable

let private uint64ToHex (len: int) (value: uint64) = S.uint64ToHex len value

// See also: https://en.cppreference.com/w/c/language/integer_constant
//
// Remarks: When signed hex literal is >=2^(N-1), it's negative in milone-lang, but positive (larger type) in C.
//          So (int32_t)0x80000000 must need casting.
let private cpIntLit flavor (text: string) =
  // s: -?<digit>+ or 0x<hex>+
  let withFlavor force (s: string) =
    match flavor with
    | I8 -> "(int8_t)" + s
    | I16 -> "(int16_t)" + s
    | I32 when force -> "(int32_t)" + s
    | I32 -> s
    | I64
    | IPtr -> s + "LL"

    | U8 -> "(uint8_t)" + s + "U"
    | U16 -> "(uint16_t)" + s + "U"
    | U32 -> "(uint32_t)" + s + "U" // U suffix can be 64-bit
    | U64 -> s + "ULL"
    | UPtr -> "(size_t)" + s + "ULL" // size_t can be 32-bit

  if S.startsWith "-0x" text then
    assert (text.Length >= 4)
    let text = text.[3..text.Length - 1]

    let value =
      // (~~~) is unimplemented
      let a = uint64FromHex 0 text.Length text

      if a = uint64 0 then
        a
      else
        (a ^^^ (uint64 (int64 (-1)))) + uint64 1

    withFlavor true ("0x" + uint64ToHex 1 value)
  else if S.startsWith "0x" text then
    assert (text.Length >= 3)
    withFlavor true text
  else
    match flavor, text with
    | I32, "-2147483648" -> "(int32_t)0x80000000"
    | _ -> withFlavor false text

let private cpCharLit value =
  if value |> charNeedsEscaping then
    value |> charEscape
  else
    string value

let private cpStrRawLit (value: string) acc =
  acc
  |> cons "\""
  |> cons (stringEscape value)
  |> cons "\""

let private cpStrObjLit (value: string) acc =
  acc
  |> cons "(struct String){.ptr = "
  |> cpStrRawLit value
  |> cons ", .len = "
  |> cons (string (SB.utf8Length value))
  |> cons "}"

let private cpStructLit fields ty acc =
  acc
  |> cons "("
  |> cpTy ty
  |> cons "){"
  |> join ", " fields (fun (field, value) acc ->
    acc
    |> cons "."
    |> cons field
    |> cons " = "
    |> cpExpr value)
  |> cons "}"

// -----------------------------------------------
// Expressions
// -----------------------------------------------

/// Replaces `{i}` with i'th argument.
let private expandPlaceholders args code =
  args
  |> List.mapi (fun i arg -> i, arg)
  |> List.fold
       (fun code (i: int, arg) ->
         let arg =
           [] |> cpExpr arg |> List.rev |> S.concat ""

         let code =
           let placeholder = "{" + string i + "}"
           code |> S.replace placeholder arg

         code)
       code

let private cpExpr expr acc : string list =
  let rec cpExprList sep exprs acc =
    exprs
    |> List.fold
         (fun (first, acc) expr ->
           let acc =
             (if isFirst first then
                acc
              else
                acc |> cons sep)
             |> cpExpr expr

           NotFirst, acc)
         (First, acc)
    |> snd

  match expr with
  | CIntExpr (value, flavor) -> acc |> cons (cpIntLit flavor value)
  | CDoubleExpr value -> acc |> cons (string value)

  | CCharExpr value when C.isAscii value |> not ->
    acc
    |> cons "(char)'\\x"
    |> cons (S.uint64ToHex 2 (uint64 (byte value)))
    |> cons "'"

  | CCharExpr value ->
    acc
    |> cons "'"
    |> cons (cpCharLit value)
    |> cons "'"

  | CStrObjExpr value -> acc |> cpStrObjLit value
  | CStrRawExpr value -> acc |> cpStrRawLit value

  | CInitExpr (fields, ty) -> acc |> cpStructLit fields ty

  | CDotExpr (CStrObjExpr value, "len") -> acc |> cons (string (SB.utf8Length value))

  | CVarExpr name -> acc |> cons name

  | CCastExpr (expr, ty) ->
    acc
    |> cons "(("
    |> cpTy ty
    |> cons ")"
    |> cpExpr expr
    |> cons ")"

  | CDotExpr (expr, field) -> acc |> cpExpr expr |> cons "." |> cons field

  | CArrowExpr (expr, field) -> acc |> cpExpr expr |> cons "->" |> cons field

  | CIndexExpr (l, r) ->
    acc
    |> cpExpr l
    |> cons "["
    |> cpExpr r
    |> cons "]"

  | CCallExpr (callee, args) ->
    acc
    |> cpExpr callee
    |> cons "("
    |> cpExprList ", " args
    |> cons ")"

  | CSizeOfExpr ty -> acc |> cons "sizeof(" |> cpTy ty |> cons ")"

  | CTyPlaceholderExpr ty -> acc |> cpTy ty

  | CUnaryExpr (CDerefUnary, CUnaryExpr (CAddressOfUnary, arg)) -> acc |> cpExpr arg

  | CUnaryExpr (op, arg) ->
    acc
    |> cons "("
    |> cons (unaryToString op)
    |> cons "("
    |> cpExpr arg
    |> cons "))"

  | CBinaryExpr (op, l, r) ->
    acc
    |> cons "("
    |> cpExpr l
    |> cons " "
    |> cons (binaryToString op)
    |> cons " "
    |> cpExpr r
    |> cons ")"

  | CNativeExpr (code, args) ->
    let code = expandPlaceholders args code
    acc |> cons code

// -----------------------------------------------
// Statements
// -----------------------------------------------

let private cpStmt indent stmt acc : string list =
  match stmt with
  | CReturnStmt None -> acc |> cons indent |> cons "return;" |> cons eol

  | CReturnStmt (Some expr) ->
    acc
    |> cons indent
    |> cons "return "
    |> cpExpr expr
    |> cons ";"
    |> cons eol

  | CExprStmt expr ->
    acc
    |> cons indent
    |> cpExpr expr
    |> cons ";"
    |> cons eol

  | CLetStmt (name, init, ty) ->
    let cpInit acc =
      match init with
      | Some init -> acc |> cons " = " |> cpExpr init
      | None -> acc

    acc
    |> cons indent
    |> cpTyWithName name ty
    |> cpInit
    |> cons ";"
    |> cons eol

  | CSetStmt (l, r) ->
    acc
    |> cons indent
    |> cpExpr l
    |> cons " = "
    |> cpExpr r
    |> cons ";"
    |> cons eol

  | CLabelStmt label -> acc |> cons label |> cons ":;" |> cons eol

  | CGotoStmt label ->
    acc
    |> cons indent
    |> cons "goto "
    |> cons label
    |> cons ";"
    |> cons eol

  | CGotoIfStmt (pred, label) ->
    acc
    |> cons indent
    |> cons "if ("
    |> cpExpr pred
    |> cons ") goto "
    |> cons label
    |> cons ";"
    |> cons eol

  | CIfStmt (cond, thenCl, elseCl) ->
    acc
    |> cons indent
    |> cons "if ("
    |> cpExpr cond
    |> cons ") {"
    |> cons eol
    |> cpStmt (deeper indent) thenCl
    |> cons indent
    |> cons "} else {"
    |> cons eol
    |> cpStmt (deeper indent) elseCl
    |> cons indent
    |> cons "}"
    |> cons eol

  | CIfStmt1 (cond, thenCl) ->
    acc
    |> cons indent
    |> cons "if ("
    |> cpExpr cond
    |> cons ") "
    |> cpStmt "" thenCl // indent isn't used.

  | CSwitchStmt (cond, clauses) ->
    let cpCaseLabels cases acc =
      cases
      |> List.fold
           (fun acc lit ->
             acc
             |> cons (deeper indent)
             |> cons "case "
             |> cpExpr lit
             |> cons ":"
             |> cons eol)
           acc

    let cpDefaultLabel isDefault acc =
      if isDefault then
        acc
        |> cons (deeper indent)
        |> cons "default:"
        |> cons eol
      else
        acc

    let cpClause acc =
      clauses
      |> List.fold
           (fun (first, acc) (cases, isDefault, body) ->
             let acc =
               (if isFirst first then
                  acc
                else
                  acc |> cons eol)
               |> cpCaseLabels cases
               |> cpDefaultLabel isDefault
               |> cpStmt (deeper (deeper indent)) body

             NotFirst, acc)
           (First, acc)
      |> snd

    acc
    |> cons indent
    |> cons "switch ("
    |> cpExpr cond
    |> cons ") {"
    |> cons eol
    |> cpClause
    |> cons indent
    |> cons "}"
    |> cons eol

  | CNativeStmt (code, args) ->
    let code = expandPlaceholders args code

    acc |> cons code

let private cpStmtList indent stmts acc : string list =
  stmts
  |> List.fold (fun acc stmt -> cpStmt indent stmt acc) acc

// -----------------------------------------------
// Declarations
// -----------------------------------------------

let private cpDecl decl acc =
  match decl with
  | CErrorDecl (message, line) ->
    acc
    |> cons "#line "
    |> cons (string line)
    |> cons eol
    |> cons "#error "
    |> cons message
    |> cons eol

  | CStructDecl (structName, fields, variants) ->
    let cpFields indent fields acc =
      fields
      |> List.fold
           (fun acc (name, ty) ->
             acc
             |> cons indent
             |> cpTyWithName name ty
             |> cons ";"
             |> cons eol)
           acc

    let cpVariants acc =
      match variants with
      | [] -> acc

      | _ ->
        acc
        |> cons "    union {"
        |> cons eol
        |> cpFields "        " variants
        |> cons "    };"
        |> cons eol

    acc
    |> cons "struct "
    |> cons structName
    |> cons " {"
    |> cons eol
    |> cpFields "    " fields
    |> cpVariants
    |> cons "};"
    |> cons eol

  | CEnumDecl (enumName, variants) ->
    let cpEnumerants variants acc =
      variants
      |> List.fold
           (fun acc variant ->
             acc
             |> cons "    "
             |> cons variant
             |> cons ","
             |> cons eol)
           acc

    acc
    |> cons "enum "
    |> cons enumName
    |> cons " {"
    |> cons eol
    |> cpEnumerants variants
    |> cons "};"
    |> cons eol

  | CStaticVarDecl (name, ty) ->
    acc
    |> cpTyWithName name ty
    |> cons ";"
    |> cons eol

  | CInternalStaticVarDecl (name, ty) ->
    acc
    // FIXME: global variable is now defined in entry module no matter where it is. (this might be resolved)
    // |> cons "static "
    |> cpTyWithName name ty
    |> cons ";"
    |> cons eol

  | CExternVarDecl (name, ty) ->
    acc
    |> cons "extern "
    |> cpTyWithName name ty
    |> cons ";"
    |> cons eol

  | CFunDecl (name, args, resultTy, body) ->
    acc
    |> cpTyWithName name resultTy
    |> cons "("
    |> cpParams args
    |> cons ") {"
    |> cons eol
    |> cpStmtList "    " body
    |> cons "}"
    |> cons eol

  | CStaticFunDecl (name, args, resultTy, body) ->
    // FIXME: monomorphization instances can't have stable external linkage,
    //        however, they still need to have external linkage.

    acc
    // |> cons "static "
    |> cpTyWithName name resultTy
    |> cons "("
    |> cpParams args
    |> cons ") {"
    |> cons eol
    |> cpStmtList "    " body
    |> cons "}"
    |> cons eol

  | CFunPtrTyDef _
  | CStructForwardDecl _
  | CFunForwardDecl _
  | CNativeDecl _ -> acc

/// Prints forward declaration.
let private cpForwardDecl decl acc =
  let cpFunForwardDecl name cpParams resultTy acc =
    acc
    |> cpTyWithName name resultTy
    |> cons "("
    |> cpParams
    |> cons ");"
    |> cons eol
    |> cons eol

  match decl with
  | CErrorDecl _
  | CEnumDecl _
  | CStaticVarDecl _
  | CInternalStaticVarDecl _
  | CExternVarDecl _ -> acc

  | CFunPtrTyDef (ident, argTys, resultTy) ->
    let acc = acc |> cons "typedef "

    let acc =
      match argTys with
      | [] ->
        acc
        |> cpTy resultTy
        |> cons "(*"
        |> cons ident
        |> cons ")(void)"

      | _ ->
        acc
        |> cpTy resultTy
        |> cons "(*"
        |> cons ident
        |> cons ")("
        |> join ", " argTys cpTy
        |> cons ")"

    acc |> cons ";" |> cons eol |> cons eol

  | CStructDecl (name, _, _) ->
    acc
    |> cons "struct "
    |> cons name
    |> cons ";"
    |> cons eol
    |> cons eol

  | CStructForwardDecl name ->
    acc
    |> cons "struct "
    |> cons name
    |> cons ";"
    |> cons eol
    |> cons eol

  | CFunForwardDecl (name, argTys, resultTy) ->
    let cpParamTys acc =
      let args = List.map (fun argTy -> "", argTy) argTys
      acc |> cpParams args

    acc |> cpFunForwardDecl name cpParamTys resultTy

  | CFunDecl (name, args, resultTy, _) ->
    acc
    |> cpFunForwardDecl name (cpParams args) resultTy

  | CStaticFunDecl (name, args, resultTy, _) ->
    acc
    // |> cons "static "
    |> cpFunForwardDecl name (cpParams args) resultTy

  | CNativeDecl code -> acc |> cons code |> cons eol

let private cpForwardDecls decls acc =
  decls
  |> List.fold (fun acc decl -> cpForwardDecl decl acc) acc

let private cpDecls decls acc =
  decls
  |> List.fold
       (fun (first, acc) decl ->
         if decl |> declIsForwardOnly then
           first, acc
         else
           let acc =
             (if isFirst first then
                acc
              else
                acc |> cons eol)
             |> cpDecl decl

           NotFirst, acc)
       (First, acc)
  |> snd

// -----------------------------------------------
// Root
// -----------------------------------------------

let private cpHeader acc =
  // stdio for printf
  // stdlib for exit
  let header =
    "#include <stdio.h>\n#include <stdlib.h>\n#include <milone.h>"

  acc |> cons header |> cons eol |> cons eol

let cirDump (decls: CDecl list) : string =
  []
  |> cpHeader
  |> cpForwardDecls decls
  |> cpDecls decls
  |> List.rev
  |> S.concat ""

let cirDumpHeader (decls: CDecl list) : string =
  []
  |> cpHeader
  |> cpForwardDecls decls
  |> List.rev
  |> S.concat ""
