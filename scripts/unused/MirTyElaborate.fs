/// # MirTyElaborate
module rec MiloneLang.MirTyElaborate

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Mir
open MiloneLang.MirGen

// -----------------------------------------------
// Context
// -----------------------------------------------

// [<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MteCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    NewTys: (TySerial * TyDef) list
    TupleMemo: AssocMap<Ty list, Ty> }

let private ofMirCtx (mirCtx: MirCtx): MteCtx =
  { Serial = mirCtx.Serial
    Vars = mirCtx.Vars
    Funs = mirCtx.Funs
    Variants = mirCtx.Variants
    Tys = mirCtx.Tys
    NewTys = []
    TupleMemo = mapEmpty (listCmp tyCmp) }

let private toMirCtx (mirCtx: MirCtx) (ctx: MteCtx) =
  { mirCtx with
      Serial = ctx.Serial
      Vars = ctx.Vars
      Funs = ctx.Funs
      Variants = ctx.Variants
      Tys = ctx.Tys }

let private freshTySerial (ctx: MteCtx) =
  ctx.Serial + 1, { ctx with Serial = ctx.Serial + 1 }

let private getUniqueTyName (ctx: MteCtx) ty =
  let rec go ty =
    let nominal tySerial _tyArgs =
      ctx.Tys |> mapFind tySerial |> tyDefToName

    match ty with
    | AppTy (BoolTyCtor, _) -> "Bool"
    | AppTy (IntTyCtor, _) -> "Int"
    | AppTy (UIntTyCtor, _) -> "UInt"
    | AppTy (CharTyCtor, _) -> "Char"
    | AppTy (StrTyCtor, _) -> "String"

    | MetaTy _
    | AppTy (ObjTyCtor, _) -> "Object"

    | AppTy (FunTyCtor, _) ->
        let arity, argTys, resultTy = tyToArgList ty

        let argTys = argTys |> List.map go
        let resultTy = go resultTy

        let funTy =
          (argTys |> strConcat)
          + resultTy
          + "Fun"
          + string arity

        funTy

    | AppTy (ListTyCtor, tyArgs) ->
        match tyArgs with
        | [ itemTy ] -> go itemTy + "List"

        | _ -> failwith "NEVER"

    | AppTy (TupleTyCtor, []) -> "Unit"

    | AppTy (TupleTyCtor, itemTys) ->
        let itemTys = itemTys |> List.map go
        let len = itemTys |> List.length
        (itemTys |> strConcat) + "Tuple" + string len

    | AppTy (SynonymTyCtor tySerial, tyArgs) -> nominal tySerial tyArgs
    | AppTy (UnionTyCtor tySerial, tyArgs) -> nominal tySerial tyArgs
    | AppTy (RecordTyCtor tySerial, tyArgs) -> nominal tySerial tyArgs

    | AppTy (UnresolvedTyCtor _, _)
    | ErrorTy _ ->
        // FIXME: collect error
        failwithf "/* unknown ty %A */" ty

  go ty

// -----------------------------------------------
// Tuples to Records
// -----------------------------------------------

let private tupleToRecord (ctx: MteCtx) itemTys =
  match ctx.TupleMemo |> mapTryFind itemTys with
  | Some it -> it, ctx
  | None ->
      let tySerial, ctx = freshTySerial ctx
      let recordTy = AppTy(RecordTyCtor tySerial, [])

      let recordName =
        (itemTys
         |> List.map (getUniqueTyName ctx)
         |> strConcat)
        + "Tuple"
        + string (List.length itemTys)

      // printfn "/* new tuple %s -> %s */" (objToString tyArgs) recordName

      let fields =
        itemTys
        |> List.mapi (fun (i: int) fieldTy -> "t" + string i, fieldTy, noLoc)

      let tyDef = RecordTyDef(recordName, fields, noLoc)

      let ctx =
        { ctx with
            Tys = ctx.Tys |> mapAdd tySerial tyDef
            NewTys = (tySerial, tyDef) :: ctx.NewTys
            TupleMemo = ctx.TupleMemo |> mapAdd itemTys recordTy }

      recordTy, ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private mteTy (ty: Ty, ctx: MteCtx) =
  match ty with
  | ErrorTy _
  | MetaTy _
  | AppTy (_, []) -> ty, ctx

  | AppTy (tyCtor, tyArgs) ->
      // printfn "/* hit ty=%s */" (objToString ty)

      let tyArgs, ctx = (tyArgs, ctx) |> stMap mteTy

      match tyCtor with
      | TupleTyCtor -> tupleToRecord ctx tyArgs

      | _ -> AppTy(tyCtor, tyArgs), ctx

let private mteExpr (expr: MExpr, ctx: MteCtx) =
  match expr with
  | MLitExpr _
  | MTagExpr _ -> expr, ctx

  | MDefaultExpr (ty, loc) ->
      let ty, ctx = (ty, ctx) |> mteTy
      MDefaultExpr(ty, loc), ctx

  | MRefExpr (varSerial, ty, loc) ->
      let ty, ctx = (ty, ctx) |> mteTy
      MRefExpr(varSerial, ty, loc), ctx

  | MProcExpr (funSerial, ty, loc) ->
      let ty, ctx = (ty, ctx) |> mteTy
      MProcExpr(funSerial, ty, loc), ctx

  | MVariantExpr (tySerial, variantSerial, ty, loc) ->
      let ty, ctx = (ty, ctx) |> mteTy
      MVariantExpr(tySerial, variantSerial, ty, loc), ctx

  | MUnaryExpr (unary, arg, resultTy, loc) ->
      let arg, ctx = (arg, ctx) |> mteExpr
      let resultTy, ctx = (resultTy, ctx) |> mteTy
      MUnaryExpr(unary, arg, resultTy, loc), ctx

  | MBinaryExpr (binary, l, r, resultTy, loc) ->
      let l, ctx = (l, ctx) |> mteExpr
      let r, ctx = (r, ctx) |> mteExpr
      let resultTy, ctx = (resultTy, ctx) |> mteTy
      MBinaryExpr(binary, l, r, resultTy, loc), ctx

let private mteInit (init, ctx: MteCtx) =
  match init with
  | MUninitInit
  | MClosureInit _ -> init, ctx

  | MExprInit expr ->
      let expr, ctx = (expr, ctx) |> mteExpr
      MExprInit expr, ctx

  | MCallPrimInit (prim, args, primTy) ->
      let args, ctx = (args, ctx) |> stMap mteExpr
      let primTy, ctx = (primTy, ctx) |> mteTy
      MCallPrimInit(prim, args, primTy), ctx

  | MCallProcInit (callee, args, calleeTy) ->
      let callee, ctx = (callee, ctx) |> mteExpr
      let args, ctx = (args, ctx) |> stMap mteExpr
      let calleeTy, ctx = (calleeTy, ctx) |> mteTy
      MCallProcInit(callee, args, calleeTy), ctx

  | MCallClosureInit (callee, args) ->
      let callee, ctx = (callee, ctx) |> mteExpr
      let args, ctx = (args, ctx) |> stMap mteExpr
      MCallClosureInit(callee, args), ctx

  | MBoxInit expr ->
      let expr, ctx = (expr, ctx) |> mteExpr
      MBoxInit expr, ctx

  | MConsInit (l, r) ->
      let l, ctx = (l, ctx) |> mteExpr
      let r, ctx = (r, ctx) |> mteExpr
      MConsInit(l, r), ctx

  | MTupleInit items ->
      let items, ctx = (items, ctx) |> stMap mteExpr
      MTupleInit items, ctx

  | MVariantInit (variantSerial, payload) ->
      let payload, ctx = (payload, ctx) |> mteExpr
      MVariantInit(variantSerial, payload), ctx

let private mteSwitchClause (clause: MSwitchClause, ctx: MteCtx) =
  let terminator, ctx =
    (clause.Terminator, ctx) |> mteTerminator

  { clause with Terminator = terminator }, ctx

let private mteTerminator (terminator: MTerminator, ctx: MteCtx) =
  match terminator with
  | MExitTerminator exitCode ->
      let exitCode, ctx = (exitCode, ctx) |> mteExpr
      MExitTerminator exitCode, ctx

  | MReturnTerminator result ->
      let result, ctx = (result, ctx) |> mteExpr
      MReturnTerminator result, ctx

  | MGotoTerminator _ -> terminator, ctx

  | MGotoIfTerminator (cond, label) ->
      let cond, ctx = (cond, ctx) |> mteExpr
      MGotoIfTerminator(cond, label), ctx

  | MIfTerminator (cond, thenCl, elseCl) ->
      let cond, ctx = (cond, ctx) |> mteExpr
      let thenCl, ctx = (thenCl, ctx) |> mteTerminator
      let elseCl, ctx = (elseCl, ctx) |> mteTerminator
      MIfTerminator(cond, thenCl, elseCl), ctx

  | MSwitchTerminator (cond, clauses) ->
      let cond, ctx = (cond, ctx) |> mteExpr
      let clauses, ctx = (clauses, ctx) |> stMap mteSwitchClause
      MSwitchTerminator(cond, clauses), ctx

let private mteStmt (stmt, ctx: MteCtx) =
  match stmt with
  | MLetValStmt (varSerial, init, ty, loc) ->
      let init, ctx = (init, ctx) |> mteInit
      let ty, ctx = (ty, ctx) |> mteTy
      MLetValStmt(varSerial, init, ty, loc), ctx

  | MSetStmt (varSerial, init, loc) ->
      let init, ctx = (init, ctx) |> mteExpr
      MSetStmt(varSerial, init, loc), ctx

  | MLabelStmt _ -> stmt, ctx

  | MIfStmt _ -> failwith "unimplemented"

  | MTerminatorStmt (terminator, loc) ->
      let terminator, ctx = (terminator, ctx) |> mteTerminator
      MTerminatorStmt(terminator, loc), ctx

let private mteBlock (block: MBlock, ctx: MteCtx) =
  let stmts, ctx = (block.Stmts, ctx) |> stMap mteStmt
  { block with Stmts = stmts }, ctx

let private mteDecl (decl, ctx: MteCtx) =
  match decl with
  | MProcDecl (funSerial, isMain, args, body, resultTy, loc) ->
      let args, ctx =
        (args, ctx)
        |> stMap (fun ((varSerial, ty, loc), ctx) ->
             let ty, ctx = (ty, ctx) |> mteTy
             (varSerial, ty, loc), ctx)

      let body, ctx = (body, ctx) |> stMap mteBlock
      let resultTy, ctx = (resultTy, ctx) |> mteTy
      MProcDecl(funSerial, isMain, args, body, resultTy, loc), ctx

let mirTyElaborate (decls: MDecl list, mirCtx: MirCtx): MDecl list * MirCtx =
  let ctx = ofMirCtx mirCtx

  let vars, ctx =
    ctx.Vars
    |> mapFold (fun (vars, ctx) varSerial varDef ->
         let varDef, ctx =
           match varDef with
           | VarDef (name, sm, ty, loc) ->
               let ty, ctx = (ty, ctx) |> mteTy
               VarDef(name, sm, ty, loc), ctx

         (vars |> mapAdd varSerial varDef), ctx) (ctx.Vars, ctx)

  let funs, ctx =
    ctx.Funs
    |> mapFold (fun (vars, ctx) funSerial (funDef: FunDef) ->
         let (TyScheme (tyVars, ty)) = funDef.Ty
         let ty, ctx = (ty, ctx) |> mteTy

         let funDef =
           { funDef with
               Ty = TyScheme(tyVars, ty) }

         (vars |> mapAdd funSerial funDef), ctx) (ctx.Funs, ctx)

  let variants, ctx =
    ctx.Variants
    |> mapFold (fun (variants, ctx) variantSerial (variantDef: VariantDef) ->
         let payloadTy, ctx = (variantDef.PayloadTy, ctx) |> mteTy
         let variantTy, ctx = (variantDef.VariantTy, ctx) |> mteTy

         let variantDef =
           { variantDef with
               PayloadTy = payloadTy
               VariantTy = variantTy }

         (variants |> mapAdd variantSerial variantDef), ctx) (ctx.Variants, ctx)

  let tys, ctx =
    ctx.Tys
    |> mapFold (fun (tys, ctx) tySerial tyDef ->
         let tyDef, ctx =
           match tyDef with
           | UniversalTyDef _
           | UnionTyDef _ -> tyDef, ctx

           | MetaTyDef (name, bodyTy, loc) ->
               let bodyTy, ctx = (bodyTy, ctx) |> mteTy
               MetaTyDef(name, bodyTy, loc), ctx

           | SynonymTyDef (name, tyVars, bodyTy, loc) ->
               let bodyTy, ctx = (bodyTy, ctx) |> mteTy
               SynonymTyDef(name, tyVars, bodyTy, loc), ctx

           | RecordTyDef (name, fields, loc) ->
               let fields, ctx =
                 (fields, ctx)
                 |> stMap (fun ((fieldName, fieldTy, fieldLoc), ctx) ->
                      let fieldTy, ctx = (fieldTy, ctx) |> mteTy
                      (fieldName, fieldTy, fieldLoc), ctx)

               RecordTyDef(name, fields, loc), ctx

         (tys |> mapAdd tySerial tyDef), ctx) (ctx.Tys, ctx)

  let tys =
    ctx.NewTys
    |> List.fold (fun tys (tySerial, tyDef) -> tys |> mapAdd tySerial tyDef) tys

  let ctx =
    { ctx with
        Vars = vars
        Funs = funs
        Variants = variants
        Tys = tys }

  let decls, (ctx: MteCtx) = (decls, ctx) |> stMap mteDecl

  let mirCtx = ctx |> toMirCtx mirCtx

  decls, mirCtx
