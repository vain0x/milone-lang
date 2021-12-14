module rec MiloneTranslation.XirToCir

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneStd.StdMap
open MiloneStd.StdMultimap
open MiloneStd.StdSet
open MiloneTranslation.Cir
open MiloneTranslation.Xir

module S = MiloneStd.StdString

type private TraceFun = string -> string list -> unit

// -----------------------------------------------
// Context
// -----------------------------------------------

// Read context.
type private Rx = { BodyDef: XBodyDef; Trace: TraceFun }

// Write context.
type private Wx =
  { Done: TreeSet<XBlockId>
    Stmts: CStmt list
    Decls: CDecl list }

let private newRx trace (bodyDef: XBodyDef) : Rx = { BodyDef = bodyDef; Trace = trace }

let private newWx () : Wx =
  { Done = TSet.empty compare
    Stmts = []
    Decls = [] }

let private xcBody (rx: Rx) (wx: Wx) : Wx =
  let rec go blockId (wx: Wx) : Wx =
    if wx.Done |> TSet.contains blockId then
      wx
    else
      let blockDef = rx.BodyDef.Blocks |> mapFind blockId

      let wx =
        { wx with Done = wx.Done |> TSet.add blockId }

      // let wx = xcBlock blockId rx wx

      wx
      |> forList go (xTerminatorToSuccessors blockDef.Terminator)

  go rx.BodyDef.EntryBlockId wx

// ===============================================

let private locToDoc (loc: Loc) : DocId =
  let (Loc (doc, _, _)) = loc
  doc

let private splitByDoc (program: XProgram) : (DocId * (XBodyId * XBodyDef) list) list =
  program.Bodies
  |> TMap.fold
       (fun map bodyId (bodyDef: XBodyDef) ->
         let doc = locToDoc bodyDef.Loc
         map |> Multimap.add doc (bodyId, bodyDef))
       (TMap.empty compare)
  |> TMap.toList

let xirToCir (trace: TraceFun) (program: XProgram) : (DocId * CDecl list) list =
  program
  |> splitByDoc
  |> List.map (fun (doc, bodiesRev) ->
    let wx = newWx ()

    let wx =
      bodiesRev
      |> List.rev
      |> List.fold
           (fun wx (_bodyId, bodyDef) ->
             let rx = newRx trace bodyDef
             xcBody rx wx)
           wx

    doc, List.rev wx.Decls)
