/// # SemaAnalyze

module rec MiloneLang.SemaAnalyze

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers

let private todo () = failwith "todo"

// -----------------------------------------------
// classifyLetDecl
// -----------------------------------------------

[<NoEquality; NoComparison>]
type ALetDecl =
  | ALetFunDecl of Vis * Ident * APat list * AExpr * Pos
  | ALetValDecl of Vis * APat * AExpr * Pos

let private classifyLetDecl letDecl =
  let rec desugar vis pat init pos =
    match pat with
    | AAnnoPat (bodyPat, annotTy, annotPos) -> desugar vis bodyPat (AAnnoExpr(init, annotTy, annotPos)) pos

    | AFunDeclPat (name, args, _) -> ALetFunDecl(vis, name, args, init, pos)

    | _ -> ALetValDecl(vis, pat, init, pos)

  match letDecl with
  | ALetDecl (vis, pat, init, pos) -> desugar vis pat init pos
  | _ -> failwith "NEVER"

// -----------------------------------------------
// Early pass
// -----------------------------------------------

let private saPatEarly vis pat ctx =
  match pat with
  | AMissingPat _ -> todo ()

  | AIdentPat (name, pos) ->
    // this is static var
    todo ()

  | _ -> todo ()

let private saLetValDeclEarly vis pat init pos ctx =
  // define function with name, arity, provisional type scheme, pos (loc)
  // add vars to namespace if public
  // import to scope
  todo ()

let private saLetFunDeclEarly vis funName paramPats pos ctx =
  // check if main or not
  // define function with name, arity, provisional type scheme, pos (loc)
  // add to namespace if public
  // import to scope
  todo ()

let private saDeclEarly decl ctx =
  match decl with
  | AExprDecl expr -> todo ()

  | ALetDecl _ ->
    match classifyLetDecl decl with
    | ALetValDecl (vis, pat, init, pos) -> saLetValDeclEarly vis pat init pos ctx

    | ALetFunDecl (vis, funName, paramPats, body, pos) -> saLetFunDeclEarly vis funName paramPats body pos ctx

  | ATySynonymDecl (vis, synonymName, tyArgs, bodyTy, pos) ->
    // define type synonym: name, provisional body type, pos
    // add to module namespace if public
    // import to scope
    // add to type decl queue
    todo ()

  | AUnionTyDecl (vis, unionName, variantDecls, pos) ->
    // define union type: name, no variants, pos
    // for each variant:
    //    add to union namespace
    //    add to module namespace if public
    //    import to scope
    // set variants
    // add to module namespace if public
    // import to scope
    // add to type decl queue

    todo ()

  | ARecordTyDecl (vis, recordName, fieldDecls, pos) ->
    // define record type: name, field with provisional types, pos
    // add to namespace if public
    // import to scope
    // add to type decl queue
    todo ()

  | AOpenDecl (path, pos) ->
    // find project name by first segment of path
    // find module by second segment of path; or error
    // import symbols in the module to scope
    todo ()

  | AAttrDecl (_, next, _) -> saDeclEarly next ctx

// -----------------------------------------------
// Declarations (late pass)
// -----------------------------------------------

let private saDeclLate decl ctx =
  match decl with
  | AExprDecl expr -> todo ()

  | ALetDecl _ ->
    match classifyLetDecl decl with
    | ALetValDecl _ ->
      // do same as early pass if not yet
      // enter scope
      //    process init
      //    process pat (irrefutable)
      // leave scope
      todo ()

    | ALetFunDecl _ ->
      // do same as early pass if not yet
      // enter scope, inc level, stash trait queue
      //    process arg pats
      //    unify function type created by patterns to provisional type
      //    process body
      //    resolve traits
      // leave scope, dec level, restore trait queue
      // generalize
      todo ()

  | ATySynonymDecl (vis, synonymName, tyArgs, bodyTy, pos) ->
    // do same as early pass if not yet
    // enter scope
    //    define type args
    //    process body type
    // leave scope
    // update data
    todo ()

  | AUnionTyDecl (vis, unionName, variantDecls, pos) ->
    // do same as early pass if not yet
    // resolve variant payload types
    todo ()

  | ARecordTyDecl (vis, recordName, fieldDecls, pos) -> todo ()

  | AOpenDecl (path, pos) ->
    // do nothing
    todo ()

  | AAttrDecl (_, next, _) -> saDeclLate next ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

// let semaAnalyze (ctx: SemaDb) (root: ARoot) (docId: DocId): BProgram * SemaDb =
//   match root with
//   | AExprRoot decls -> (decls, nameCtx) |> athDecls docId

//   | AModuleRoot (moduleName, body, pos) ->
//       let body, nameCtx = (body, nameCtx) |> athDecls docId
//       let serial, nameCtx = nameCtx |> nameCtxAdd moduleName
//       let loc = toLoc docId pos
//       [ HModuleExpr(ModuleTySerial serial, body, loc) ], nameCtx
