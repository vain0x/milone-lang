/// Prints C language code from C language IR.
module rec MiloneLang.CPrinting

let ( *- ) acc second =
  second :: acc

let eol = """
"""

let join sep f (xs, acc) =
  let rec go acc xs =
    match xs with
    | [] ->
      acc
    | [x] ->
      f (x, acc)
    | x :: xs ->
      let acc = f (x, acc)
      let acc = acc *- sep
      go acc xs
  go acc xs

let opStr op =
  match op with
  | COp.Add -> "+"
  | COp.Sub -> "-"
  | COp.Mul -> "*"
  | COp.Div -> "/"
  | COp.Mod -> "%"
  | COp.Eq -> "=="
  | COp.Ne -> "!="
  | COp.Lt -> "<"
  | COp.Le -> "<="

let rec cprintTy acc ty: string list =
  match ty with
  | CTy.Void ->
    acc *- "void"
  | CTy.Int ->
    acc *- "int"
  | CTy.Char ->
    acc *- "char"
  | CTy.Ptr ty ->
    let acc = cprintTy acc ty
    acc *- "*"
  | CTy.Struct ident ->
    acc *- "struct " *- ident
  | CTy.Enum ident ->
    acc *- "enum " *- ident

let rec cprintParams acc ps: string list =
  let rec go acc ps =
    match ps with
    | [] -> acc
    | [name, ty] ->
      cprintTy acc ty *- " " *- name
    | (name, ty) :: ps ->
      let acc = cprintTy acc ty
      let acc = acc *- " " *- name *- ", "
      go acc ps
  go acc ps

let cprintExprChar value =
  match value with
  | '\r' -> "\\r"
  | '\n' -> "\\n"
  | '\t' -> "\\t"
  | '\'' -> "\\'"
  | '\\' -> "\\\\"
  | '\u0000' -> "\\0"
  | _ -> string value

let cprintExprStrRaw acc (value: string) =
  let rec chunk i =
    if i >= value.Length || value.[i] = '\\'
    then i
    else chunk (i + 1)
  let rec go acc i =
    if i >= value.Length then
      acc
    else
      match value.[i] with
      | '\u0000' ->
        // FIXME: support
        go (acc *- "\\0") (i + 1)
      | '\r' ->
        go (acc *- "\\r") (i + 1)
      | '\n' ->
        go (acc *- "\\n") (i + 1)
      | '\t' ->
        go (acc *- "\\t") (i + 1)
      | '\"' ->
        go (acc *- "\\\"") (i + 1)
      | '\\' ->
        go (acc *- "\\\\") (i + 1)
      | _ ->
        go (acc *- string value.[i]) (i + 1)
  go (acc *- "\"") 0 *- "\""

let cprintExprStrObj acc (value: string) =
  let acc = acc *- "(struct String){.str = "
  let acc = cprintExprStrRaw acc value
  let acc = acc *- ", .len = " *- string value.Length *- "}"
  acc

let cprintExprInit acc fields ty =
  let acc = acc *- "("
  let acc = cprintTy acc ty
  let acc = acc *- "){"
  let acc =
    (fields, acc) |> join ", " (fun ((field, value), acc) ->
      let acc = acc *- "." *- field *- " = "
      let acc = cprintExpr acc value
      acc
    )
  let acc = acc *- "}"
  acc

let rec cprintExpr acc expr: string list =
  let rec cprintExprList acc index separator exprs =
    match exprs with
    | [] -> acc
    | expr :: exprs ->
      let acc = if index > 0 then acc *- separator else acc
      let acc = cprintExpr acc expr
      cprintExprList acc 1 separator exprs
  match expr with
  | CExpr.Default ->
    acc *- "{}"
  | CExpr.Int value ->
    acc *- string value
  | CExpr.Char value ->
    acc *- "'" *- cprintExprChar value *- "'"
  | CExpr.StrObj value ->
    cprintExprStrObj acc value
  | CExpr.StrRaw value->
    cprintExprStrRaw acc value
  | CExpr.Init (fields, ty) ->
    cprintExprInit acc fields ty
  | CExpr.Nav (CExpr.StrObj value, "len") ->
    acc *- string value.Length
  | CExpr.Ref (value) ->
    acc *- value
  | CExpr.Proj (left, index) ->
    let acc = cprintExpr acc left
    acc *- ".t" *- string index
  | CExpr.Cast (expr, ty) ->
    let acc = acc *- "(("
    let acc = cprintTy acc ty
    let acc = acc *- ")"
    let acc = cprintExpr acc expr
    let acc = acc *- ")"
    acc
  | CExpr.Nav (expr, field) ->
    let acc = cprintExpr acc expr
    let acc = acc *- "." *- field
    acc
  | CExpr.Arrow (expr, field) ->
    let acc = cprintExpr acc expr
    let acc = acc *- "->" *- field
    acc
  | CExpr.Index (l, r) ->
    let acc = cprintExpr acc l
    let acc = acc *- "["
    let acc = cprintExpr acc r
    let acc = acc *- "]"
    acc
  | CExpr.Call (callee, args) ->
    let acc = cprintExpr acc callee
    let acc = acc *- "("
    let acc = cprintExprList acc 0 ", " args
    let acc = acc *- ")"
    acc
  | CExpr.UniOp (op, arg) ->
    let acc =
      match op with
      | CUniOp.Not -> acc *- "!"
      | CUniOp.Deref -> acc *- "*"
    let acc = acc *- "("
    let acc = cprintExpr acc arg
    let acc = acc *- ")"
    acc
  | CExpr.Op (op, first, second) ->
    let acc = acc *- "("
    let acc = cprintExpr acc first
    let acc = acc *- " " *- opStr op *- " "
    let acc = cprintExpr acc second
    let acc = acc *- ")"
    acc

let cprintStmt acc indent stmt: string list =
  match stmt with
  | CStmt.Return None ->
    acc *- indent *- "return;" *- eol
  | CStmt.Return (Some expr) ->
    let acc = acc *- indent *- "return "
    let acc = cprintExpr acc expr
    acc *- ";" *- eol
  | CStmt.Expr expr ->
    let acc = acc *- indent
    let acc = cprintExpr acc expr
    acc *- ";" *- eol
  | CStmt.Let (name, init, ty) ->
    let acc = acc *- indent
    let acc = cprintTy acc ty
    let acc = acc *- " " *- name
    let acc =
      match init with
      | Some init ->
        let acc = acc *- " = "
        cprintExpr acc init
      | None ->
        acc
    acc *- ";" *- eol
  | CStmt.LetAlloc (name, valPtrTy, varTy) ->
    let valTy =
      match valPtrTy with
      | CTy.Ptr ty -> ty
      | _ -> failwithf "Expected pointer type but %A" valPtrTy
    let acc = acc *- indent
    let acc = cprintTy acc varTy
    let acc = acc *- " " *- name *- " = ("
    let acc = cprintTy acc varTy
    let acc = acc *- ")malloc(sizeof("
    let acc = cprintTy acc valTy
    let acc = acc *- "));" *- eol
    acc
  | CStmt.Set (l, r) ->
    let acc = acc *- indent
    let acc = cprintExpr acc l *- " = "
    let acc = cprintExpr acc r *- ";" *- eol
    acc
  | CStmt.Label label ->
    acc *- label *- ":;" *- eol
  | CStmt.Goto label ->
    acc *- indent *- "goto " *- label *- ";" *- eol
  | CStmt.GotoUnless (pred, label) ->
    let acc = acc *- indent *- "if (!("
    let acc = cprintExpr acc pred
    let acc = acc *- ")) goto " *- label *- ";" *- eol
    acc

let rec cprintStmts acc indent stmts: string list =
  match stmts with
  | [] ->
    acc
  | stmt :: stmts ->
    let acc = cprintStmt acc indent stmt
    cprintStmts acc indent stmts

let cprintDecl acc decl =
  match decl with
  | CDecl.Struct (ident, fields) ->
    let acc = acc *- "struct " *- ident *- " {" *- eol
    let rec go acc fields =
      match fields with
      | [] -> acc
      | (ident, ty) :: fields ->
        let acc = acc *- "    "
        let acc = cprintTy acc ty
        let acc = acc *- " " *- ident *- ";" *- eol
        go acc fields
    let acc = go acc fields
    let acc = acc *- "};" *- eol
    acc
  | CDecl.Enum (tyIdent, variants) ->
    let acc = acc *- "enum " *- tyIdent *- " {" *- eol
    let rec go acc variants =
      match variants with
      | [] -> acc
      | variant :: variants ->
        let acc = acc *- "    "
        let acc = acc *- variant *- "," *- eol
        go acc variants
    let acc = go acc variants
    let acc = acc *- "};" *- eol
    acc
  | CDecl.Fun (ident, args, resultTy, body) ->
    let acc = cprintTy acc resultTy
    let acc = acc *- " " *- ident *- "("
    let acc = cprintParams acc args
    let acc = acc *- ") {" *- eol
    let acc = cprintStmts acc "    " body
    let acc = acc *- "}" *- eol
    acc

let rec cprintDecls acc decls =
  let rec go acc decls =
    match decls with
    | [] ->
      acc
    | [decl] ->
      cprintDecl acc decl
    | decl :: decls ->
      let acc = cprintDecl acc decl *- eol
      go acc decls
  go acc decls

let cprintHeader acc =
  let header = """#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
  char* str;
  int len;
};

int int_cmp(int l, int r) {
  if (l == r) return 0;
  if (l < r) return -1;
  return 1;
}

int int_clamp(int x, int l, int r) {
  if (x < l) return l;
  if (x > r) return r;
  return x;
}

int str_cmp(struct String left, struct String right) {
  return strcmp(left.str, right.str);
}

struct String str_add(struct String left, struct String right) {
  if (left.len == 0 || right.len == 0) {
    return right.len == 0 ? left : right;
  }
  int len = left.len + right.len;
  char* str = (char*)malloc((len + 1) * sizeof(char));
  strcpy(str, left.str);
  strcpy(str + left.len, right.str);
  return (struct String){.str = str, .len = len};
}

struct String str_slice(struct String s, int l, int r) {
  l = int_clamp(l, 0, s.len);
  r = int_clamp(r + 1, l, s.len);
  int len = r - l;
  char* str;
  if (r == s.len) {
    str = s.str + l;
  } else {
    str = (char*)malloc((len + 1) * sizeof(char));
    strncpy(str, s.str + l, len);
    str[len] = '\0';
  }
  return (struct String){.str = str, .len = len};
}
"""
  acc *- header *- eol

let cprintRun (printer: string list -> string list): string =
  printer [] |> List.rev |> String.concat ""

let cprint (decls: CDecl list): string =
  cprintRun (fun acc -> cprintDecls (cprintHeader acc) decls)
