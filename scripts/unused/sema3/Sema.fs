module rec MiloneLang.Sema

open MiloneLang.Syntax

module M = MiloneStd.StdMap

type ProjectName = string

type Ns =
  | ValueNs
  | TyNs
  | ModuleNs

type Symbol = Symbol of id: int * raw: string

type Scope =
  { ValueEnv: M.TreeMap<string * Ns, Symbol>
    TyEnv: M.TreeMap<string * Ns, Symbol>
    ModuleEnv: M.TreeMap<string * Ns, Symbol list>
    Range: Pos * Pos }

type SymbolDb =
  { Modules: M.TreeMap<Symbol, Scope list> }

type SemaDb = { Projects: M.TreeMap<string, string> }
