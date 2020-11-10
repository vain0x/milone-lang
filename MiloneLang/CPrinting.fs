/// Converts CIR to C language source code.
/// Includes runtime functions.
module rec MiloneLang.CPrinting

open MiloneLang.Types
open MiloneLang.Helpers

let eol = """
"""

let join sep f (xs, acc) =
  let rec go acc xs =
    match xs with
    | [] -> acc
    | [ x ] -> f (x, acc)
    | x :: xs ->
        let acc = f (x, acc)
        let acc = acc |> cons sep
        go acc xs

  go acc xs

let opStr op =
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

let cprintTyFunPtr name argTys resultTy acc =
  let acc = cprintTy acc resultTy

  let acc =
    acc
    |> cons "(*"
    |> cons name
    |> cons ")"
    |> cons "("

  let rec go acc argTys =
    (argTys, acc)
    |> join ", " (fun (argTy, acc) -> cprintTy acc argTy)

  let acc = go acc argTys
  acc |> cons ")"

let rec cprintTy acc ty: string list =
  match ty with
  | CVoidTy -> acc |> cons "void"
  | CIntTy -> acc |> cons "int"
  | CUInt32Ty -> acc |> cons "uint32_t"
  | CCharTy -> acc |> cons "char"
  | CPtrTy ty ->
      let acc = cprintTy acc ty
      acc |> cons "*"
  | CFunPtrTy (argTys, resultTy) -> cprintTyFunPtr "" argTys resultTy acc
  | CStructTy ident -> acc |> cons "struct " |> cons ident
  | CEnumTy ident -> acc |> cons "enum " |> cons ident

/// `T x` or `T (*x)(..)`
let cprintTyWithName acc name ty =
  match ty with
  | CFunPtrTy (argTys, resultTy) -> cprintTyFunPtr name argTys resultTy acc
  | _ -> cprintTy acc ty |> cons " " |> cons name

let rec cprintParams acc ps: string list =
  let rec go acc ps =
    match ps with
    | [] -> acc
    | [ name, ty ] -> cprintTy acc ty |> cons " " |> cons name
    | (name, ty) :: ps ->
        let acc = cprintTy acc ty

        let acc =
          acc |> cons " " |> cons name |> cons ", "

        go acc ps

  go acc ps

let cprintExprChar value =
  if value |> charNeedsEscaping then value |> charEscape else string value

let cprintExprStrRaw acc (value: string) =
  acc
  |> cons "\""
  |> cons (strEscape value)
  |> cons "\""

let cprintExprStrObj acc (value: string) =
  let acc = acc |> cons "(struct String){.str = "
  let acc = cprintExprStrRaw acc value

  let acc =
    acc
    |> cons ", .len = "
    |> cons (string value.Length)
    |> cons "}"

  acc

let cprintExprInit acc fields ty =
  let acc = acc |> cons "("
  let acc = cprintTy acc ty
  let acc = acc |> cons "){"

  let acc =
    (fields, acc)
    |> join ", " (fun ((field, value), acc) ->
         let acc =
           acc |> cons "." |> cons field |> cons " = "

         let acc = cprintExpr acc value
         acc)

  let acc = acc |> cons "}"
  acc

let rec cprintExpr acc expr: string list =
  let rec cprintExprList acc index separator exprs =
    match exprs with
    | [] -> acc
    | expr :: exprs ->
        let acc =
          if index > 0 then acc |> cons separator else acc

        let acc = cprintExpr acc expr
        cprintExprList acc 1 separator exprs

  match expr with
  | CDefaultExpr -> acc |> cons "{}"
  | CIntExpr value -> acc |> cons (string value)
  | CCharExpr value ->
      acc
      |> cons "'"
      |> cons (cprintExprChar value)
      |> cons "'"
  | CStrObjExpr value -> cprintExprStrObj acc value
  | CStrRawExpr value -> cprintExprStrRaw acc value
  | CInitExpr (fields, ty) -> cprintExprInit acc fields ty
  | CNavExpr (CStrObjExpr value, "len") -> acc |> cons (string value.Length)
  | CRefExpr (value) -> acc |> cons value
  | CProjExpr (left, index) ->
      let acc = cprintExpr acc left
      acc |> cons ".t" |> cons (string index)
  | CCastExpr (expr, ty) ->
      let acc = acc |> cons "(("
      let acc = cprintTy acc ty
      let acc = acc |> cons ")"
      let acc = cprintExpr acc expr
      let acc = acc |> cons ")"
      acc
  | CNavExpr (expr, field) ->
      let acc = cprintExpr acc expr
      let acc = acc |> cons "." |> cons field
      acc
  | CArrowExpr (expr, field) ->
      let acc = cprintExpr acc expr
      let acc = acc |> cons "->" |> cons field
      acc
  | CIndexExpr (l, r) ->
      let acc = cprintExpr acc l
      let acc = acc |> cons "["
      let acc = cprintExpr acc r
      let acc = acc |> cons "]"
      acc
  | CCallExpr (callee, args) ->
      let acc = cprintExpr acc callee
      let acc = acc |> cons "("
      let acc = cprintExprList acc 0 ", " args
      let acc = acc |> cons ")"
      acc
  | CUnaryExpr (op, arg) ->
      let acc = acc |> cons "("

      let acc =
        match op with
        | CNotUnary -> acc |> cons "!"
        | CDerefUnary -> acc |> cons "*"

      let acc = acc |> cons "("
      let acc = cprintExpr acc arg
      let acc = acc |> cons "))"
      acc
  | CBinaryExpr (op, first, second) ->
      let acc = acc |> cons "("
      let acc = cprintExpr acc first

      let acc =
        acc |> cons " " |> cons (opStr op) |> cons " "

      let acc = cprintExpr acc second
      let acc = acc |> cons ")"
      acc

let cprintStmt acc indent stmt: string list =
  match stmt with
  | CReturnStmt None -> acc |> cons indent |> cons "return;" |> cons eol
  | CReturnStmt (Some expr) ->
      let acc = acc |> cons indent |> cons "return "
      let acc = cprintExpr acc expr
      acc |> cons ";" |> cons eol
  | CExprStmt expr ->
      let acc = acc |> cons indent
      let acc = cprintExpr acc expr
      acc |> cons ";" |> cons eol
  | CLetStmt (name, init, ty) ->
      let acc = acc |> cons indent
      let acc = cprintTyWithName acc name ty

      let acc =
        match init with
        | Some init ->
            let acc = acc |> cons " = "
            cprintExpr acc init
        | None -> acc

      acc |> cons ";" |> cons eol
  | CLetAllocStmt (name, valPtrTy, varTy) ->
      let valTy =
        match valPtrTy with
        | CPtrTy ty -> ty
        | _ -> failwithf "Never: Expected pointer type but %A" valPtrTy

      let acc = acc |> cons indent
      let acc = cprintTyWithName acc name varTy
      let acc = acc |> cons " = ("
      let acc = cprintTy acc varTy

      let acc =
        acc |> cons ")milone_mem_alloc(1, sizeof("

      let acc = cprintTy acc valTy
      let acc = acc |> cons "));" |> cons eol
      acc
  | CSetStmt (l, r) ->
      let acc = acc |> cons indent
      let acc = cprintExpr acc l |> cons " = "
      let acc = cprintExpr acc r |> cons ";" |> cons eol
      acc
  | CLabelStmt label -> acc |> cons label |> cons ":;" |> cons eol
  | CGotoStmt label ->
      acc
      |> cons indent
      |> cons "goto "
      |> cons label
      |> cons ";"
      |> cons eol
  | CGotoIfStmt (pred, label) ->
      let acc = acc |> cons indent |> cons "if ("
      let acc = cprintExpr acc pred

      let acc =
        acc
        |> cons ") goto "
        |> cons label
        |> cons ";"
        |> cons eol

      acc

  | CIfStmt (cond, thenCl, elseCl) ->
      let acc = acc |> cons indent |> cons "if ("
      let acc = cprintExpr acc cond

      let acc = acc |> cons ") {" |> cons eol

      let acc = cprintStmts acc ("    " + indent) thenCl

      let acc =
        acc |> cons indent |> cons "} else {" |> cons eol

      let acc = cprintStmts acc ("    " + indent) elseCl

      acc |> cons indent |> cons "}" |> cons eol

let rec cprintStmts acc indent stmts: string list =
  match stmts with
  | [] -> acc
  | stmt :: stmts ->
      let acc = cprintStmt acc indent stmt
      cprintStmts acc indent stmts

let cprintDecl acc decl =
  match decl with
  | CErrorDecl (message, line) ->
      let acc =
        acc
        |> cons "#line "
        |> cons (string line)
        |> cons eol

      let acc =
        acc |> cons "#error " |> cons message |> cons eol

      acc
  | CStructDecl (ident, fields, variants) ->
      let cprintFields indent acc fields =
        let rec go acc fields =
          match fields with
          | [] -> acc
          | (ident, ty) :: fields ->
              let acc = acc |> cons indent
              let acc = cprintTyWithName acc ident ty
              let acc = acc |> cons ";" |> cons eol
              go acc fields

        go acc fields

      let acc =
        acc
        |> cons "struct "
        |> cons ident
        |> cons " {"
        |> cons eol

      let acc = cprintFields "    " acc fields

      let acc =
        match variants with
        | [] -> acc
        | _ ->
            let acc = acc |> cons "    union {" |> cons eol
            let acc = cprintFields "        " acc variants
            let acc = acc |> cons "    };" |> cons eol
            acc

      let acc = acc |> cons "};" |> cons eol
      acc
  | CEnumDecl (tyIdent, variants) ->
      let acc =
        acc
        |> cons "enum "
        |> cons tyIdent
        |> cons " {"
        |> cons eol

      let rec go acc variants =
        match variants with
        | [] -> acc
        | variant :: variants ->
            let acc = acc |> cons "    "

            let acc =
              acc |> cons variant |> cons "," |> cons eol

            go acc variants

      let acc = go acc variants
      let acc = acc |> cons "};" |> cons eol
      acc
  | CStaticVarDecl (ident, _) ->
      acc
      |> cons "// static "
      |> cons ident
      |> cons ";"
      |> cons eol
  | CFunDecl (ident, args, resultTy, body) ->
      let acc = cprintTyWithName acc ident resultTy
      let acc = acc |> cons "("
      let acc = cprintParams acc args
      let acc = acc |> cons ") {" |> cons eol
      let acc = cprintStmts acc "    " body
      let acc = acc |> cons "}" |> cons eol
      acc

/// Prints forward declaration.
let cprintDeclForward acc decl =
  match decl with
  | CErrorDecl _ -> acc
  | CStructDecl (ident, _, _) ->
      let acc =
        acc
        |> cons "struct "
        |> cons ident
        |> cons ";"
        |> cons eol
        |> cons eol

      acc
  | CEnumDecl (tyIdent, _) ->
      let acc =
        acc
        |> cons "enum "
        |> cons tyIdent
        |> cons ";"
        |> cons eol
        |> cons eol

      acc
  | CStaticVarDecl (ident, ty) ->
      let acc = acc |> cons "static "
      let acc = cprintTyWithName acc ident ty
      acc |> cons ";" |> cons eol |> cons eol
  | CFunDecl (ident, args, resultTy, _) ->
      let acc = cprintTyWithName acc ident resultTy
      let acc = acc |> cons "("
      let acc = cprintParams acc args
      let acc = acc |> cons ");" |> cons eol |> cons eol
      acc

let rec cprintDeclForwards acc decls =
  let rec go acc decls =
    match decls with
    | [] -> acc
    | decl :: decls ->
        let acc = cprintDeclForward acc decl
        go acc decls

  go acc decls

let rec cprintDecls acc decls =
  let acc = cprintDeclForwards acc decls

  let rec go acc decls =
    match decls with
    | [] -> acc
    | [ decl ] -> cprintDecl acc decl
    | decl :: decls ->
        let acc = cprintDecl acc decl |> cons eol
        go acc decls

  go acc decls

let cprintHeader acc =
  let header = "#include \"milone.h\""
  acc |> cons header |> cons eol |> cons eol

let cprintRun (printer: string list -> string list): string = printer [] |> listRev |> strConcat

let cprint (decls: CDecl list): string =
  cprintRun (fun acc -> cprintDecls (cprintHeader acc) decls)
