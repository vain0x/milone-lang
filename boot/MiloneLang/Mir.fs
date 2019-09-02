/// Converts HIR to MIR.
/// Deconstructs pattern matching.
module rec MiloneLang.Mir

open MiloneLang.Types
open MiloneLang.Helpers

type TyCtx = Typing.TyCtx

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    Serial: int
    Vars: Map<int, VarDef>
    Tys: Map<int, TyDef>
    LabelSerial: int
    Stmts: MStmt list
    Diags: Diag list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): MirCtx =
  {
    Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    LabelSerial = 0
    Stmts = []
    Diags = tyCtx.Diags
  }

let ctxGetVar (ctx: MirCtx) varSerial =
  ctx.Vars |> Map.find varSerial

let ctxGetTy (ctx: MirCtx) tySerial =
  ctx.Tys |> Map.find tySerial

let ctxGetVariants (ctx: MirCtx) tySerial =
  match ctxGetTy ctx tySerial with
  | TyDef.Union (_, variantSerials, _) ->
    variantSerials |> List.map
      (fun variantSerial ->
        match ctxGetVar ctx variantSerial with
        | VarDef.Variant (_, _, _, payloadTy, _, _) ->
          variantSerial, payloadTy
        | _ ->
          failwith "Expected variant"
      )
  | _ ->
    eprintfn "Expected union type"
    assert false
    []

let ctxAddErr (ctx: MirCtx) message loc =
  { ctx with Diags = Diag.Err (message, loc) :: ctx.Diags }

let ctxNewBlock (ctx: MirCtx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddStmt (ctx: MirCtx) (stmt: MStmt) =
  { ctx with Stmts = stmt :: ctx.Stmts }

/// Returns statements in reversed order.
let ctxTakeStmts (ctx: MirCtx) =
  ctx.Stmts, { ctx with Stmts = [] }

let ctxFreshVar (ctx: MirCtx) (ident: string) (ty: Ty) loc =
  let serial = ctx.Serial + 1
  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars = ctx.Vars |> Map.add serial (VarDef.Var (ident, ty, loc))
    }
  let refExpr = MExpr.Ref (serial, ty, loc)
  refExpr, serial, ctx

let ctxLetFreshVar (ctx: MirCtx) (ident: string) (ty: Ty) loc =
  let refExpr, serial, ctx = ctxFreshVar ctx ident ty loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (serial, MInit.UnInit, ty, loc))
  let setStmt expr = MStmt.Set (serial, expr, loc)
  refExpr, setStmt, ctx

let ctxFreshLabel (ctx: MirCtx) (ident: string) loc =
  let serial = ctx.LabelSerial + 1
  let ctx = { ctx with LabelSerial = ctx.LabelSerial + 1 }
  let ident = sprintf "%s_%d" ident serial
  let labelStmt = MStmt.Label (ident, loc)
  labelStmt, ident, ctx

/// Gets if the serial denotes to a variant function.
let ctxIsVariantFun (ctx: MirCtx) serial =
  match ctx.Vars |> Map.tryFind serial with
  | Some (VarDef.Variant _) ->
    true
  | _ ->
    false

let mopFrom op =
  match op with
  | Op.Add -> MOp.Add
  | Op.Sub -> MOp.Sub
  | Op.Mul -> MOp.Mul
  | Op.Div -> MOp.Div
  | Op.Mod -> MOp.Mod
  | Op.Eq -> MOp.Eq
  | Op.Ne -> MOp.Ne
  | Op.Lt -> MOp.Lt
  | Op.Le -> MOp.Le
  | Op.Gt
  | Op.Ge
  | Op.Pipe
  | Op.And
  | Op.Or
  | Op.App
  | Op.Cons _
  | Op.Range
  | Op.Index -> failwith "Never: We don't use > >= && || :: .. in MIR"

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.Uni (MUniOp.Proj index, expr, resultTy, loc)

let strAddExpr ctx _op l r (_, loc) =
  MExpr.Bin (MOp.StrAdd, l, r, tyStr, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let opScalarExpr ctx op l r (ty, loc) =
  MExpr.Bin (op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let strCmpExpr ctx op l r (ty, loc) =
  let strCmpExpr = MExpr.Bin (MOp.StrCmp, l, r, tyInt, loc)
  let zeroExpr = MExpr.Lit (Lit.Int 0, loc)
  let opExpr = MExpr.Bin (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

/// Generates a comparison expression.
let cmpExpr ctx (op: MOp) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)
  match mexprToTy l with
  | Ty.Con ((TyCon.Bool | TyCon.Int | TyCon.Char), _) ->
    opScalarExpr ctx op l r (ty, loc)
  | Ty.Con (TyCon.Str, _) ->
    strCmpExpr ctx op l r (ty, loc)
  | _ ->
    failwith "unimpl"

let mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MExpr.Lit (lit, loc)
  let eqExpr, ctx = cmpExpr ctx MOp.Eq expr litExpr tyBool loc
  let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr = MExpr.Uni (MUniOp.ListIsEmpty, expr, tyList itemTy, loc)
  let gotoStmt = MStmt.GotoUnless (isEmptyExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let listTy = tyList itemTy
  let isEmpty = MExpr.Uni (MUniOp.ListIsEmpty, expr, tyBool, loc)
  let nonEmpty = MExpr.Uni (MUniOp.Not, isEmpty, tyBool, loc)
  let gotoStmt = MStmt.GotoUnless (nonEmpty, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  let head = MExpr.Uni (MUniOp.ListHead, expr, itemTy, loc)
  let tail = MExpr.Uni (MUniOp.ListTail, expr, listTy, loc)
  let _, ctx = mirifyPat ctx endLabel l head
  let _, ctx = mirifyPat ctx endLabel r tail
  false, ctx

let mirifyPatRef (ctx: MirCtx) endLabel serial ty loc expr =
  match ctx.Vars |> Map.find serial with
  | VarDef.Variant _ ->
    // Compare tags.
    let lTagExpr = MExpr.Uni (MUniOp.Tag, expr, tyInt, loc)
    let rTagExpr = MExpr.Ref (serial, tyInt, loc)
    let eqExpr = MExpr.Bin (MOp.Eq, lTagExpr, rTagExpr, tyBool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
    true, ctxAddStmt ctx letStmt

let mirifyPatCall (ctx: MirCtx) endLabel serial args ty loc expr =
  match ctx.Vars |> Map.find serial, args with
  | VarDef.Variant (_, _, _, payloadTy, _, _), [payload] ->
    // Compare tags.
    let lTagExpr = MExpr.Uni (MUniOp.Tag, expr, tyInt, loc)
    let rTagExpr = MExpr.Ref (serial, tyInt, loc)
    let eqExpr = MExpr.Bin (MOp.Eq, lTagExpr, rTagExpr, tyBool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt

    // Extract content.
    let extractExpr = MExpr.Uni (MUniOp.GetVariant serial, expr, payloadTy, loc)
    let _, ctx = mirifyPat ctx endLabel payload extractExpr
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
    true, ctxAddStmt ctx letStmt

let mirifyPatTuple ctx endLabel itemPats itemTys expr loc =
  let rec go covered ctx i itemPats itemTys =
    match itemPats, itemTys with
    | [], [] ->
      covered, ctx
    | itemPat :: itemPats, itemTy :: itemTys ->
      let item = projExpr expr i itemTy loc
      let itemCovered, ctx = mirifyPat ctx endLabel itemPat item
      go (covered && itemCovered) ctx (i + 1) itemPats itemTys
    | _ ->
      failwith "Never"
  go true ctx 0 itemPats itemTys

let mirifyPatAs ctx endLabel pat serial expr loc =
  let ty, _ = patExtract pat
  let ctx = ctxAddStmt ctx (MStmt.LetVal (serial, MInit.Expr expr, ty, loc))
  let expr = MExpr.Ref (serial, ty, loc)
  let covers, ctx = mirifyPat ctx endLabel pat expr
  covers, ctx

/// Processes pattern matching
/// to generate let-val statements for each subexpression
/// and goto statements when determined if the pattern to match.
/// Determines if the pattern covers the whole.
let mirifyPat ctx (endLabel: string) (pat: HPat) (expr: MExpr): bool * MirCtx =
  match pat with
  | HPat.Ref ("_", _, _, _) ->
    // Discard result.
    true, ctx
  | HPat.Lit (lit, loc) ->
    mirifyPatLit ctx endLabel lit expr loc
  | HPat.Nil (itemTy, loc) ->
    mirifyPatNil ctx endLabel itemTy expr loc
  | HPat.Ref (_, serial, ty, loc) ->
    mirifyPatRef ctx endLabel serial ty loc expr
  | HPat.Call (HPat.Ref (_, serial, _, _), args, ty, loc) ->
    mirifyPatCall ctx endLabel serial args ty loc expr
  | HPat.Cons (l, r, itemTy, loc) ->
    mirifyPatCons ctx endLabel l r itemTy loc expr
  | HPat.Tuple (itemPats, Ty.Con (TyCon.Tuple, itemTys), loc) ->
    mirifyPatTuple ctx endLabel itemPats itemTys expr loc
  | HPat.As (pat, _, serial, loc) ->
    mirifyPatAs ctx endLabel pat serial expr loc
  | HPat.Or _ ->
    failwith "Unimpl nested OR pattern."
  | HPat.Nav _ ->
    failwith "Never: Nav pattern in mirify"
  | HPat.Call _ ->
    failwith "Never: Call pattern incorrect."
  | HPat.Tuple _ ->
    failwith "Never: Tuple pattern must be of tuple type."
  | HPat.Anno _ ->
    failwith "Never annotation pattern in MIR-ify stage."

let mirifyExprRef (ctx: MirCtx) valRef ty loc =
  match valRef with
  | HValRef.Var serial ->
    match ctx.Vars |> Map.tryFind serial with
    | Some (VarDef.Variant (_, tySerial, _, _, _, _)) ->
      MExpr.Variant (tySerial, serial, ty, loc), ctx
    | Some (VarDef.Fun (_, _, _, loc)) ->
      MExpr.Proc (serial, ty, loc), ctx
    | _ ->
      MExpr.Ref (serial, ty, loc), ctx
  | HValRef.Prim _ ->
    failwithf "Never: Primitives must appear as callee."

let mirifyBlock ctx expr =
  let blockCtx = ctxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = ctxTakeStmts blockCtx
  let ctx = ctxRollBack ctx blockCtx
  stmts, expr, ctx

[<RequireQualifiedAccess>]
type Space =
  | CoverAll
  /// Space identified by int.
  | Variant
    of int * Space
  /// Reference of space. Used for recursive spaces. Never empty.
  | Ref
    of int * (unit -> Space)
  | Union
    of Space list

let spaceCoverAll =
  Space.CoverAll

let spaceRef serial thunk =
  Space.Ref (serial, thunk)

let spaceEmpty =
  Space.Union []

let spaceUnit =
  spaceCoverAll

let spaceVariant variant =
  Space.Variant variant

let spaceSum variants =
  variants |> listMap spaceVariant |> spaceUnion

let spaceUnion spaces =
  let rec go spaces acc =
    match spaces with
    | [] ->
      acc

    | Space.Union subspaces :: spaces ->
      acc |> go subspaces |> go spaces

    | space :: spaces when space |> spaceIsEmpty ->
      acc |> go spaces

    | space :: spaces ->
      (space :: acc) |> go spaces

  [] |> go spaces |> Space.Union

let rec spaceIsEmpty space =
  match space with
  | Space.CoverAll
  | Space.Ref _ ->
    false

  | Space.Variant (_, subspace) ->
    subspace |> spaceIsEmpty

  | Space.Union spaces ->
    spaces |> List.forall spaceIsEmpty

let rec spaceExclude first second =
  match first, second with
  | _, Space.CoverAll
  | Space.Union [], _ ->
    spaceEmpty

  | Space.CoverAll, _
  | _, Space.Union [] ->
    first

  | Space.Variant (tag, firstSpace), Space.Variant (secondTag, secondSpace)
    when tag = secondTag ->
    let subspace = spaceExclude firstSpace secondSpace
    spaceVariant (tag, subspace)

  | Space.Variant _, Space.Variant _ ->
    first

  | _, Space.Union seconds ->
    seconds |> List.fold spaceExclude first

  | Space.Union firsts, _ ->
    firsts |> List.map (fun first -> spaceExclude first second) |> spaceUnion

  | Space.Ref (firstRef, _), Space.Ref (secondRef, _)
    when firstRef = secondRef ->
    spaceEmpty

  | Space.Ref (_, thunk), _ ->
    spaceExclude (thunk ()) second

  | _, Space.Ref (_, thunk) ->
    // Never happens because patterns don't generate ref spaces.
    assert false
    spaceExclude first (thunk ())

let spaceCovers other cover =
  spaceExclude other cover |> spaceIsEmpty

let tyToSpace ctx ty =
  let rec go ty =
    match ty with
    | Ty.Con (TyCon.Bool, []) ->
      spaceSum
        [
          // false
          0, spaceUnit
          // true
          1, spaceUnit
        ]

    | Ty.Con (TyCon.Ref tySerial, []) ->
      let variants = ctxGetVariants ctx tySerial
      let rec thunk () =
        variants
        |> List.map (fun (variantSerial, payloadTy) ->
            variantSerial, go payloadTy
          )
        |> spaceSum

      spaceRef tySerial thunk

    | Ty.Con (TyCon.Tuple, []) ->
      spaceUnit

    | Ty.Con (TyCon.Tuple, itemTys) ->
      itemTys |> List.mapi (fun i itemTy -> i, go itemTy) |> spaceSum

    | Ty.Con (TyCon.List, [itemTy]) ->
      let itemSpace = go itemTy
      let rec thunk () =
        let consSpace =
          spaceSum
            [
              // head
              0, itemSpace
              // tail
              1, spaceRef (-1) thunk
            ]
        spaceSum
          [
            // nil
            0, spaceUnit
            // cons
            1, consSpace
          ]
      spaceRef (-2) thunk

    | _ ->
      spaceCoverAll

  go ty

let patToSpace ctx pat =
  let rec go pat =
    match pat with
    | HPat.Lit (Lit.Bool false, _) ->
      spaceSum [0, spaceUnit]

    | HPat.Lit (Lit.Bool true, _) ->
      spaceSum [1, spaceUnit]

    | HPat.Ref (_, varSerial, _, _) ->
      match ctxGetVar ctx varSerial with
      | VarDef.Var _ ->
        spaceCoverAll

      | VarDef.Variant _ ->
        spaceSum [varSerial, spaceUnit]

      | _ ->
        failwith "Never: Functions can't be patterns"

    | HPat.Call (HPat.Ref (_, varSerial, _, _), [payloadPat], _, _)
      when ctxIsVariantFun ctx varSerial ->
      spaceSum [varSerial, go payloadPat]

    | HPat.Tuple ([], _, _) ->
      spaceUnit

    | HPat.Tuple (itemPats, _, _) ->
      itemPats |> List.mapi (fun i itemPat -> i, go itemPat) |> spaceSum

    | HPat.Nil _ ->
      spaceSum [0, spaceUnit]

    | HPat.Cons (headPat, tailPat, _, _) ->
      let consSpace =
        spaceSum
          [
            0, go headPat
            1, go tailPat
          ]
      spaceSum [1, consSpace]

    | HPat.Or (_first, _second, _, _) ->
      spaceEmpty

    | HPat.As (pat, _, _, _) ->
      go pat

    | HPat.Anno (pat, _, _) ->
      go pat

    | HPat.Lit _
    | HPat.Nav _
    | _ ->
      spaceEmpty

  go pat

let patsToSpace ctx pats =
  pats |> List.map (patToSpace ctx) |> spaceUnion

let patsIsCovering ctx ty pats =
  if patsIsCoveringOld pats then
    true
  else
    let tySpace = ty |> tyToSpace ctx
    let patSpace = pats |> patsToSpace ctx
    eprintfn "pat=%A ty=%A" pats ty
    eprintfn "pats=%A tys=%A ex=%A" patSpace tySpace (spaceExclude tySpace patSpace)
    patSpace |> spaceCovers tySpace

/// Gets if the target must match with any of the patterns.
let patsIsCoveringOld pats =
  let rec go pat =
    match pat with
    | HPat.Ref _ ->
      true
    | HPat.Lit _
    | HPat.Nil _
    | HPat.Nav _
    | HPat.Cons _
    | HPat.Call _ ->
      false
    | HPat.Tuple (itemPats, _, _) ->
      itemPats |> List.forall go
    | HPat.As (pat, _, _, _) ->
      go pat
    | HPat.Anno (pat, _, _) ->
      go pat
    | HPat.Or (first, second, _, _) ->
      go first || go second
  List.exists go pats

let mirifyExprMatch ctx target arms ty loc =
  let noLabel = "<NEVER>"
  let temp, tempSet, ctx = ctxLetFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = ctxFreshLabel ctx "end_match" loc

  let target, ctx = mirifyExpr ctx target

  let isCovering =
    arms
    |> List.choose
      (fun (pat, guard, _) -> if hxIsAlwaysTrue guard then Some pat else None)
    |> patsIsCovering ctx (mexprToTy target)

  /// By walking over arms, calculates what kind of MIR instructions to emit.
  let rec goArms ctx acc firstPat arms =
    match arms with
    | (pat, guard, body) :: arms ->
      let pats = patNormalize pat
      let disjCount = pats |> List.length

      // No need to jump to body from pattern if no OR patterns.
      let needsJump = disjCount > 1

      let bodyLabel, ctx =
        if not needsJump then noLabel, ctx else
        let _, bodyLabel, ctx = ctxFreshLabel ctx "match_body" loc
        bodyLabel, ctx

      let rec goPats ctx acc firstPat pats =
        match pats with
        | pat :: pats ->
          // Label on the pattern.
          // The first pattern's label is unnecessary and not created.
          let acc, ctx =
            if firstPat then acc, ctx else
            let _, patLabel, ctx = ctxFreshLabel ctx "next" loc
            MatchIR.PatLabel patLabel :: acc, ctx
          let acc =
            MatchIR.Pat (pat, noLabel) :: acc
          let acc =
            if not needsJump then acc else
            MatchIR.GoBody bodyLabel :: acc

          goPats ctx acc false pats
        | [] ->
          acc, ctx

      let acc, ctx = goPats ctx acc firstPat pats

      let acc =
        if not needsJump then acc else
        MatchIR.BodyLabel bodyLabel :: acc
      let acc = MatchIR.Guard (guard, noLabel) :: acc
      let acc = MatchIR.Body body :: acc
      goArms ctx acc false arms
    | [] ->
      let _, exhaustLabel, ctx = ctxFreshLabel ctx "next" loc
      let acc = MatchIR.PatLabel exhaustLabel :: acc
      acc, ctx

  /// Fixes up instructions.
  /// 1. By walking over instructions in the reversed order,
  /// fill `nextLabel` fields.
  /// 2. Remove trivial guards.
  let rec fixUp acc nextLabel instructionsRev =
    match instructionsRev with
    | MatchIR.PatLabel patLabel as instruction :: rest ->
      // The leading instructions refers to this label as next one.
      fixUp (instruction :: acc) patLabel rest
    | MatchIR.Pat (pat, _) :: rest ->
      let acc = MatchIR.Pat (pat, nextLabel) :: acc
      fixUp acc nextLabel rest
    | MatchIR.Guard (guard, _) :: rest ->
      let acc =
        // Trivial guard is unnecessary.
        if guard |> hxIsAlwaysTrue then acc else
        MatchIR.Guard (guard, nextLabel) :: acc
      fixUp acc nextLabel rest
    | instruction :: rest ->
      fixUp (instruction :: acc) nextLabel rest
    | [] ->
      acc

  /// Emits MIR instructions based on matching IRs.
  let rec emit ctx instructions =
    match instructions with
    | MatchIR.PatLabel patLabel :: rest ->
      let ctx = ctxAddStmt ctx (MStmt.Label (patLabel, loc))
      emit ctx rest
    | MatchIR.Pat (pat, nextLabel) :: rest ->
      // Perform pattern matching. Go to the next pattern on failure.
      let _, ctx = mirifyPat ctx nextLabel pat target
      emit ctx rest
    | MatchIR.GoBody bodyLabel :: rest ->
      let ctx = ctxAddStmt ctx (MStmt.Goto (bodyLabel, loc))
      emit ctx rest
    | MatchIR.BodyLabel bodyLabel :: rest ->
      let ctx = ctxAddStmt ctx (MStmt.Label (bodyLabel, loc))
      emit ctx rest
    | MatchIR.Guard (guard, nextLabel) :: rest ->
      let ctx =
        if guard |> hxIsAlwaysTrue then ctx else
        let guard, ctx = mirifyExpr ctx guard
        ctxAddStmt ctx (MStmt.GotoUnless (guard, nextLabel, loc))
      emit ctx rest
    | MatchIR.Body body :: rest ->
      // Enter into the body.
      let body, ctx = mirifyExpr ctx body
      // Leave the match.
      let ctx = ctxAddStmt ctx (tempSet body)
      let ctx = ctxAddStmt ctx (MStmt.Goto (endLabel, loc))
      emit ctx rest
    | [] ->
      // Abort if exhaust.
      if isCovering then ctx else
      let abortStmt = MStmt.Exit (MExpr.Lit (Lit.Int 1, loc), loc)
      let ctx = ctxAddStmt ctx abortStmt
      ctx

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = ctxAddStmt ctx endLabelStmt

  temp, ctx

let mirifyExprIndex ctx l r _ loc =
  match exprToTy l, exprToTy r with
  | Ty.Con (TyCon.Str, _), Ty.Con (TyCon.Int, _) ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Bin (MOp.StrIndex, l, r, tyChar, loc), ctx
  | Ty.Con (TyCon.Str, _), Ty.Con (TyCon.Range, _) ->
    let rl, rr =
      match r with
      | HExpr.Bin (Op.Range, rl, rr, _, _) -> rl, rr
      | _ -> failwith "Never"
    let l, ctx = mirifyExpr ctx l
    let rl, ctx = mirifyExpr ctx rl
    let rr, ctx = mirifyExpr ctx rr
    let temp, tempSerial, ctx = ctxFreshVar ctx "slice" tyStr loc
    let funTy = tyFun tyStr (tyFun tyInt (tyFun tyInt tyStr))
    let callPrim = MInit.CallPrim (HPrim.StrSlice, [l; rl; rr], funTy)
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, callPrim, tyStr, loc))
    temp, ctx
  | _ ->
    failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let ctx = ctxAddStmt ctx (MStmt.Exit (arg, loc))
  MExpr.Default (ty, loc), ctx

let mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = ctxFreshVar ctx "box" tyObj loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Box arg, tyObj, loc))
  temp, ctx

let mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.Uni (MUniOp.Unbox, arg, ty, loc), ctx

let mirifyExprCallStrLength ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.Uni (MUniOp.StrLen, arg, ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.Uni (MUniOp.Not, arg, ty, notLoc), ctx

let mirifyExprCallVariantFun (ctx: MirCtx) serial payload ty loc =
  // Put payload on the heap.
  let payload, ctx = mirifyExpr ctx payload
  let payloadTy = mexprToTy payload
  let _, payloadSerial, ctx = ctxFreshVar ctx "payload" payloadTy loc
  let payloadInit = MInit.Indirect payload
  let ctx = ctxAddStmt ctx (MStmt.LetVal (payloadSerial, payloadInit, payloadTy, loc))

  let temp, tempSerial, ctx = ctxFreshVar ctx "variant" ty loc
  let init = MInit.Variant (serial, payloadSerial)
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, init, ty, loc))
  temp, ctx

let mirifyExprOpCons ctx l r listTy loc =
  let _, tempSerial, ctx = ctxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (l, r), listTy, loc))
  MExpr.Ref (tempSerial, listTy, loc), ctx

let mirifyExprTuple ctx items itemTys loc =
  let ty = tyTuple itemTys
  let _, tempSerial, ctx = ctxFreshVar ctx "tuple" ty loc

  let rec go acc ctx items =
    match items with
    | [] ->
      List.rev acc, ctx
    | item :: items ->
      let item, ctx = mirifyExpr ctx item
      go (item :: acc) ctx items
  let items, ctx = go [] ctx items

  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Tuple items, ty, loc))
  MExpr.Ref (tempSerial, ty, loc), ctx

let mirifyExprBin ctx op l r ty loc =
  match op with
  | Op.Cons ->
    mirifyExprOpCons ctx l r ty loc
  | Op.Index ->
    mirifyExprIndex ctx l r ty loc
  | Op.Gt ->
    mirifyExprBin ctx Op.Lt r l ty loc
  | Op.Ge ->
    mirifyExprBin ctx Op.Le r l ty loc
  | Op.Eq
  | Op.Ne
  | Op.Lt
  | Op.Le ->
    let op = mopFrom op
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    cmpExpr ctx op l r ty loc
  | Op.And
  | Op.Or
  | Op.Pipe ->
    failwith "Never: Desugared operators"
  | Op.App ->
    failwith "Never: Apps erased in FunTrans."
  | _ ->
    let op = mopFrom op
    let lTy = exprToTy l
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    match lTy with
    | Ty.Con ((TyCon.Int | TyCon.Char), _) ->
      opScalarExpr ctx op l r (ty, loc)
    | Ty.Con (TyCon.Str, _) when op = MOp.Add ->
      strAddExpr ctx op l r (ty, loc)
    | _ ->
      failwithf "unimpl"

let mirifyExprSemi ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let mirifyExprInfCallProc ctx callee args ty loc =
  let core () =
    match callee with
    | HExpr.Ref (_, HValRef.Prim prim, _, _) ->
      let primTy = exprToTy callee
      let (args, ctx) = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
      let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
      let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallPrim (prim, args, primTy), ty, loc))
      temp, ctx
    | _ ->
      let calleeTy = exprToTy callee
      let callee, ctx = mirifyExpr ctx callee
      let (args, ctx) = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
      let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
      let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallProc (callee, args, calleeTy), ty, loc))
      temp, ctx
  match args with
  | [arg] ->
    match callee with
    | HExpr.Ref (_, HValRef.Prim HPrim.Not, _, _) ->
      mirifyExprCallNot ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.Exit, _, _) ->
      mirifyExprCallExit ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.Box, _, _) ->
      mirifyExprCallBox ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.Unbox, _, _) ->
      mirifyExprCallUnbox ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.StrLength, _, _) ->
      mirifyExprCallStrLength ctx arg ty loc
    | HExpr.Ref (_, HValRef.Var serial, _, _) when ctxIsVariantFun ctx serial ->
      mirifyExprCallVariantFun ctx serial arg ty loc
    | _ ->
      core ()
  | _ ->
    core ()

let mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee
  let args, ctx = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
  let tempRef, tempSerial, ctx = ctxFreshVar ctx "app" resultTy loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallClosure (callee, args), resultTy, loc))
  tempRef, ctx

let mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = ctxFreshVar ctx "env" envTy envLoc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (envSerial, MInit.Expr env, envTy, envLoc))

  let tempRef, tempSerial, ctx = ctxFreshVar ctx "fun" funTy loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Closure (funSerial, envSerial), funTy, loc))
  tempRef, ctx

let mirifyExprInf ctx infOp args ty loc =
  match infOp, args, ty with
  | InfOp.List _, [], Ty.Con (TyCon.List, [itemTy]) ->
    MExpr.Default (tyList itemTy, loc), ctx
  | InfOp.Tuple, [], Ty.Con (TyCon.Tuple, []) ->
    MExpr.Default (tyUnit, loc), ctx
  | InfOp.Tuple, _, Ty.Con (TyCon.Tuple, itemTys) ->
    mirifyExprTuple ctx args itemTys loc
  | InfOp.Semi, _, _ ->
    mirifyExprSemi ctx args
  | InfOp.CallProc, callee :: args, _ ->
    mirifyExprInfCallProc ctx callee args ty loc
  | InfOp.CallClosure, callee :: args, _ ->
    mirifyExprInfCallClosure ctx callee args ty loc
  | InfOp.Closure funSerial, [env], _ ->
    mirifyExprInfClosure ctx funSerial env ty loc
  | t ->
    failwithf "Never: %A" t

let mirifyExprLetVal ctx pat init next letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init
  let ctx =
    if exhaustive then ctx else
    ctxAddErr ctx "Let pattern must be exhaustive for now" letLoc
  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprLetFun ctx calleeIdent calleeSerial argPats body next letLoc =
  let defineArg ctx argPat =
    match argPat with
    | HPat.Ref (_, serial, ty, loc) ->
      // NOTE: Optimize for usual cases to not generate redundant local vars.
      (serial, 1, ty, loc), ctx
    | _ ->
      let argTy, argLoc = patExtract argPat
      let arg, argSerial, ctx = ctxFreshVar ctx "arg" argTy argLoc
      let exhaustive, ctx = mirifyPat ctx "_never_" argPat arg
      let ctx =
        if exhaustive then ctx else
        ctxAddErr ctx "Argument pattern must be exhaustive for now" argLoc
      (argSerial, 1, argTy, argLoc), ctx

  let rec defineArgs acc ctx argPats =
    match argPats with
    | [] ->
      List.rev acc, ctx
    | argPat :: argPats ->
      let arg, ctx = defineArg ctx argPat
      defineArgs (arg :: acc) ctx argPats

  let mirifyFunBody ctx argPats body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs [] ctx argPats
    let lastExpr, ctx = mirifyExpr ctx body
    let returnStmt = MStmt.Return (lastExpr, blockLoc)
    let ctx = ctxAddStmt ctx returnStmt

    let stmts, ctx = ctxTakeStmts ctx
    let body = List.rev stmts
    args, blockTy, body, ctx

  let bodyCtx = ctxNewBlock ctx
  let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
  let ctx = ctxRollBack ctx bodyCtx
  let procStmt = MStmt.Proc ({ Callee = calleeSerial; Args = args; ResultTy = resultTy; Body = body; Main = calleeIdent = "main" }, letLoc)
  let ctx = ctxAddStmt ctx procStmt

  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprTyDecl ctx _tySerial _tyDecl loc =
  MExpr.Default (tyUnit, loc), ctx

let mirifyExprOpen ctx loc =
  MExpr.Default (tyUnit, loc), ctx

let mirifyExpr (ctx: MirCtx) (expr: HExpr): MExpr * MirCtx =
  match expr with
  | HExpr.Lit (lit, loc) ->
    MExpr.Lit (lit, loc), ctx
  | HExpr.Ref (_, serial, ty, loc) ->
    mirifyExprRef ctx serial ty loc
  | HExpr.Match (target, arms, ty, loc) ->
    mirifyExprMatch ctx target arms ty loc
  | HExpr.Bin (op, l, r, ty, loc) ->
    mirifyExprBin ctx op l r ty loc
  | HExpr.Inf (infOp, args, ty, loc) ->
    mirifyExprInf ctx infOp args ty loc
  | HExpr.Let (pat, body, next, _, loc) ->
    mirifyExprLetVal ctx pat body next loc
  | HExpr.LetFun (ident, serial, args, body, next, _, loc) ->
    mirifyExprLetFun ctx ident serial args body next loc
  | HExpr.TyDef (_, tySerial, tyDecl, loc) ->
    mirifyExprTyDecl ctx tySerial tyDecl loc
  | HExpr.Open (_, loc) ->
    mirifyExprOpen ctx loc
  | HExpr.If _
  | HExpr.Nav _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.Tuple, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    let ctx = ctxAddErr ctx error loc
    MExpr.Default (tyObj, loc), ctx

let mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, ctx
    | expr :: exprs ->
      let expr, ctx = mirifyExpr ctx expr
      go (expr :: acc) ctx exprs
  go [] ctx exprs

/// Collect all declaration contained by the statements.
let collectDecls (stmts: MStmt list) =
  let rec go decls stmts =
    match stmts with
    | MStmt.Proc (procDecl, loc) :: stmts ->
      let decls = go decls procDecl.Body
      let decls = MDecl.Proc (procDecl, loc) :: decls
      let decls = go decls stmts
      decls
    | _ :: stmts ->
      go decls stmts
    | [] ->
      decls
  go [] stmts |> List.rev

let mirify (expr: HExpr, tyCtx: TyCtx): MDecl list * MirCtx =
  let ctx = ctxFromTyCtx tyCtx

  // OK: It's safe to discard the expression thanks to main hoisting.
  let _expr, ctx = mirifyExpr ctx expr

  let stmts = ctx.Stmts |> List.rev
  let decls = collectDecls stmts
  decls, ctx
