module rec MiloneLang.MirEliminate

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TySystem
open MiloneLang.Hir
open MiloneLang.Mir
open MiloneLang.MirGen

type MirEliminateResult = { VarKill: AssocSet<VarSerial> }

// -----------------------------------------------
// Util
// -----------------------------------------------

let private forList folder xs state =
  xs
  |> List.fold (fun state x -> folder x state) state

let private mPrimIsPure prim =
  match prim with
  | MIntOfStrPrim _
  | MFloatOfStrPrim _
  | MCharOfStrPrim
  | MStrOfBoolPrim
  | MStrOfCharPrim
  | MStrOfIntPrim _
  | MStrOfFloatPrim _
  | MStrGetSlicePrim
  | MPtrReadPrim -> true

  | MCallNativePrim _ -> false

let private mInitIsPure init =
  match init with
  | MUninitInit
  | MExprInit _
  | MClosureInit _
  | MBoxInit _
  | MConsInit _
  | MTupleInit _
  | MVariantInit _
  | MRecordInit _ -> true

  | MCallProcInit _
  | MCallClosureInit _ -> false

  | MPrimInit (prim, _) -> mPrimIsPure prim

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MeCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    VarUse: AssocSet<VarSerial>
    VarKill: AssocSet<VarSerial>
    IsChanged: bool }

let private ofMirCtx (mirCtx: MirCtx): MeCtx =
  { Vars = mirCtx.Vars
    Funs = mirCtx.Funs
    VarUse = setEmpty varSerialCmp
    VarKill = setEmpty varSerialCmp
    IsChanged = false }

let private toResult (ctx: MeCtx): MirEliminateResult = { VarKill = ctx.VarKill }

// -----------------------------------------------
// Data flow analysis
// -----------------------------------------------

/// Gets whether a var is read somewhere and not killed.
let private inUse varSerial (ctx: MeCtx) =
  setContains varSerial ctx.VarUse
  && not (setContains varSerial ctx.VarKill)

let private addVarUse varSerial (ctx: MeCtx) =
  if setContains varSerial ctx.VarUse
     || setContains varSerial ctx.VarKill then
    ctx
  else
    printfn "// var marked as use: %s" (mapFind varSerial ctx.Vars |> varDefToName)
    { ctx with
        VarUse = ctx.VarUse |> setAdd varSerial
        IsChanged = true }

/// Marks all variables in the expr in use.
let private dfaExpr expr ctx =
  match expr with
  | MLitExpr _
  | MDefaultExpr _
  | MProcExpr _
  | MVariantExpr _
  | MTagExpr _
  | MNativeExpr _ -> ctx

  | MRefExpr (varSerial, _, _) -> ctx |> addVarUse varSerial

  | MUnaryExpr (_, arg, _, _) -> ctx |> dfaExpr arg
  | MBinaryExpr (_, l, r, _, _) -> ctx |> dfaExpr l |> dfaExpr r

let private dfaExprs exprs ctx = ctx |> forList dfaExpr exprs

let private dfaInit init ctx =
  match init with
  | MUninitInit -> ctx

  | MExprInit expr -> ctx |> dfaExpr expr
  | MPrimInit (_, args) -> ctx |> dfaExprs args

  | MCallProcInit (callee, args, _) -> ctx |> dfaExpr callee |> dfaExprs args
  | MCallClosureInit (callee, args) -> ctx |> dfaExpr callee |> dfaExprs args

  | MClosureInit (_, envVarSerial) -> ctx |> addVarUse envVarSerial
  | MBoxInit expr -> ctx |> dfaExpr expr
  | MConsInit (l, r) -> ctx |> dfaExpr l |> dfaExpr r
  | MTupleInit items -> ctx |> dfaExprs items
  | MVariantInit (_, payload) -> ctx |> dfaExpr payload
  | MRecordInit items -> ctx |> dfaExprs items

let private dfaTerminator terminator ctx =
  match terminator with
  | MExitTerminator arg -> ctx |> dfaExpr arg

  | MGotoTerminator _ -> ctx
  | MReturnTerminator arg -> ctx |> dfaExpr arg
  | MGotoIfTerminator (cond, _) -> ctx |> dfaExpr cond

  | MIfTerminator (cond, thenCl, elseCl) ->
      ctx
      |> dfaTerminator thenCl
      |> dfaTerminator elseCl
      |> dfaExpr cond

  | MSwitchTerminator (cond, clauses) ->
      let dfaClause (clause: MSwitchClause) ctx = ctx |> dfaTerminator clause.Terminator
      ctx |> forList dfaClause clauses |> dfaExpr cond

let private dfaActionStmt stmt ctx =
  match stmt with
  | MActionStmt (_, args, _) -> ctx |> dfaExprs args
  | _ -> failwith "NEVER"

let private dfaLetValStmt stmt ctx =
  match stmt with
  | MLetValStmt (varSerial, init, _, _) ->
      if inUse varSerial ctx || not (mInitIsPure init)
      then ctx |> dfaInit init
      else ctx

  | _ -> failwith "NEVER"

let private dfaSetStmt stmt ctx =
  match stmt with
  | MSetStmt (varSerial, init, _) -> if ctx |> inUse varSerial then ctx |> dfaExpr init else ctx
  | _ -> failwith "NEVER"

let private dfaTerminatorStmt stmt ctx =
  match stmt with
  | MTerminatorStmt (terminator, _) -> ctx |> dfaTerminator terminator
  | _ -> failwith "NEVER"

let private dfaStmt stmt ctx =
  match stmt with
  | MLabelStmt _
  | MNativeStmt _ -> ctx

  | MActionStmt _ -> dfaActionStmt stmt ctx
  | MLetValStmt _ -> dfaLetValStmt stmt ctx
  | MSetStmt _ -> dfaSetStmt stmt ctx
  | MTerminatorStmt _ -> dfaTerminatorStmt stmt ctx

  | MIfStmt _ -> failwith "NEVER"

let private dfaBlock (block: MBlock) ctx =
  // Data-flow analysis works faster by iterating over program in reversed order
  // since use-sites appear first and def-sites later.
  ctx |> forList dfaStmt (List.rev block.Stmts)

let private dfaDecl decl (ctx: MeCtx) =
  match decl with
  | MProcDecl (funSerial, _, body, _, _) ->
      let funName = (mapFind funSerial ctx.Funs).Name
      printfn "// enter fun: %s" funName
      let ctx = ctx |> forList dfaBlock body
      printfn "// leave fun: %s" funName
      ctx

  | MNativeDecl _ -> ctx

let private dfaRoot decls (ctx: MeCtx) =
  printfn "// dfaRoot: begin"

  // Collect variables in use.
  let rec analyzeLoop (ctx: MeCtx) =
    let ctx = ctx |> forList dfaDecl decls

    let isChanged, ctx =
      ctx.IsChanged, { ctx with IsChanged = false }

    if isChanged then
      printfn "// some var marked as use"
      analyzeLoop ctx
    else
      ctx

  let ctx = analyzeLoop ctx

  printfn "// dfaRoot analyzed"

  // Kill variables not in use.
  let isChanged, ctx =
    ctx.Vars
    |> mapFold (fun (isChanged, ctx: MeCtx) varSerial (_: VarDef) ->
         if setContains varSerial ctx.VarUse
            || setContains varSerial ctx.VarKill then
           isChanged, ctx
         else
           printfn "// kill %s" (mapFind varSerial ctx.Vars |> varDefToName)

           let ctx =
             { ctx with
                 VarKill = setAdd varSerial ctx.VarKill }

           true, ctx) (false, ctx)

  if isChanged then
    printfn "// some var killed"
    dfaRoot decls ctx
  else
    ctx

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

let mirEliminate (decls, mirCtx: MirCtx): MirEliminateResult =
  let ctx = ofMirCtx mirCtx
  ctx |> dfaRoot decls |> toResult
