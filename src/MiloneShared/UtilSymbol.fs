module MiloneShared.UtilSymbol

open System
open System.Collections.Generic
open System.Threading

let private tMap =
  let capacity = 4000
  new ThreadLocal<_>(fun () -> Dictionary<string, int>(capacity), ResizeArray<string>(capacity))

let private symbolIntern (name: string) =
  let map, entries = tMap.Value
  let name = String.Intern(name)

  match map.TryGetValue(name) with
  | true, id -> id

  | false, _ ->
    let id = entries.Count
    entries.Add(name)
    map.Add(name, id)
    id

let private symbolToString (id: int) =
  let _, entries = tMap.Value
  entries.[id]

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
