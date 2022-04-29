module MiloneShared.UtilSymbol

open System
open System.Collections.Generic

// Locks following fields.
let private sLocker = obj ()

let mutable private sLastId = 0
let private sMap = Dictionary<string, int>()
let private sData = Array.zeroCreate 4000

let private symbolIntern (name: string) =
  let name = String.Intern(name)

  lock sLocker (fun () ->
    match sMap.TryGetValue(name) with
    | true, id -> id

    | false, _ ->
      sLastId <- sLastId + 1
      let id = sLastId
      sData.[id] <- name
      sMap.Add(name, id)
      id)

let private symbolToString (id: int) =
  lock sLocker (fun () ->
    assert (uint id <= uint sLastId)
    sData.[id])

[<Struct; NoEquality; NoComparison>]
type Symbol =
  private
  | Symbol of int
  member private this.Value =
    let (Symbol n) = this
    n

  override this.ToString() =
    let (Symbol n) = this
    symbolToString n

module Symbol =
  let intern (s: string) = Symbol(symbolIntern s)
  let equals (Symbol l) (Symbol r) = l = r
  let compare (Symbol l) (Symbol r) = compare l r
  let toString (Symbol n) : string = symbolToString n
