module rec MiloneLang.Self

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers
open MiloneLang.Lexing
open MiloneLang.Parsing
open MiloneLang.AstToHir
open MiloneLang.Bundling
open MiloneLang.NameRes
open MiloneLang.Typing
open MiloneLang.MainHoist
open MiloneLang.ClosureConversion
open MiloneLang.EtaExpansion
open MiloneLang.Hoist
open MiloneLang.Monomorphizing
// open MiloneLang.Mir

let litToString lit =
  match lit with
  | Lit.Bool true ->
    "true"

  | Lit.Bool false ->
    "false"

  | Lit.Int value ->
    string value

  | Lit.Char value ->
    "'" + (if charNeedsEscaping value then charEscape value else string value) + "'"

  | Lit.Str value ->
    "\"" + strEscape value + "\""

let tokenToString token =
  match token with
  | Token.Error ->
    "Error"

  | Token.Bool false ->
    "false"

  | Token.Bool true ->
    "true"

  | Token.Int value ->
    string value

  | Token.Char value ->
    litToString (Lit.Char value)

  | Token.Str value ->
    litToString (Lit.Str value)

  | Token.Ident ident ->
    ident

  | Token.ParenL ->
    "("

  | Token.ParenR ->
    ")"

  | Token.BracketL ->
    "["

  | Token.BracketR ->
    "]"

  | Token.Amp ->
    "&"

  | Token.AmpAmp ->
    "&&"

  | Token.Arrow ->
    "->"

  | Token.Colon ->
    ":"

  | Token.ColonColon ->
    "::"

  | Token.Comma ->
    ","

  | Token.Dot ->
    "."

  | Token.DotDot ->
    ".."

  | Token.Eq ->
    "="

  | Token.Gt ->
    ">"

  | Token.GtEq ->
    ">="

  | Token.Lt ->
    "<"

  | Token.LtEq ->
    "<="

  | Token.LtGt ->
    "<>"

  | Token.Minus ->
    "-"

  | Token.Percent ->
    "%"

  | Token.Pipe ->
    "|"

  | Token.PipeGt ->
    "|>"

  | Token.PipePipe ->
    "||"

  | Token.Plus ->
    "+"

  | Token.Semi ->
    ";"

  | Token.Star ->
    "*"

  | Token.Slash ->
    "/"

  | Token.As ->
    "as"

  | Token.Do ->
    "do"

  | Token.Else ->
    "else"

  | Token.Fun ->
    "fun"

  | Token.If ->
    "if"

  | Token.In ->
    "in"

  | Token.Internal ->
    "internal"

  | Token.Let ->
    "let"

  | Token.Match ->
    "match"

  | Token.Module ->
    "module"

  | Token.Namespace ->
    "namespace"

  | Token.Of ->
    "of"

  | Token.Open ->
    "open"

  | Token.Private ->
    "private"

  | Token.Public ->
    "public"

  | Token.Rec ->
    "rec"

  | Token.Then ->
    "then"

  | Token.Type ->
    "type"

  | Token.When ->
    "when"

  | Token.With ->
    "with"

let atDump ty =
  match ty with
  | ATy.Missing loc ->
    dumpTreeFromError "missing" loc

  | ATy.App (ident, tys, _) ->
    dumpTreeNew ident (tys |> listMap atDump)

  | ATy.Suffix (lTy, ident, _) ->
    dumpTreeNew ident [atDump lTy]

  | ATy.Tuple (itemTys, _) ->
    dumpTreeNew "tuple" (listMap atDump itemTys)

  | ATy.Fun (sTy, tTy, _) ->
    dumpTreeNew "fun" ([sTy; tTy] |> listMap atDump)

let apDump (pat: APat) =
  match pat with
  | APat.Missing loc ->
    dumpTreeFromError "missing" loc

  | APat.Lit (lit, _) ->
    lit |> litToString |> dumpTreeNewLeaf

  | APat.Ident (ident, _) ->
    dumpTreeNewLeaf ident

  | APat.ListLit (pats, _) ->
    dumpTreeNew "list" (pats |> listMap apDump)

  | APat.Nav (l, r, _) ->
    dumpTreeNew ("." + r) [apDump l]

  | APat.Call (calleePat, argPats, _) ->
    dumpTreeNew "call" (
      apDump calleePat
      :: (argPats |> listMap apDump)
    )

  | APat.Cons (head, tail, _) ->
    dumpTreeNew "cons" [apDump head] |> dumpTreeAttachNext (apDump tail)

  | APat.TupleLit (pats, _) ->
    dumpTreeNew "tuple" (pats |> listMap apDump)

  | APat.As (pat, ident, _) ->
    dumpTreeNew ("as " + ident) [apDump pat]

  | APat.Anno (pat, ty, _) ->
    dumpTreeNew "anno" [apDump pat; atDump ty]

  | APat.Or (l, r, _) ->
    dumpTreeNew "or" [apDump l] |> dumpTreeAttachNext (apDump r)

  | APat.Fun (callee, args, _) ->
    dumpTreeNew "fun" (
      dumpTreeNewLeaf callee
      :: (args |> listMap apDump)
    )

let axDump (expr: AExpr) =
  match expr with
  | AExpr.Missing loc ->
    dumpTreeFromError "missing" loc

  | AExpr.Lit (lit, _) ->
    dumpTreeNewLeaf (litToString lit)

  | AExpr.Ident (ident, _) ->
    dumpTreeNewLeaf ident

  | AExpr.ListLit (items, _) ->
    dumpTreeNew "list" (items |> listMap axDump)

  | AExpr.If (cond, body, alt, _) ->
    dumpTreeNew "if" [
      axDump cond
      axDump body
      axDump alt
    ]

  | AExpr.Match (target, arms, _) ->
    let dumpArm (AArm (pat, guard, body, _)) =
      dumpTreeNew "arm" [apDump pat; axDump guard]
      |> dumpTreeAttachNext (axDump body)

    dumpTreeNew "match" (axDump target :: (arms |> listMap dumpArm))

  | AExpr.Fun (pats, body, _) ->
    dumpTreeNew "fun" (pats |> listMap apDump)
    |> dumpTreeAttachNext (axDump body)

  | AExpr.Nav (l, r, _) ->
    dumpTreeNew ("." + r) [axDump l]

  | AExpr.Index (l, r, _) ->
    dumpTreeNew "index" [axDump l]

  | AExpr.Uni (UniOp.Neg, arg, _) ->
    dumpTreeNew "-" [axDump arg]

  | AExpr.Bin (_, l, r, _) ->
    dumpTreeNew "bin" [axDump l; axDump r] // FIXME: binOp to string

  | AExpr.Range (items, _) ->
    dumpTreeNew "range" (items |> listMap axDump)

  | AExpr.TupleLit (items, _) ->
    dumpTreeNew "tuple" (items |> listMap axDump)

  | AExpr.Anno (body, ty, _) ->
    dumpTreeNew "anno" [axDump body; atDump ty]

  | AExpr.Semi (exprs, _) ->
    dumpTreeNew "semi" (exprs |> listMap axDump)

  | AExpr.Let (pat, body, next, _) ->
    dumpTreeNew "let" [apDump pat; axDump body]
    |> dumpTreeAttachNext (axDump next)

  | AExpr.TySynonym (ident, ty, _) ->
    dumpTreeNew "synonym" [dumpTreeNewLeaf ident]
    |> dumpTreeAttachNext (atDump ty)

  | AExpr.TyUnion (ident, variants, _) ->
    let dumpVariant (AVariant (ident, _, _)) =
      dumpTreeNewLeaf ident

    dumpTreeNew "union" (dumpTreeNewLeaf ident :: (variants |> listMap dumpVariant))

  | AExpr.Open (path, _) ->
    dumpTreeNew "open" (path |> listMap dumpTreeNewLeaf)

let serialToIdent nameCtx serial =
  (nameCtx |> nameCtxFind serial) + "_" + string serial

let tyConToString nameCtx tyCon =
  match tyCon with
  | TyCon.Bool ->
    "bool"

  | TyCon.Int ->
    "int"

  | TyCon.Char ->
    "char"

  | TyCon.Str ->
    "str"

  | TyCon.Obj ->
    "obj"

  | TyCon.Fun ->
    "fun"

  | TyCon.Tuple ->
    "tuple"

  | TyCon.List ->
    "list"

  | TyCon.Ref tySerial ->
    serialToIdent nameCtx tySerial

let tyDump nameCtx (ty: Ty) =
  match ty with
  | Ty.Error (0, 0) ->
    dumpTreeNewLeaf "untyped"

  | Ty.Error loc ->
    dumpTreeFromError "ERROR" loc

  | Ty.Con (tyCon, tys) ->
    dumpTreeNew (tyConToString nameCtx tyCon) (tys |> listMap (tyDump nameCtx))

  | Ty.Meta (tySerial, _) ->
    dumpTreeNewLeaf (serialToIdent nameCtx tySerial)

let patDump nameCtx (pat: HPat) =
  match pat with
  | HPat.Lit (lit, _) ->
    lit |> litToString |> dumpTreeNewLeaf

  | HPat.Nil (itemTy, _) ->
    dumpTreeNew "[]" [tyDump nameCtx itemTy]

  | HPat.OptionNone (itemTy, _) ->
    dumpTreeNew "None" [tyDump nameCtx itemTy]

  | HPat.OptionSome (itemTy, _) ->
    dumpTreeNew "Some" [tyDump nameCtx itemTy]

  | HPat.Discard _ ->
    dumpTreeNewLeaf "_"

  | HPat.Ref (varSerial, ty, _) ->
    dumpTreeNew (serialToIdent nameCtx varSerial) [tyDump nameCtx ty]

  | HPat.Nav (l, r, _, _) ->
    dumpTreeNew ("." + r) [patDump nameCtx l]

  | HPat.Call (callee, args, _, _) ->
    let callee = callee |> patDump nameCtx
    let args = args |> listMap (patDump nameCtx)
    dumpTreeNew "call" (callee :: args)

  | HPat.Cons (l, r, _, _) ->
    dumpTreeNew "cons" [patDump nameCtx l; patDump nameCtx r]

  | HPat.Tuple (itemPats, _, _) ->
    let itemPats = itemPats |> listMap (patDump nameCtx)
    dumpTreeNew "tuple" itemPats

  | HPat.As (innerPat, varSerial, _) ->
    let innerPat = innerPat |> patDump nameCtx
    let ident = serialToIdent nameCtx varSerial
    dumpTreeNew ("as " + ident) [innerPat]

  | HPat.Anno (innerPat, ty, _) ->
    let innerPat = innerPat |> patDump nameCtx
    let ty = ty |> tyDump nameCtx
    dumpTreeNew "anno" [innerPat; ty]

  | HPat.Or (l, r, _, _) ->
    dumpTreeNew "|" [patDump nameCtx l]
    |> dumpTreeAttachNext (patDump nameCtx r)

let hxDump nameCtx (expr: HExpr) =
  let showIdent serial = serialToIdent nameCtx serial

  match expr with
  | HExpr.Lit (lit, _) ->
    lit |> litToString |> dumpTreeNewLeaf

  | HExpr.Prim _ ->
    dumpTreeNewLeaf "prim"

  | HExpr.Ref (serial, ty, _) ->
    dumpTreeNew (showIdent serial) [tyDump nameCtx ty]

  | HExpr.Match (target, arms, _, _) ->
    let onArm (pat, guard, body) =
      dumpTreeNew "arm" [
        patDump nameCtx pat
        hxDump nameCtx guard
        hxDump nameCtx body
      ]
    let target = hxDump nameCtx target
    let arms = arms |> listMap onArm
    dumpTreeNew "match" (target :: arms)

  | HExpr.Nav (l, r, _, _) ->
    dumpTreeNew ("." + r) [hxDump nameCtx l]

  | HExpr.Inf (InfOp.Semi, items, _, _) ->
    let len = items |> listLength
    if len >= 2 then
      let last = items |> listLast
      let items = items |> listTruncate (len - 1)
      dumpTreeNew "semi" (items |> listMap (hxDump nameCtx))
      |> dumpTreeAttachNext (hxDump nameCtx last)
    else
      let items = items |> listMap (hxDump nameCtx)
      dumpTreeNew "semi" items

  | HExpr.Inf (_, items, _, _) ->
    let items = items |> listMap (hxDump nameCtx)
    dumpTreeNew "inf" items

  | HExpr.Let (pat, body, next, _, _) ->
    dumpTreeNew "let-val" [
      patDump nameCtx pat
      hxDump nameCtx body
    ]
    |> dumpTreeAttachNext (hxDump nameCtx next)

  | HExpr.LetFun (callee, _, args, body, next, _, _) ->
    let callee = dumpTreeNewLeaf (showIdent callee)
    let args = args |> listMap (patDump nameCtx)
    let body = body |> hxDump nameCtx
    dumpTreeNew "let-fun" (callee :: (listAppend args [body]))
    |> dumpTreeAttachNext (hxDump nameCtx next)

  | HExpr.TyDecl (tySerial, TyDecl.Synonym (ty, _), _) ->
    dumpTreeNew "synonym" [
      dumpTreeNewLeaf (showIdent tySerial)
      tyDump nameCtx ty
    ]

  | HExpr.TyDecl (tySerial, TyDecl.Union (_, variants, _), _) ->
    let onVariant (_, varSerial, _, payloadTy) =
      dumpTreeNew (showIdent varSerial) [tyDump nameCtx payloadTy]

    let variants = variants |> listMap onVariant
    dumpTreeNew "union" (dumpTreeNewLeaf (showIdent tySerial) :: variants)

  | HExpr.Open (path, _) ->
    dumpTreeNew "open" (path |> listMap dumpTreeNewLeaf)

  | HExpr.Error (msg, loc) ->
    dumpTreeFromError msg loc

let doSelf (fileReadAllText: string -> string) =
  // let doFile (filePath: string) =
  //   printfn "FILE %s" filePath

  //   let source = fileReadAllText filePath
  //   let tokens = source |> tokenize

  //   tokens |> listIter (fun (token, (y, x)) -> printfn "%s (%d, %d)" (tokenToString token) y x)

  //   let ast, errors = tokens |> parse
  //   printfn "AST:"
  //   printfn "%s" (ast |> axDump |> dumpTreeToString)

  //   errors |> listIter (fun (msg, (y, x)) -> printfn "ERROR %s (%d:%d)" msg (y + 1) (x + 1))

  //   let nameCtx = nameCtxEmpty ()
  //   let expr, nameCtx = (ast, nameCtx) |> astToHir
  //   printfn "HIR:"
  //   printfn "%s" (expr |> hxDump nameCtx |> dumpTreeToString)

  // doFile "MiloneLang/Lexing.fs"
  // doFile "MiloneLang/Parsing.fs"
  // doFile "MiloneLang/AstToHir.fs"

  let readModuleFile moduleName =
    printfn "Load %s" moduleName
    fileReadAllText ("tests/examples/MiloneLang/" + moduleName + ".fs")

  let projectName = "MiloneLang"
  let nameCtx = nameCtxEmpty ()

  let expr, nameCtx, errorListList = parseProjectModules readModuleFile projectName nameCtx

  printfn "Name resolution"
  let expr, scopeCtx = nameRes (expr, nameCtx)

  let tyCtxHasError tyCtx =
    tyCtx |> tyCtxGetLogs |> listIsEmpty |> not

  let logs =
    printfn "Type inference"
    let expr, tyCtx = infer (expr, scopeCtx, errorListList)
    if tyCtx |> tyCtxHasError then
      tyCtx |> tyCtxGetLogs
    else

    printfn "Hoist main"
    let expr, tyCtx = hoistMain (expr, tyCtx)

    printfn "Closure conversion"
    let expr, tyCtx = declosure (expr, tyCtx)
    if tyCtx |> tyCtxHasError then
      tyCtx |> tyCtxGetLogs
    else

    printfn "Eta expansion"
    let expr, tyCtx = uneta (expr, tyCtx)
    if tyCtx |> tyCtxHasError then
      tyCtx |> tyCtxGetLogs
    else

    printfn "Hoist"
    let expr, tyCtx = hoist (expr, tyCtx)

    printfn "Monomorphization"
    let expr, tyCtx = monify (expr, tyCtx)
    tyCtx |> tyCtxGetLogs
    // if tyCtx |> tyCtxHasError then
    //   tyCtx |> tyCtxGetLogs
    // else

    // printfn "Mir"
    // let stmts, mirCtx = mirify (expr, tyCtx)

    // printfn "stmts %d" (stmts |> listLength)
    // mirCtx |> mirCtxGetLogs

  // printfn "HIR:"
  // printfn "%s" (expr |> hxDump nameCtx |> dumpTreeToString)

  logs |> listIter (fun (log, loc) ->
    printfn "ERROR %s" (log |> logToString loc)
  )
  0
