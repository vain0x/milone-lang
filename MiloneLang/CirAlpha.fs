// Alpha conversion.

module rec MiloneLang.CirAlpha

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Cir

let forList folder xs ctx =
  List.fold (fun ctx x -> folder x ctx) ctx xs

let caExpr ctx expr =
  match expr with
  | CDefaultExpr
  | CIntExpr _
  | CDoubleExpr _
  | CCharExpr _
  | CStrRawExpr _
  | CStrObjExpr _
  | CVarExpr (CPublicIdent _)
  | CSizeOfExpr _
  | CNativeExpr _ -> expr

  | CVarExpr (CPrivateIdent (name, serial)) -> CVarExpr(CPublicIdent(name + "_" + intToHexWithPadding 0 serial))

  | CInitExpr (fields, ty) ->
      let fields =
        fields
        |> List.map (fun (ident, expr) -> ident, caExpr ctx expr)

      CInitExpr(fields, ty)

  | CCastExpr (arg, ty) ->
      let arg = caExpr ctx arg
      CCastExpr(arg, ty)

  | CDotExpr (l, r) -> CDotExpr(caExpr ctx l, r)

  | CArrowExpr (l, r) -> CArrowExpr(caExpr ctx l, r)

  | CIndexExpr (l, r) -> CIndexExpr(caExpr ctx l, caExpr ctx r)

  | CCallExpr (f, args) -> CCallExpr(caExpr ctx f, List.map (caExpr ctx) args)
  | CUnaryExpr (unary, arg) -> CUnaryExpr(unary, caExpr ctx arg)
  | CBinaryExpr (binary, l, r) -> CBinaryExpr(binary, caExpr ctx l, caExpr ctx r)

let caStmt ctx stmt =
  match stmt with
  | CLabelStmt _
  | CGotoStmt _
  | CNativeStmt _ -> stmt

  | CExprStmt expr -> CExprStmt(caExpr ctx expr)

  | CLetStmt (ident, init, ty) -> CLetStmt(ident, Option.map (caExpr ctx) init, ty)

  | CLetAllocStmt (ident, valTy, varTy) -> CLetAllocStmt(ident, valTy, varTy)

  | CSetStmt (l, r) -> stmt

  | CGotoIfStmt (cond, label) -> stmt

  | CIfStmt (cond, body, alt) -> stmt

  | CSwitchStmt (cond, clauses) -> stmt

  | CReturnStmt resultOpt -> stmt

let caStmts ctx stmts = stmts |> List.map (caStmt ctx), ctx

let caDecl ctx decl =
  match decl with
  | CErrorDecl _
  | CStructDecl _
  | CEnumDecl _
  | CStaticVarDecl _
  | CFunForwardDecl _
  | CNativeDecl _ -> decl

  | CFunDecl (funName, args, resultTy, body) ->
      let body, ctx = caStmts ctx body
      CFunDecl(funName, args, resultTy, body)

let caDecls ctx decls = ()
