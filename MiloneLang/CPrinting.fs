/// Converts CIR to C language source code.
/// Includes runtime functions.
module rec MiloneLang.CPrinting

open MiloneLang.Types
open MiloneLang.Helpers

let private eol = "\n"

let private deeper (indent: string) = "    " + indent

let private join sep xs f acc =
  let rec go xs acc =
    match xs with
    | [] -> acc
    | [ x ] -> acc |> f x
    | x :: xs -> acc |> f x |> cons sep |> go xs

  go xs acc

type private First =
  | First
  | NotFirst

let private isFirst first =
  match first with
  | First -> true
  | NotFirst -> false

// -----------------------------------------------
// Operators
// -----------------------------------------------

let private unaryToString op =
  match op with
  | CNotUnary -> "!"
  | CDerefUnary -> "*"

let private binaryToString op =
  match op with
  | CAddBinary -> "+"
  | CSubBinary -> "-"
  | CMulBinary -> "*"
  | CDivBinary -> "/"
  | CModBinary -> "%"
  | CEqualBinary -> "=="
  | CNotEqualBinary -> "!="
  | CLessBinary -> "<"
  | CLessEqualBinary -> "<="
  | CGreaterBinary -> ">"
  | CGreaterEqualBinary -> ">="

// -----------------------------------------------
// Types
// -----------------------------------------------

let private cprintTyFunPtr name argTys resultTy acc =
  acc
  |> cprintTy resultTy
  |> cons "(*"
  |> cons name
  |> cons ")("
  |> join ", " argTys cprintTy
  |> cons ")"

let private cprintTy ty acc: string list =
  match ty with
  | CVoidTy -> acc |> cons "void"
  | CIntTy -> acc |> cons "int"
  | CUInt32Ty -> acc |> cons "uint32_t"
  | CCharTy -> acc |> cons "char"
  | CPtrTy ty -> acc |> cprintTy ty |> cons "*"
  | CFunPtrTy (argTys, resultTy) -> acc |> cprintTyFunPtr "" argTys resultTy
  | CStructTy ident -> acc |> cons "struct " |> cons ident
  | CEnumTy ident -> acc |> cons "enum " |> cons ident

/// `T x` or `T (*x)(..)`
let private cprintTyWithName name ty acc =
  match ty with
  | CFunPtrTy (argTys, resultTy) -> acc |> cprintTyFunPtr name argTys resultTy
  | _ -> acc |> cprintTy ty |> cons " " |> cons name

let private cprintParams ps acc: string list =
  let rec go ps acc =
    match ps with
    | [] -> acc

    | [ name, ty ] -> acc |> cprintTy ty |> cons " " |> cons name

    | (name, ty) :: ps ->
        acc
        |> cprintTy ty
        |> cons " "
        |> cons name
        |> cons ", "
        |> go ps

  acc |> go ps

// -----------------------------------------------
// Literals
// -----------------------------------------------

let private cprintExprChar value =
  if value |> charNeedsEscaping then value |> charEscape else string value

let private cprintExprStrRaw (value: string) acc =
  acc
  |> cons "\""
  |> cons (strEscape value)
  |> cons "\""

let private cprintExprStrObj (value: string) acc =
  acc
  |> cons "(struct String){.str = "
  |> cprintExprStrRaw value
  |> cons ", .len = "
  |> cons (string value.Length)
  |> cons "}"

let private cpLit lit acc =
  match lit with
  | BoolLit false -> acc |> cons "0"
  | BoolLit true -> acc |> cons "1"
  | IntLit value -> acc |> cons (string value)

  | CharLit value ->
      acc
      |> cons "'"
      |> cons (cprintExprChar value)
      |> cons "'"

  | StrLit _ -> failwith "unsupported"

let private cprintExprInit fields ty acc =
  acc
  |> cons "("
  |> cprintTy ty
  |> cons "){"
  |> join ", " fields (fun (field, value) acc ->
       acc
       |> cons "."
       |> cons field
       |> cons " = "
       |> cprintExpr value)
  |> cons "}"

// -----------------------------------------------
// Expressions
// -----------------------------------------------

let private cprintExpr expr acc: string list =
  let rec cprintExprList sep exprs acc =
    exprs
    |> List.fold (fun (first, acc) expr ->
         let acc =
           (if isFirst first then acc else acc |> cons sep)
           |> cprintExpr expr

         NotFirst, acc) (First, acc)
    |> snd

  match expr with
  | CDefaultExpr -> acc |> cons "{}"
  | CIntExpr value -> acc |> cons (string value)

  | CCharExpr value ->
      acc
      |> cons "'"
      |> cons (cprintExprChar value)
      |> cons "'"

  | CStrObjExpr value -> acc |> cprintExprStrObj value
  | CStrRawExpr value -> acc |> cprintExprStrRaw value

  | CInitExpr (fields, ty) -> acc |> cprintExprInit fields ty

  | CNavExpr (CStrObjExpr value, "len") -> acc |> cons (string value.Length)

  | CRefExpr name -> acc |> cons name

  | CProjExpr (l, index) ->
      acc
      |> cprintExpr l
      |> cons ".t"
      |> cons (string index)

  | CCastExpr (expr, ty) ->
      acc
      |> cons "(("
      |> cprintTy ty
      |> cons ")"
      |> cprintExpr expr
      |> cons ")"

  | CNavExpr (expr, field) -> acc |> cprintExpr expr |> cons "." |> cons field

  | CArrowExpr (expr, field) -> acc |> cprintExpr expr |> cons "->" |> cons field

  | CIndexExpr (l, r) ->
      acc
      |> cprintExpr l
      |> cons "["
      |> cprintExpr r
      |> cons "]"

  | CCallExpr (callee, args) ->
      acc
      |> cprintExpr callee
      |> cons "("
      |> cprintExprList ", " args
      |> cons ")"

  | CUnaryExpr (op, arg) ->
      acc
      |> cons "("
      |> cons (unaryToString op)
      |> cons "("
      |> cprintExpr arg
      |> cons "))"

  | CBinaryExpr (op, l, r) ->
      acc
      |> cons "("
      |> cprintExpr l
      |> cons " "
      |> cons (binaryToString op)
      |> cons " "
      |> cprintExpr r
      |> cons ")"

// -----------------------------------------------
// Statements
// -----------------------------------------------

let private cprintStmt indent stmt acc: string list =
  match stmt with
  | CReturnStmt None -> acc |> cons indent |> cons "return;" |> cons eol

  | CReturnStmt (Some expr) ->
      acc
      |> cons indent
      |> cons "return "
      |> cprintExpr expr
      |> cons ";"
      |> cons eol

  | CExprStmt expr ->
      acc
      |> cons indent
      |> cprintExpr expr
      |> cons ";"
      |> cons eol

  | CLetStmt (name, init, ty) ->
      let cpInit acc =
        match init with
        | Some init -> acc |> cons " = " |> cprintExpr init
        | None -> acc

      acc
      |> cons indent
      |> cprintTyWithName name ty
      |> cpInit
      |> cons ";"
      |> cons eol

  | CLetAllocStmt (name, valPtrTy, varTy) ->
      let valTy =
        match valPtrTy with
        | CPtrTy ty -> ty
        | _ -> failwithf "Never: Expected pointer type but %A" valPtrTy

      acc
      |> cons indent
      |> cprintTyWithName name varTy
      |> cons " = ("
      |> cprintTy varTy
      |> cons ")milone_mem_alloc(1, sizeof("
      |> cprintTy valTy
      |> cons "));"
      |> cons eol

  | CSetStmt (l, r) ->
      acc
      |> cons indent
      |> cprintExpr l
      |> cons " = "
      |> cprintExpr r
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
      |> cprintExpr pred
      |> cons ") goto "
      |> cons label
      |> cons ";"
      |> cons eol

  | CIfStmt (cond, thenCl, elseCl) ->
      acc
      |> cons indent
      |> cons "if ("
      |> cprintExpr cond
      |> cons ") {"
      |> cons eol
      |> cprintStmts (deeper indent) thenCl
      |> cons indent
      |> cons "} else {"
      |> cons eol
      |> cprintStmts (deeper indent) elseCl
      |> cons indent
      |> cons "}"
      |> cons eol

  | CSwitchStmt (cond, clauses) ->
      let cpCaseLabels cases acc =
        cases
        |> List.fold (fun acc lit ->
             acc
             |> cons (deeper indent)
             |> cons "case "
             |> cprintExpr lit
             |> cons ":"
             |> cons eol) acc

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
        |> List.fold (fun (first, acc) (cases, isDefault, body) ->
             let acc =
               (if isFirst first then acc else acc |> cons eol)
               |> cpCaseLabels cases
               |> cpDefaultLabel isDefault
               |> cprintStmts (deeper (deeper indent)) body

             NotFirst, acc) (First, acc)
        |> snd

      acc
      |> cons indent
      |> cons "switch ("
      |> cprintExpr cond
      |> cons ") {"
      |> cons eol
      |> cpClause
      |> cons indent
      |> cons "}"
      |> cons eol

let private cprintStmts indent stmts acc: string list =
  stmts
  |> List.fold (fun acc stmt -> cprintStmt indent stmt acc) acc

// -----------------------------------------------
// Declarations
// -----------------------------------------------

let private cprintDecl decl acc =
  match decl with
  | CErrorDecl (message, line) ->
      acc
      |> cons "#line "
      |> cons (string line)
      |> cons eol
      |> cons "#error "
      |> cons message
      |> cons eol

  | CStructDecl (ident, fields, variants) ->
      let cpFields indent fields acc =
        fields
        |> List.fold (fun acc (ident, ty) ->
             acc
             |> cons indent
             |> cprintTyWithName ident ty
             |> cons ";"
             |> cons eol) acc

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
      |> cons ident
      |> cons " {"
      |> cons eol
      |> cpFields "    " fields
      |> cpVariants
      |> cons "};"
      |> cons eol

  | CEnumDecl (tyIdent, variants) ->
      let cpEnumerants variants acc =
        variants
        |> List.fold (fun acc variant ->
             acc
             |> cons "    "
             |> cons variant
             |> cons ","
             |> cons eol) acc

      acc
      |> cons "enum "
      |> cons tyIdent
      |> cons " {"
      |> cons eol
      |> cpEnumerants variants
      |> cons "};"
      |> cons eol

  | CStaticVarDecl (ident, _) ->
      acc
      |> cons "// static "
      |> cons ident
      |> cons ";"
      |> cons eol

  | CFunDecl (ident, args, resultTy, body) ->
      acc
      |> cprintTyWithName ident resultTy
      |> cons "("
      |> cprintParams args
      |> cons ") {"
      |> cons eol
      |> cprintStmts "    " body
      |> cons "}"
      |> cons eol

/// Prints forward declaration.
let private cprintDeclForward decl acc =
  match decl with
  | CErrorDecl _ -> acc

  | CStructDecl (ident, _, _) ->
      acc
      |> cons "struct "
      |> cons ident
      |> cons ";"
      |> cons eol
      |> cons eol

  | CEnumDecl (ident, _) ->
      acc
      |> cons "enum "
      |> cons ident
      |> cons ";"
      |> cons eol
      |> cons eol

  | CStaticVarDecl (ident, ty) ->
      acc
      |> cons "static "
      |> cprintTyWithName ident ty
      |> cons ";"
      |> cons eol
      |> cons eol

  | CFunDecl (ident, args, resultTy, _) ->
      acc
      |> cprintTyWithName ident resultTy
      |> cons "("
      |> cprintParams args
      |> cons ");"
      |> cons eol
      |> cons eol

let private cprintDeclForwards decls acc =
  decls
  |> List.fold (fun acc decl -> cprintDeclForward decl acc) acc

let private cprintDecls decls acc =
  let acc = acc |> cprintDeclForwards decls

  decls
  |> List.fold (fun (first, acc) decl ->
       let acc =
         (if isFirst first then acc else acc |> cons eol)
         |> cprintDecl decl

       NotFirst, acc) (First, acc)
  |> snd

// -----------------------------------------------
// Root
// -----------------------------------------------

let private cprintHeader acc =
  let header = "#include \"milone.h\""
  acc |> cons header |> cons eol |> cons eol

let cprint (decls: CDecl list): string =
  []
  |> cprintHeader
  |> cprintDecls decls
  |> List.rev
  |> strConcat
