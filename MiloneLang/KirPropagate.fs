module rec MiloneLang.KirPropagate

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers
open MiloneLang.KirGen

type private KirPropagateCtx =
  { VarDefs: AssocMap<VarSerial, KVarDef>
    VarUses: AssocMap<VarSerial, int> }

let private ctxEmpty (): KirPropagateCtx =
  { VarDefs = mapEmpty intCmp
    VarUses = mapEmpty intCmp }

let private findKVarDef varSerial (ctx: KirPropagateCtx) = ctx.VarDefs |> mapTryFind varSerial

let private kpDefVar varSerial varDef (ctx: KirPropagateCtx) =
  // printfn "// kp: [TRACE] def #%d := %s" varSerial (objToString varDef)

  { ctx with
      VarDefs = ctx.VarDefs |> mapAdd varSerial varDef }

let private kpUseTerm term (ctx: KirPropagateCtx) =
  match term with
  | KVarTerm (varSerial, _, loc) ->
      match ctx |> findKVarDef varSerial with
      | Some (KLitVarDef lit) ->
          printfn "// kp: [TRACE] const prop #%d => %s" varSerial (objToString lit)

          KLitTerm(lit, loc), ctx

      | Some (KSelectVarDef (term, KSelfPath)) ->
          printfn "// kp: [TRACE] remove mov #%d => %s" varSerial (objToString term)

          term, ctx

      | _ -> term, ctx

  | _ -> term, ctx

let private kpUseTerms terms ctx =
  (terms, ctx)
  |> stMap (fun (term, ctx) -> kpUseTerm term ctx)

let private kpNode (node: KNode) ctx: KNode * KirPropagateCtx =
  match node with
  | KJumpNode (jointSerial, args, loc) ->
      let args, ctx = ctx |> kpUseTerms args
      KJumpNode(jointSerial, args, loc), ctx

  | KReturnNode (funSerial, args, loc) ->
      let args, ctx = ctx |> kpUseTerms args
      KReturnNode(funSerial, args, loc), ctx

  | KSelectNode (term, path, result, cont, loc) ->
      let cont, ctx =
        ctx
        |> kpDefVar result (KSelectVarDef(term, path))
        |> kpNode cont

      let term, ctx = ctx |> kpUseTerm term
      KSelectNode(term, path, result, cont, loc), ctx

  | KPrimNode (prim, args, results, conts, loc) ->
      let ctx =
        match prim, args, results with
        | KAddPrim, [ KLitTerm (IntLit l, _); KLitTerm (IntLit r, _) ], [ result ] ->
            printfn "// kp: [TRACE] lit #%d := %d + %d" result l r

            ctx |> kpDefVar result (KLitVarDef(IntLit(l + r)))

        | _ -> ctx

      let conts, ctx =
        (conts, ctx)
        |> stMap (fun (cont, ctx) -> kpNode cont ctx)

      let args, ctx = ctx |> kpUseTerms args
      KPrimNode(prim, args, results, conts, loc), ctx

  | KJointNode (joints, cont, loc) ->
      let joints, ctx =
        (joints, ctx)
        |> stMap (fun (jointBinding, ctx) ->
             let (KJointBinding (jointSerial, args, body, loc)) = jointBinding

             let body, ctx = ctx |> kpNode body

             KJointBinding(jointSerial, args, body, loc), ctx)

      let cont, ctx = ctx |> kpNode cont
      KJointNode(joints, cont, loc), ctx

let kirPropagate (root: KRoot, kirGenCtx: KirGenCtx): KRoot * KirGenCtx =
  let (KRoot (funBindings)) = root

  let ctx = ctxEmpty ()

  let funBindings, _ =
    (funBindings, ctx)
    |> stMap (fun (funBinding, ctx) ->
         let (KFunBinding (funSerial, args, body, loc)) = funBinding

         let body, ctx = ctx |> kpNode body

         KFunBinding(funSerial, args, body, loc), ctx)

  KRoot(funBindings), kirGenCtx
