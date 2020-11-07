/// ## Type Elaborating
module rec MiloneLang.TyElaborating

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Records

let private ofTyCtx (tyCtx: TyCtx): TyElaborationCtx =
  let vars = tyCtx |> tyCtxGetVars
  let tys = tyCtx |> tyCtxGetTys
  TyElaborationCtx(vars, tys, mapEmpty (intHash, intCmp))

let private toTyCtx tyCtx (ctx: TyElaborationCtx): TyCtx =
  let (TyCtx (serial, _, _, tyDepths, letDepth, traitBounds, logs)) = tyCtx
  let (TyElaborationCtx (vars, tys, _)) = ctx
  TyCtx(serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

// -----------------------------------------------
// Control
// -----------------------------------------------

let private teTy ctx ty =
  match ty with
  | AppTy (RefTyCtor tySerial, []) ->
      match ctx
            |> tyElaborationCtxGetRecordMap
            |> mapTryFind tySerial with
      | Some (tupleTy, _) -> tupleTy
      | _ -> ty

  | AppTy (_, []) -> ty

  | AppTy (tyCtor, tyArgs) ->
      let tyArgs = tyArgs |> listMap (teTy ctx)
      AppTy(tyCtor, tyArgs)

  | MetaTy _
  | ErrorTy _ -> ty

let private tePat ctx pat = pat |> patMap (teTy ctx) id

let private teExpr ctx expr =
  match expr with
  | HRecordExpr (fields, ty, loc) ->
      let doArm () =
        let fieldMap =
          match ty with
          | AppTy (RefTyCtor tySerial, []) ->
              match ctx
                    |> tyElaborationCtxGetRecordMap
                    |> mapTryFind tySerial with
              | Some (_, fieldMap) -> fieldMap
              | _ -> failwithf "NEVER: Expected a record. %A" expr
          | _ -> failwithf "NEVER: Expected a record. %A" expr

        let fields =
          fields
          |> listMap (fun (ident, init, _) ->
               let index, _ = fieldMap |> mapFind ident
               index, init)
          |> listSort (fun (l, _) (r, _) -> intCmp l r)
          |> listMap (fun (_, init) -> init)

        hxTuple fields loc

      doArm ()

  | HLitExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HRefExpr _
  | HPrimExpr _ -> expr |> exprMap (teTy ctx) id

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target = target |> teExpr ctx

        let go (pat, guard, body) =
          let pat = pat |> tePat ctx
          let guard = guard |> teExpr ctx
          let body = body |> teExpr ctx
          pat, guard, body

        let arms = arms |> listMap go
        let ty = ty |> teTy ctx
        HMatchExpr(target, arms, ty, loc)

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let l = l |> teExpr ctx
        let ty = ty |> teTy ctx
        HNavExpr(l, r, ty, loc)

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items = items |> listMap (teExpr ctx)
        let ty = ty |> teTy ctx
        HInfExpr(infOp, items, ty, loc)

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let pat = pat |> tePat ctx
        let init = init |> teExpr ctx
        let next = next |> teExpr ctx
        let ty = ty |> teTy ctx
        HLetValExpr(vis, pat, init, next, ty, loc)

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let args = args |> listMap (tePat ctx)
        let body = body |> teExpr ctx
        let next = next |> teExpr ctx
        let ty = ty |> teTy ctx
        HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc)

      doArm ()

  | HErrorExpr (error, loc) -> failwithf "NEVER: %A" (error, loc)
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let tyElaborate (expr: HExpr, tyCtx: TyCtx) =
  let ctx = ofTyCtx tyCtx

  // record -> tuple mapping
  // recursion is not supported
  let recordMap =
    ctx
    |> tyElaborationCtxGetTys
    |> mapFold (fun acc tySerial tyDef ->
         match tyDef with
         | RecordTyDef (_, fields, _) ->
             let tupleTy =
               fields
               |> listMap (fun (_, ty, _) -> ty)
               |> tyTuple

             let fieldMap =
               fields
               |> listMapWithIndex (fun i (ident, ty, _) -> ident, (i, ty))
               |> mapOfList (strHash, strCmp)

             (tySerial, (tupleTy, fieldMap)) :: acc

         | _ -> acc) []
    |> mapOfList (intHash, intCmp)

  let vars =
    ctx
    |> tyElaborationCtxGetVars
    |> mapMap (fun _ varDef ->
         match varDef with
         | VarDef (ident, sm, ty, loc) ->
             let ty = ty |> teTy ctx
             VarDef(ident, sm, ty, loc)

         | FunDef (ident, arity, TyScheme (tyArgs, ty), loc) ->
             let ty = ty |> teTy ctx
             FunDef(ident, arity, TyScheme(tyArgs, ty), loc)

         | VariantDef (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
             let payloadTy = payloadTy |> teTy ctx
             VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc))

  let ctx =
    ctx
    |> tyElaborationCtxWithVars vars
    |> tyElaborationCtxWithRecordMap recordMap

  let expr = expr |> teExpr ctx
  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
