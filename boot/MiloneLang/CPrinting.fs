/// Converts C-IR to C language code.
/// Includes runtime functions.
module rec MiloneLang.CPrinting

open MiloneLang.Types
open MiloneLang.Helpers

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
      let acc = acc |> cons sep
      go acc xs
  go acc xs

let opStr op =
  match op with
  | CBinOp.Add -> "+"
  | CBinOp.Sub -> "-"
  | CBinOp.Mul -> "*"
  | CBinOp.Div -> "/"
  | CBinOp.Mod -> "%"
  | CBinOp.Eq -> "=="
  | CBinOp.Ne -> "!="
  | CBinOp.Lt -> "<"
  | CBinOp.Le -> "<="

let cprintTyFunPtr name argTys resultTy acc =
  let acc = cprintTy acc resultTy
  let acc = acc |> cons "(*" |> cons name |> cons ")" |> cons "("
  let rec go acc argTys =
    (argTys, acc) |> join ", " (fun (argTy, acc) ->
      cprintTy acc argTy
    )
  let acc = go acc argTys
  acc |> cons ")"

let rec cprintTy acc ty: string list =
  match ty with
  | CTy.Void ->
    acc |> cons "void"
  | CTy.Int ->
    acc |> cons "int"
  | CTy.Char ->
    acc |> cons "char"
  | CTy.Ptr ty ->
    let acc = cprintTy acc ty
    acc |> cons "*"
  | CTy.FunPtr (argTys, resultTy) ->
    cprintTyFunPtr "" argTys resultTy acc
  | CTy.Struct ident ->
    acc |> cons "struct " |> cons ident
  | CTy.Enum ident ->
    acc |> cons "enum " |> cons ident

/// `T x` or `T (*x)(..)`
let cprintTyWithName acc name ty =
  match ty with
  | CTy.FunPtr (argTys, resultTy) ->
    cprintTyFunPtr name argTys resultTy acc
  | _ ->
    cprintTy acc ty |> cons " " |> cons name

let rec cprintParams acc ps: string list =
  let rec go acc ps =
    match ps with
    | [] -> acc
    | [name, ty] ->
      cprintTy acc ty |> cons " " |> cons name
    | (name, ty) :: ps ->
      let acc = cprintTy acc ty
      let acc = acc |> cons " " |> cons name |> cons ", "
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
        go (acc |> cons "\\0") (i + 1)
      | '\r' ->
        go (acc |> cons "\\r") (i + 1)
      | '\n' ->
        go (acc |> cons "\\n") (i + 1)
      | '\t' ->
        go (acc |> cons "\\t") (i + 1)
      | '\"' ->
        go (acc |> cons "\\\"") (i + 1)
      | '\\' ->
        go (acc |> cons "\\\\") (i + 1)
      | _ ->
        go (acc |> cons (string value.[i])) (i + 1)
  go (acc |> cons "\"") 0 |> cons "\""

let cprintExprStrObj acc (value: string) =
  let acc = acc |> cons "(struct String){.str = "
  let acc = cprintExprStrRaw acc value
  let acc = acc |> cons ", .len = " |> cons (string value.Length) |> cons "}"
  acc

let cprintExprInit acc fields ty =
  let acc = acc |> cons "("
  let acc = cprintTy acc ty
  let acc = acc |> cons "){"
  let acc =
    (fields, acc) |> join ", " (fun ((field, value), acc) ->
      let acc = acc |> cons "." |> cons field |> cons " = "
      let acc = cprintExpr acc value
      acc
    )
  let acc = acc |> cons "}"
  acc

let rec cprintExpr acc expr: string list =
  let rec cprintExprList acc index separator exprs =
    match exprs with
    | [] -> acc
    | expr :: exprs ->
      let acc = if index > 0 then acc |> cons separator else acc
      let acc = cprintExpr acc expr
      cprintExprList acc 1 separator exprs
  match expr with
  | CExpr.Default ->
    acc |> cons "{}"
  | CExpr.Int value ->
    acc |> cons (string value)
  | CExpr.Char value ->
    acc |> cons "'" |> cons (cprintExprChar value) |> cons "'"
  | CExpr.StrObj value ->
    cprintExprStrObj acc value
  | CExpr.StrRaw value->
    cprintExprStrRaw acc value
  | CExpr.Init (fields, ty) ->
    cprintExprInit acc fields ty
  | CExpr.Nav (CExpr.StrObj value, "len") ->
    acc |> cons (string value.Length)
  | CExpr.Ref (value) ->
    acc |> cons value
  | CExpr.Proj (left, index) ->
    let acc = cprintExpr acc left
    acc |> cons ".t" |> cons (string index)
  | CExpr.Cast (expr, ty) ->
    let acc = acc |> cons "(("
    let acc = cprintTy acc ty
    let acc = acc |> cons ")"
    let acc = cprintExpr acc expr
    let acc = acc |> cons ")"
    acc
  | CExpr.Nav (expr, field) ->
    let acc = cprintExpr acc expr
    let acc = acc |> cons "." |> cons field
    acc
  | CExpr.Arrow (expr, field) ->
    let acc = cprintExpr acc expr
    let acc = acc |> cons "->" |> cons field
    acc
  | CExpr.Index (l, r) ->
    let acc = cprintExpr acc l
    let acc = acc |> cons "["
    let acc = cprintExpr acc r
    let acc = acc |> cons "]"
    acc
  | CExpr.Call (callee, args) ->
    let acc = cprintExpr acc callee
    let acc = acc |> cons "("
    let acc = cprintExprList acc 0 ", " args
    let acc = acc |> cons ")"
    acc
  | CExpr.Uni (op, arg) ->
    let acc = acc |> cons "("
    let acc =
      match op with
      | CUniOp.Not -> acc |> cons "!"
      | CUniOp.Deref -> acc |> cons "*"
    let acc = acc |> cons "("
    let acc = cprintExpr acc arg
    let acc = acc |> cons "))"
    acc
  | CExpr.Bin (op, first, second) ->
    let acc = acc |> cons "("
    let acc = cprintExpr acc first
    let acc = acc |> cons " " |> cons (opStr op) |> cons " "
    let acc = cprintExpr acc second
    let acc = acc |> cons ")"
    acc

let cprintStmt acc indent stmt: string list =
  match stmt with
  | CStmt.Return None ->
    acc |> cons indent |> cons "return;" |> cons eol
  | CStmt.Return (Some expr) ->
    let acc = acc |> cons indent |> cons "return "
    let acc = cprintExpr acc expr
    acc |> cons ";" |> cons eol
  | CStmt.Expr expr ->
    let acc = acc |> cons indent
    let acc = cprintExpr acc expr
    acc |> cons ";" |> cons eol
  | CStmt.Let (name, init, ty) ->
    let acc = acc |> cons indent
    let acc = cprintTyWithName acc name ty
    let acc =
      match init with
      | Some init ->
        let acc = acc |> cons " = "
        cprintExpr acc init
      | None ->
        acc
    acc |> cons ";" |> cons eol
  | CStmt.LetAlloc (name, valPtrTy, varTy) ->
    let valTy =
      match valPtrTy with
      | CTy.Ptr ty -> ty
      | _ -> failwithf "Never: Expected pointer type but %A" valPtrTy
    let acc = acc |> cons indent
    let acc = cprintTyWithName acc name varTy
    let acc = acc |> cons " = ("
    let acc = cprintTy acc varTy
    let acc = acc |> cons ")malloc(sizeof("
    let acc = cprintTy acc valTy
    let acc = acc |> cons "));" |> cons eol
    acc
  | CStmt.Set (l, r) ->
    let acc = acc |> cons indent
    let acc = cprintExpr acc l |> cons " = "
    let acc = cprintExpr acc r |> cons ";" |> cons eol
    acc
  | CStmt.Label label ->
    acc |> cons label |> cons ":;" |> cons eol
  | CStmt.Goto label ->
    acc |> cons indent |> cons "goto " |> cons label |> cons ";" |> cons eol
  | CStmt.GotoUnless (pred, label) ->
    let acc = acc |> cons indent |> cons "if (!("
    let acc = cprintExpr acc pred
    let acc = acc |> cons ")) goto " |> cons label |> cons ";" |> cons eol
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
  | CDecl.ErrDir (message, line) ->
    let acc = acc |> cons "#line " |> cons (string line) |> cons eol
    let acc = acc |> cons "#error " |> cons message |> cons eol
    acc
  | CDecl.Struct (ident, fields, variants) ->
    let cprintFields indent acc fields =
      let rec go acc fields =
        match fields with
        | [] ->
          acc
        | (ident, ty) :: fields ->
          let acc = acc |> cons indent
          let acc = cprintTyWithName acc ident ty
          let acc = acc |> cons ";" |> cons eol
          go acc fields
      go acc fields
    let acc = acc |> cons "struct " |> cons ident |> cons " {" |> cons eol
    let acc = cprintFields "    " acc fields
    let acc =
      match variants with
      | [] ->
        acc
      | _ ->
        let acc = acc |> cons "    union {" |> cons eol
        let acc = cprintFields "        " acc variants
        let acc = acc |> cons "    };" |> cons eol
        acc
    let acc = acc |> cons "};" |> cons eol
    acc
  | CDecl.Enum (tyIdent, variants) ->
    let acc = acc |> cons "enum " |> cons tyIdent |> cons " {" |> cons eol
    let rec go acc variants =
      match variants with
      | [] -> acc
      | variant :: variants ->
        let acc = acc |> cons "    "
        let acc = acc |> cons variant |> cons "," |> cons eol
        go acc variants
    let acc = go acc variants
    let acc = acc |> cons "};" |> cons eol
    acc
  | CDecl.Fun (ident, args, resultTy, body) ->
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
  | CDecl.ErrDir _ ->
    acc
  | CDecl.Struct (ident, _, _) ->
    let acc = acc |> cons "struct " |> cons ident |> cons ";" |> cons eol |> cons eol
    acc
  | CDecl.Enum (tyIdent, _) ->
    let acc = acc |> cons "enum " |> cons tyIdent |> cons ";" |> cons eol |> cons eol
    acc
  | CDecl.Fun (ident, args, resultTy, _) ->
    let acc = cprintTyWithName acc ident resultTy
    let acc = acc |> cons "("
    let acc = cprintParams acc args
    let acc = acc |> cons ");" |> cons eol |> cons eol
    acc

let rec cprintDeclForwards acc decls =
  let rec go acc decls =
    match decls with
    | [] ->
      acc
    | decl :: decls ->
      let acc = cprintDeclForward acc decl
      go acc decls
  go acc decls

let rec cprintDecls acc decls =
  let acc = cprintDeclForwards acc decls
  let rec go acc decls =
    match decls with
    | [] ->
      acc
    | [decl] ->
      cprintDecl acc decl
    | decl :: decls ->
      let acc = cprintDecl acc decl |> cons eol
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

int str_to_int(struct String s) {
  return atoi(s.str);
}

struct String str_of_int(int value) {
  char* str = calloc(20, sizeof(char));
  sprintf(str, "%d", value);
  return (struct String){.str = str, .len = strlen(str)};
}

struct String str_of_char(char value) {
  char* str = calloc(2, sizeof(char));
  str[0] = value;
  return (struct String){.str = str, .len = strlen(str)};
}

void milone_assert(int cond) {
  if (!cond) {
    exit(1);
  }
}

struct String file_read_all_text(struct String file_name) {
  FILE *fp = fopen(file_name.str, "r");
  if (!fp) {
    fprintf(stderr, "File '%s' not found.", file_name.str);
    abort();
  }

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  if (size < 0) {
    fclose(fp);
    fprintf(stderr, "%s", "Couldn't retrieve the file size.");
    abort();
  }
  fseek(fp, 0, SEEK_SET);

  char *content = calloc((size_t)size + 1, sizeof(char));
  size_t read_size = fread(content, 1, (size_t)size, fp);
  if (read_size != (size_t)size) {
    fclose(fp);
    fprintf(stderr, "%s", "Couldn't retrieve the file contents");
    abort();
  }

  fclose(fp);
  return (struct String){.str = content, .len = size};
}

int file_write_all_text(struct String file_name, struct String content) {
  FILE *fp = fopen(file_name.str, "w");
  if (!fp) {
    fprintf(stderr, "File '%s' not found.", file_name.str);
    abort();
  }

  fprintf(fp, "%s", content.str);

  fclose(fp);
  return 0;
}

static int s_argc;
static char **s_argv;

int arg_count(int _unit) {
  return s_argc;
}

struct String arg_get(int index) {
  if (!(0 <= index && index < s_argc)) {
    abort();
  }

  char *str = s_argv[index];
  int len = strlen(str);
  return (struct String){.str = str, .len = len};
}

int main(int argc, char** argv) {
  s_argc = argc - 1;
  s_argv = argv + 1;

  int milone_main();
  return milone_main();
}

#define main milone_main
"""
  acc |> cons header |> cons eol

let cprintRun (printer: string list -> string list): string =
  printer [] |> List.rev |> String.concat ""

let cprint (decls: CDecl list): string =
  cprintRun (fun acc -> cprintDecls (cprintHeader acc) decls)
