module rec MiloneLang.SemaNameResolve

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Sema

module M = Std.StdMap

let private desugarLetDecl isRec vis pat body pos =
  match pat with
  | AAscribePat (pat, ascriptionTy, ascriptionLoc) ->
    let body =
      AAscribeExpr(body, ascriptionTy, ascriptionLoc)

    desugarLetDecl isRec vis pat body pos

  | AFunDeclPat (name, args) -> ALetFunDecl(isRec, vis, name, args, body, pos)

  | _ -> ALetValDecl(isRec, vis, pat, body, pos)

// -----------------------------------------------
// Context
// -----------------------------------------------

type Ctx = { Db: SemaDb }

let newCtx (db: SemaDb) : Ctx = { Db = db }

let finishCtx (ctx: Ctx) : SemaDb = ctx.Db

let private todo () = failwithf "TODO"

// -----------------------------------------------
// Engine
// -----------------------------------------------

let defineSymbolAsValueInLocal name ctx = ctx

let defineSymbolAsTypeInLocal name ctx = ctx

let defineSymbolAsModuleInLocal name ctx = ctx

let importName name ctx = ctx

let importAllFrom path ctx = ctx

// -----------------------------------------------
// Declaration phase
// -----------------------------------------------

let defineSymbolsInPat pat ctx =
  match pat with
  | AMissingPat _
  | ALitPat _ -> ctx

  | AIdentPat name -> defineSymbolAsValueInLocal name ctx

  | ANavPat (l, _, _) -> ctx |> defineSymbolsInPat l
  | AListPat (pats, _) -> ctx |> forList defineSymbolsInPat pats
  | AConsPat (l, r, _) ->
    ctx
    |> defineSymbolsInPat l
    |> defineSymbolsInPat r
  | ATuplePat (pats, _) -> ctx |> forList defineSymbolsInPat pats

  | AAppPat (l, r, _) ->
    ctx
    |> defineSymbolAsValueInLocal l
    |> defineSymbolAsValueInLocal r

  | AAsPat (body, name, _) ->
    ctx
    |> defineSymbolsInPat body
    |> defineSymbolAsValueInLocal name

  | AAscribePat (body, _, _) -> defineSymbolsInPat body ctx

  | AOrPat (l, _, _) -> defineSymbolsInPat l ctx

  | AFunDeclPat (name, _) -> defineSymbolAsValueInLocal name ctx

let declareDecl decl ctx =
  match decl with
  | AExprDecl _ -> ctx

  | ALetDecl (_, _, pat, _, _) -> ctx |> defineSymbolsInPat pat

  | ATySynonymDecl (_, name, _, _, _) -> ctx |> defineSymbolAsTypeInLocal name

  | AUnionTyDecl (_, name, variants, _) ->
    let declareVariant (AVariant (name, _, _)) ctx = defineSymbolAsValueInLocal name ctx

    ctx
    |> defineSymbolAsTypeInLocal name
    |> forList declareVariant variants

  | ARecordTyDecl (_, name, _, _) -> ctx |> defineSymbolAsTypeInLocal name

  | AOpenDecl (path, _) -> ctx |> importAllFrom path

  | AModuleSynonymDecl (name, path, _) -> ctx |> defineSymbolAsModuleInLocal name

  | AModuleDecl _ -> todo ()

  | AAttrDecl (_, next, _) -> ctx |> declareDecl next

// -----------------------------------------------
// Resolution phase
// -----------------------------------------------

let resolveDecl decl ctx = ctx

let resolveDecls (decls: ADecl list) ctx : Ctx =
  ctx
  |> forList declareDecl decls
  |> forList resolveDecl decls

// -----------------------------------------------
// Interface
// -----------------------------------------------

let resolveNames (ast: ARoot) (db: SemaDb) : SemaDb =
  match ast with
  | AExprRoot _ -> todo ()

  | AModuleRoot (_, decls, _) -> newCtx db |> resolveDecls decls |> finishCtx
