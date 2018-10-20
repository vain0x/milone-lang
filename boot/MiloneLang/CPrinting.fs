/// Prints C language code from C language IR.
module rec MiloneLang.CPrinting

open System

let ( *- ) acc second =
  second :: acc

let eol = Environment.NewLine

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
  | COp.Gt -> ">"
  | COp.Ge -> ">="

let valVariantName vTy =
  match vTy with
  | CValTy.Int -> "i"
  | CValTy.Str -> "s"
  | CValTy.Tuple _ -> "t"

let tupleFn ty =
  match ty with
  | CValTy.Int -> "tuple_i"
  | CValTy.Str -> "tuple_s"
  | CValTy.Tuple _ -> failwith "unimpl"

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
  | CTy.Val _ ->
    acc *- "Val"

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

let rec cprintExpr acc expr: string list =
  let rec cprintExprList acc index separator exprs =
    match exprs with
    | [] -> acc
    | expr :: exprs ->
      let acc = if index > 0 then acc *- separator else acc
      let acc = cprintExpr acc expr
      cprintExprList acc 1 separator exprs
  match expr with
  | CExpr.Int value ->
    acc *- string value
  | CExpr.Str value ->
    acc *- "\"" *- value *- "\""
  | CExpr.Val (expr, vTy) ->
    let acc = acc *- "(Val){." *- valVariantName vTy *- " = "
    let acc = cprintExpr acc expr
    acc *- "}"
  | CExpr.Ref (value, _) ->
    acc *- value
  | CExpr.Prim CPrim.Malloc ->
    acc *- "malloc"
  | CExpr.Prim CPrim.Printf ->
    acc *- "printf"
  | CExpr.Prim (CPrim.Tuple ty) ->
    acc *- tupleFn ty
  | CExpr.Arrow (left, field, _) ->
    let acc = cprintExpr acc left
    acc *- "->" *- field
  | CExpr.Cast (expr, ty) ->
    let acc = acc *- "(("
    let acc = cprintTy acc ty
    let acc = acc *- ")"
    let acc = cprintExpr acc expr
    let acc = acc *- ")"
    acc
  | CExpr.Op (op, first, second, _) ->
    let acc = acc *- "("
    let acc = cprintExpr acc first
    let acc = acc *- " " *- opStr op *- " "
    let acc = cprintExpr acc second
    let acc = acc *- ")"
    acc
  | CExpr.Call (callee, args, _) ->
    let acc = cprintExpr acc callee
    let acc = acc *- "("
    let acc = cprintExprList acc 0 ", " args
    let acc = acc *- ")"
    acc
  | CExpr.Set (l, r, _) ->
    let acc = cprintExpr acc l *- " = "
    let acc = cprintExpr acc r
    acc

let cprintStmt acc indent stmt: string list =
  let acc = acc *- indent
  match stmt with
  | CStmt.Return None ->
    acc *- "return;" *- eol
  | CStmt.Return (Some expr) ->
    let acc = acc *- "return "
    let acc = cprintExpr acc expr
    acc *- ";" *- eol
  | CStmt.Expr expr ->
    let acc = cprintExpr acc expr
    acc *- ";" *- eol
  | CStmt.Let (name, ty, init) ->
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
  | CStmt.LetTuple2 (name, l, r) ->
    let acc = acc *- "Val " *- name *- " = {.t = malloc(2 * sizeof(Val))};" *- eol *- indent
    let acc = acc *- name *- ".t[0] = "
    let acc = cprintExpr acc l
    let acc = acc *- ";" *- eol *- indent
    let acc = acc *- name *- ".t[1] = "
    let acc = cprintExpr acc r
    let acc = acc *- ";" *- eol
    acc
  | CStmt.If (pred, thenStmts, elseStmts) ->
    let acc = acc *- "if ("
    let acc = cprintExpr acc pred
    let acc = acc *- ") {" *- eol
    let acc = cprintStmts acc (indent + "    ") thenStmts
    let acc = acc *- indent *- "} else {" *- eol
    let acc = cprintStmts acc (indent + "    ") elseStmts
    let acc = acc *- indent *- "}" *- eol
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
  | CDecl.Fun decl ->
    let acc = acc *- "int" *- " " *- decl.Name *- "("
    let acc = cprintParams acc decl.Params
    let acc = acc *- ") {" *- eol
    let acc = cprintStmts acc "    " decl.Body
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

typedef union Val {
  int i;
  char* s;
  union Val* t;
} Val;

int tuple_i(Val v, int i) { return v.t[i].i; }
char* tuple_s(Val v, int i) { return v.t[i].s; }
"""
  acc *- header *- eol

let cprintRun (printer: string list -> string list): string =
  printer [] |> List.rev |> String.concat ""

let cprint (decls: CDecl list): string =
  cprintRun (fun acc -> cprintDecls (cprintHeader acc) decls)
