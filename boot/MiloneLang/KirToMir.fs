/// # KirToMir
///
/// Convert KIR to MIR to join into CirGen pass.

module rec MiloneLang.KirToMir

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers

let private unreachable value = failwithf "NEVER: %A" value

/// Reconstructs fun type from type of args and result.
let rec private restoreCalleeTy args ty =
  match args with
  | [] -> ty

  | arg :: args ->
      let argTy = mexprToTy arg
      restoreCalleeTy args (tyFun argTy ty)

// -----------------------------------------------
// KirToMirCtx
// -----------------------------------------------

let private jointMapEmpty () = mapEmpty (intHash, intCmp)

let private ofKirGenCtx (kirGenCtx: KirGenCtx): KirToMirCtx =
  let (KirGenCtx (serial, vars, tys, logs, mainFunSerial, _, _)) = kirGenCtx
  KirToMirCtx(serial, vars, tys, mainFunSerial, 0, jointMapEmpty (), [], logs)

let private toMirCtx (ctx: KirToMirCtx): MirCtx =
  let (KirToMirCtx (serial, vars, tys, _, labelSerial, _, _, logs)) = ctx
  MirCtx(serial, vars, tys, labelSerial, [], logs)

let private freshSerial ctx =
  let serial = (ctx |> kirToMirCtxGetSerial) + 1
  let ctx = ctx |> kirToMirCtxWithSerial serial
  serial, ctx

let private newVar hint ty loc ctx =
  let varSerial, ctx = ctx |> freshSerial

  let ctx =
    let vars =
      ctx
      |> kirToMirCtxGetVars
      |> mapAdd varSerial (VarDef(hint, AutoSM, ty, loc))

    ctx |> kirToMirCtxWithVars vars

  varSerial, ctx

let private findVarDef varSerial ctx =
  ctx |> kirToMirCtxGetVars |> mapFind varSerial

let private findVarTy varSerial ctx =
  match ctx |> kirToMirCtxGetVars |> mapTryFind varSerial with
  | Some (VarDef (_, _, ty, _)) -> ty
  | _ -> failwithf "Expected var. %A" varSerial

let private findFunTy funSerial ctx =
  match ctx |> kirToMirCtxGetVars |> mapTryFind funSerial with
  | Some (FunDef (_, _, TyScheme (_, ty), _)) -> ty
  | _ -> failwithf "Expected fun. %A" funSerial

let private addStmt stmt ctx =
  ctx
  |> kirToMirCtxWithStmts (stmt :: (ctx |> kirToMirCtxGetStmts))

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

/// Adds a statement to bind binary operation to variable.
///
/// `let-val result = binary(l, r)`
let private setBinaryM (binary: MBinary) (l: MExpr) r result loc ctx =
  let resultTy = findVarTy result ctx

  let expr = MBinaryExpr(binary, l, r, resultTy, loc)

  ctx
  |> addStmt (MLetValStmt(result, MExprInit expr, resultTy, loc))

/// Converts arg of 1-arity prim to MIR and adds let-val statement in MIR.
///
/// Used for basic 1-arity operations.
let private setUnaryK (unary: MUnary) (term: KTerm) result cont loc ctx =
  let arg = kmTerm term
  let resultTy = findVarTy result ctx

  ctx
  |> addStmt (MLetValStmt(result, MExprInit(MUnaryExpr(unary, arg, resultTy, loc)), resultTy, loc))
  |> kmNode cont

/// Converts args to MIR and adds let-val statement in MIR.
///
/// Used for basic 2-arity operations.
let private setBinaryK (binary: MBinary) (l: KTerm) r result cont loc ctx =
  let l = kmTerm l
  let r = kmTerm r

  ctx
  |> setBinaryM binary l r result loc
  |> kmNode cont

// -----------------------------------------------
// Primitive
// -----------------------------------------------

let private kmPrimAdd itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MAddBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimSub itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MSubBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimMul itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MMulBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimDiv itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MDivBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimMod itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MModBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimEqual itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MEqualBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimLess itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] -> ctx |> setBinaryK MLessBinary l r result cont loc
  | _ -> unreachable itself

let private kmPrimNot itself args results conts loc ctx =
  match args, results, conts with
  | [ arg ], [ result ], [ cont ] -> ctx |> setUnaryK MNotUnary arg result cont loc
  | _ -> unreachable itself

let private kmPrimStrIndex itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] ->
      ctx
      |> setBinaryK MStrIndexBinary l r result cont loc

  | _ -> unreachable itself

let private kmPrimStrAdd itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] ->
      ctx
      |> setBinaryK MStrAddBinary l r result cont loc

  | _ -> unreachable itself

let private kmPrimStrCompare itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] ->
      ctx
      |> setBinaryK MStrCmpBinary l r result cont loc

  | _ -> unreachable itself

let private kmPrimStrLength itself args results conts loc ctx =
  match args, results, conts with
  | [ arg ], [ result ], [ cont ] -> ctx |> setUnaryK MStrLenUnary arg result cont loc
  | _ -> unreachable itself

let private kmPrimCons itself args results conts loc ctx =
  match args, results, conts with
  | [ l; r ], [ result ], [ cont ] ->
      let l = kmTerm l
      let r = kmTerm r

      let listTy = mexprToTy r

      ctx
      |> addStmt (MLetValStmt(result, MConsInit(l, r), listTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimSome itself args results conts loc ctx =
  match args, results, conts with
  | [ item ], [ result ], [ cont ] ->
      let item = kmTerm item

      let itemTy = mexprToTy item
      let listTy = tyList itemTy
      let nil = MDefaultExpr(itemTy, loc)

      ctx
      |> addStmt (MLetValStmt(result, MConsInit(item, nil), listTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimTuple itself args results conts loc ctx =
  match args, results, conts with
  | args, [ result ], [ cont ] ->
      let items = args |> listMap kmTerm
      let itemTys = items |> listMap mexprToTy
      let tupleTy = tyTuple itemTys

      ctx
      |> addStmt (MLetValStmt(result, MTupleInit items, tupleTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimVariant itself args results conts loc ctx =
  match args, results, conts with
  | [ KVariantTerm (variantSerial, _, _); payload ], [ result ], [ cont ] ->
      let payload = kmTerm payload

      // Set payload to temporary var since MVariantInit requires a serial, not expr.
      let payloadVarSerial, ctx =
        let ty, loc = mexprExtract payload
        ctx |> newVar "payload" ty loc

      let resultTy = ctx |> findVarTy result

      ctx
      |> addStmt (MLetValStmt(result, MVariantInit(variantSerial, payloadVarSerial), resultTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimClosure itself args results conts loc ctx =
  match args, results, conts with
  | [ KVarTerm (funSerial, AppTy (FunTyCtor, [ _; closureTy ]), _); KVarTerm (envSerial, _, _) ], [ result ], [ cont ] ->
      ctx
      |> addStmt (MLetValStmt(result, MClosureInit(funSerial, envSerial), closureTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimCallProc itself args results conts loc ctx =
  let args = args |> listMap kmTerm

  match args, results, conts with
  | callee :: args, [ result ], [ cont ] ->
      let calleeTy = mexprToTy callee
      let resultTy = findVarTy result ctx

      ctx
      |> addStmt (MLetValStmt(result, MCallProcInit(callee, args, calleeTy), resultTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimCallClosure itself args results conts loc ctx =
  let args = args |> listMap kmTerm

  match args, results, conts with
  | callee :: args, [ result ], [ cont ] ->
      let resultTy = findVarTy result ctx

      ctx
      |> addStmt (MLetValStmt(result, MCallClosureInit(callee, args), resultTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimBox itself args results conts loc ctx =
  match args, results, conts with
  | [ arg ], [ result ], [ cont ] ->
      let arg = kmTerm arg

      ctx
      |> addStmt (MLetValStmt(result, MBoxInit arg, tyObj, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimUnbox itself args results conts loc ctx =
  match args, results, conts with
  | [ arg ], [ result ], [ cont ] -> setUnaryK MUnboxUnary arg result cont loc ctx
  | _ -> unreachable itself

/// Converts a prim node which doesn't require special handling in this conversion
/// to simple call.
let private kmPrimOther itself prim args results conts loc ctx =
  match results, conts with
  | [ result ], [ cont ] ->
      let args = args |> listMap kmTerm

      let resultTy = findVarTy result ctx
      let primTy = restoreCalleeTy args resultTy

      ctx
      |> addStmt (MLetValStmt(result, MCallPrimInit(prim, args, primTy), resultTy, loc))
      |> kmNode cont

  | _ -> unreachable itself

let private kmPrimNode itself prim args results conts loc ctx: KirToMirCtx =
  let other prim =
    kmPrimOther itself prim args results conts loc ctx

  match prim with
  | KAddPrim -> kmPrimAdd itself args results conts loc ctx
  | KSubPrim -> kmPrimSub itself args results conts loc ctx
  | KMulPrim -> kmPrimMul itself args results conts loc ctx
  | KDivPrim -> kmPrimDiv itself args results conts loc ctx
  | KModPrim -> kmPrimMod itself args results conts loc ctx
  | KEqualPrim -> kmPrimEqual itself args results conts loc ctx
  | KLessPrim -> kmPrimLess itself args results conts loc ctx
  | KNotPrim -> kmPrimNot itself args results conts loc ctx
  | KStrAddPrim -> kmPrimStrAdd itself args results conts loc ctx
  | KStrComparePrim -> kmPrimStrCompare itself args results conts loc ctx
  | KStrIndexPrim -> kmPrimStrIndex itself args results conts loc ctx
  | KStrLengthPrim -> kmPrimStrLength itself args results conts loc ctx
  | KStrGetSlicePrim -> other HPrim.StrGetSlice
  | KConsPrim -> kmPrimCons itself args results conts loc ctx
  | KSomePrim -> kmPrimSome itself args results conts loc ctx
  | KTuplePrim -> kmPrimTuple itself args results conts loc ctx
  | KVariantPrim -> kmPrimVariant itself args results conts loc ctx
  | KClosurePrim -> kmPrimClosure itself args results conts loc ctx
  | KCallProcPrim -> kmPrimCallProc itself args results conts loc ctx
  | KCallClosurePrim -> kmPrimCallClosure itself args results conts loc ctx
  | KBoxPrim -> kmPrimBox itself args results conts loc ctx
  | KUnboxPrim -> kmPrimUnbox itself args results conts loc ctx
  | KExitPrim -> other HPrim.Exit
  | KAssertPrim -> other HPrim.Assert
  | KCharPrim -> other HPrim.Char
  | KIntPrim -> other HPrim.Int
  | KStringPrim -> other HPrim.String
  | KPrintfnPrim -> other HPrim.Printfn
  | KInRegionPrim -> other HPrim.InRegion
  | KNativeFunPrim (ident, arity) -> other (HPrim.NativeFun(ident, arity))

// -----------------------------------------------
// kmTerm, kmNode
// -----------------------------------------------

let private kmTerm (term: KTerm): MExpr =
  match term with
  | KLitTerm (lit, loc) -> MLitExpr(lit, loc)

  | KVarTerm (varSerial, ty, loc)
  | KFunTerm (varSerial, ty, loc)
  | KVariantTerm (varSerial, ty, loc)
  | KLabelTerm (varSerial, ty, loc) -> MRefExpr(varSerial, ty, loc)

  | KTagTerm (varSerial, ty, loc) -> failwith ""

  | KNilTerm (itemTy, loc) -> MDefaultExpr(tyList itemTy, loc)

  | KNoneTerm (itemTy, loc) -> MDefaultExpr(tyList itemTy, loc)

  | KUnitTerm loc -> MDefaultExpr(tyUnit, loc)

let private kmNode (node: KNode) ctx: KirToMirCtx =
  match node with
  | KJumpNode (jointSerial, args, loc) ->
      let label, argSerials =
        ctx
        |> kirToMirCtxGetJointMap
        |> mapFind jointSerial

      let rec go argSerials args ctx =
        match argSerials, args with
        | [], [] -> ctx

        | varSerial :: argSerials, arg :: args ->
            ctx
            |> addStmt (MSetStmt(varSerial, kmTerm arg, loc))
            |> go argSerials args

        | _ -> failwithf "NEVER: bad arity. %A" node

      ctx
      |> go argSerials args
      |> addStmt (MGotoStmt(label, loc))

  | KReturnNode (_funSerial, args, loc) ->
      let arg =
        match args with
        | [] -> MDefaultExpr(tyUnit, loc)
        | [ arg ] -> kmTerm arg
        | _ -> unreachable node

      ctx |> addStmt (MReturnStmt(arg, loc))

  | KSelectNode (term, path, result, cont, loc) ->
      let term = kmTerm term

      let doUnary unary ctx =
        let expr = MUnaryExpr(unary, term, noTy, loc)
        ctx
        |> addStmt (MLetValStmt(result, MExprInit(expr), noTy, loc))

      let ctx =
        match path with
        | KSelfPath ->
            ctx
            |> addStmt (MLetValStmt(result, MExprInit(term), noTy, loc))

        | KHeadPath _ -> doUnary MListHeadUnary ctx
        | KTailPath _ -> doUnary MListTailUnary ctx
        | KFieldPath (i, _) -> doUnary (MProjUnary i) ctx
        | KTagPath _ -> doUnary MTagUnary ctx
        | KPayloadPath (variantSerial, _) -> doUnary (MGetVariantUnary variantSerial) ctx

      kmNode cont ctx

  | KPrimNode (prim, args, results, conts, loc) -> kmPrimNode node prim args results conts loc ctx

let private kmFunBinding binding ctx =
  let genBody jointMap processBody ctx =
    let parentJointMap = ctx |> kirToMirCtxGetJointMap
    let parentStmts = ctx |> kirToMirCtxGetStmts

    let ctx =
      ctx
      |> kirToMirCtxWithJointMap jointMap
      |> kirToMirCtxWithStmts []

    let ctx = processBody ctx

    let stmts = ctx |> kirToMirCtxGetStmts

    let ctx =
      ctx
      |> kirToMirCtxWithJointMap parentJointMap
      |> kirToMirCtxWithStmts parentStmts

    stmts, ctx

  let (KFunBinding (funSerial, args, joints, loc)) = binding

  let isMainFun =
    match findVarDef funSerial ctx with
    | FunDef (ident, _, _, _) -> ident = "main"
    | _ -> false

  let args, resultTy =
    let rec go args funTy =
      match args, funTy with
      | arg :: args, AppTy (FunTyCtor, [ sTy; tTy ]) ->
          let args, resultTy = go args tTy
          (arg, sTy, loc) :: args, resultTy

      | [], resultTy -> [], resultTy

      | _ -> failwithf "NEVER: illegal KFunBinding. %A" binding

    let funTy = findFunTy funSerial ctx
    go args funTy

  let body, ctx =
    let jointMap =
      joints
      |> listMapWithIndex (fun (i: int) joint ->
           let (KJointBinding (jointSerial, args, _, _)) = joint
           let label = "L" + string i
           jointSerial, (label, args))
      |> mapOfList (intHash, intCmp)

    let rec go joints ctx =
      match joints with
      | [] -> ctx

      | KJointBinding (jointSerial, _args, body, loc) :: joints ->
          let label, _ = jointMap |> mapFind jointSerial

          ctx
          |> addStmt (MLabelStmt(label, loc))
          |> kmNode body
          |> go joints

    ctx |> genBody jointMap (go joints)

  ctx
  |> addStmt (MProcStmt(funSerial, isMainFun, args, body, resultTy, loc))

let kirToMir (root: KRoot, kirGenCtx: KirGenCtx): MStmt list * MirCtx =
  let ctx = ofKirGenCtx kirGenCtx

  let ctx =
    let (KRoot funBindings) = root

    funBindings
    |> listFold (fun ctx binding -> kmFunBinding binding ctx) ctx

  let stmts = ctx |> kirToMirCtxGetStmts
  let mirCtx = ctx |> toMirCtx
  stmts, mirCtx
