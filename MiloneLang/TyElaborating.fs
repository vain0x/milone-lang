/// ## Type Elaborating
module rec MiloneLang.TyElaborating

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Records

let private hxIsUnboxingRef expr =
  match expr with
  | HInfExpr (InfOp.App, [ HPrimExpr (HPrim.Unbox, _, _); HRefExpr _ ], _, _) -> true
  | _ -> false

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
      let tyArgs = tyArgs |> List.map (teTy ctx)
      AppTy(tyCtor, tyArgs)

  | MetaTy _
  | ErrorTy _ -> ty

let private tePat ctx pat = pat |> patMap (teTy ctx) id

let private teExpr ctx expr =
  match expr with
  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        let tupleTy, fieldMap =
          match ty with
          | AppTy (RefTyCtor tySerial, []) ->
              match ctx
                    |> tyElaborationCtxGetRecordMap
                    |> mapTryFind tySerial with
              | Some (tupleTy, fieldMap) -> tupleTy, fieldMap
              | _ -> failwithf "NEVER: %A" expr
          | _ -> failwithf "NEVER: %A" expr

        // Base expr is guaranteed to be a cheap expr thanks to modification in Typing,
        // so we can freely clone this.
        let baseOpt =
          assert (baseOpt |> Option.forall hxIsUnboxingRef)

          baseOpt |> Option.map (teExpr ctx)

        let fields =
          fields
          |> List.map (fun (ident, init, _) ->
               let init = init |> teExpr ctx
               let index, _ = fieldMap |> mapFind ident
               index, init)
          |> listSort (fun (l, _) (r, _) -> intCmp l r)

        match baseOpt with
        | Some baseExpr ->
            let itemTys =
              match tupleTy with
              | AppTy (_, fieldTys) -> fieldTys
              | _ -> failwithf "NEVER: %A" expr

            let itemExpr index =
              let itemTy = itemTys |> List.item index
              HInfExpr(InfOp.TupleItem index, [ baseExpr ], itemTy, loc)

            let n = itemTys |> List.length

            let rec go i fields =
              match fields with
              | [] when i = n -> []

              | (index, init) :: fields when index = i -> init :: go (i + 1) fields

              | _ -> itemExpr i :: go (i + 1) fields

            hxTuple (go 0 fields) loc

        | None ->
            let fields =
              fields |> List.map (fun (_, init) -> init)

            hxTuple fields loc

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        // record.field ==> tuple.index
        let index =
          match exprToTy l with
          | AppTy (RefTyCtor tySerial, []) ->
              let _, fieldMap =
                ctx
                |> tyElaborationCtxGetRecordMap
                |> mapFind tySerial

              let index, _ = fieldMap |> mapFind r
              index

          | _ -> failwithf "NEVER: %A" expr

        let l = l |> teExpr ctx
        let ty = ty |> teTy ctx
        HInfExpr(InfOp.TupleItem index, [ l ], ty, loc)

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

        let arms = arms |> List.map go
        let ty = ty |> teTy ctx
        HMatchExpr(target, arms, ty, loc)

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items = items |> List.map (teExpr ctx)
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
        let args = args |> List.map (tePat ctx)
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
               |> List.map (fun (_, ty, _) -> ty)
               |> tyTuple

             let fieldMap =
               fields
               |> List.mapi (fun i (ident, ty, _) -> ident, (i, ty))
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
