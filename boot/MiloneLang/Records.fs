/// ## Records
///
/// Generated by scripts/RecordGen from `Records.yml`.
/// Run `./records` to regenerate.
///
/// Defines some types as synonym of tuple with getter/setter functions
/// because record types are unimplemented in milone-lang.
module rec MiloneLang.Records

open MiloneLang.Types

type ScopeCtx =
  | ScopeCtx
    of Serial
      * AssocMap<Serial, Ident>
      * AssocMap<VarSerial, VarDef>
      * AssocMap<VarSerial, LetDepth>
      * AssocMap<TySerial, TyDef>
      * AssocMap<TySerial, LetDepth>
      * ScopeSerial
      * Scope
      * LetDepth

let scopeCtxGetSerial (ScopeCtx (serial, _, _, _, _, _, _, _, _)) =
  serial

let scopeCtxGetNameMap (ScopeCtx (_, nameMap, _, _, _, _, _, _, _)) =
  nameMap

let scopeCtxGetVars (ScopeCtx (_, _, vars, _, _, _, _, _, _)) =
  vars

let scopeCtxGetVarDepths (ScopeCtx (_, _, _, varDepths, _, _, _, _, _)) =
  varDepths

let scopeCtxGetTys (ScopeCtx (_, _, _, _, tys, _, _, _, _)) =
  tys

let scopeCtxGetTyDepths (ScopeCtx (_, _, _, _, _, tyDepths, _, _, _)) =
  tyDepths

let scopeCtxGetLocalSerial (ScopeCtx (_, _, _, _, _, _, localSerial, _, _)) =
  localSerial

let scopeCtxGetLocal (ScopeCtx (_, _, _, _, _, _, _, local, _)) =
  local

let scopeCtxGetLetDepth (ScopeCtx (_, _, _, _, _, _, _, _, letDepth)) =
  letDepth

let scopeCtxWithSerial serial (ScopeCtx (_, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithNameMap nameMap (ScopeCtx (serial, _, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithVars vars (ScopeCtx (serial, nameMap, _, varDepths, tys, tyDepths, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithVarDepths varDepths (ScopeCtx (serial, nameMap, vars, _, tys, tyDepths, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithTys tys (ScopeCtx (serial, nameMap, vars, varDepths, _, tyDepths, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithTyDepths tyDepths (ScopeCtx (serial, nameMap, vars, varDepths, tys, _, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithLocalSerial localSerial (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, _, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithLocal local (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, _, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

let scopeCtxWithLetDepth letDepth (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, _)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, localSerial, local, letDepth)

type TyContext =
  | TyContext
    of Serial
      * AssocMap<TySerial, TyDef>
      * AssocMap<TySerial, LetDepth>

let tyContextGetSerial (TyContext (serial, _, _)) =
  serial

let tyContextGetTys (TyContext (_, tys, _)) =
  tys

let tyContextGetTyDepths (TyContext (_, _, tyDepths)) =
  tyDepths

let tyContextWithSerial serial (TyContext (_, tys, tyDepths)): TyContext =
  TyContext (serial, tys, tyDepths)

let tyContextWithTys tys (TyContext (serial, _, tyDepths)): TyContext =
  TyContext (serial, tys, tyDepths)

let tyContextWithTyDepths tyDepths (TyContext (serial, tys, _)): TyContext =
  TyContext (serial, tys, tyDepths)

type TyCtx =
  | TyCtx
    of Serial
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * AssocMap<TySerial, LetDepth>
      * LetDepth
      * (Trait * Loc) list
      * (Log * Loc) list

let tyCtxGetSerial (TyCtx (serial, _, _, _, _, _, _)) =
  serial

let tyCtxGetVars (TyCtx (_, vars, _, _, _, _, _)) =
  vars

let tyCtxGetTys (TyCtx (_, _, tys, _, _, _, _)) =
  tys

let tyCtxGetTyDepths (TyCtx (_, _, _, tyDepths, _, _, _)) =
  tyDepths

let tyCtxGetLetDepth (TyCtx (_, _, _, _, letDepth, _, _)) =
  letDepth

let tyCtxGetTraitBounds (TyCtx (_, _, _, _, _, traitBounds, _)) =
  traitBounds

let tyCtxGetLogs (TyCtx (_, _, _, _, _, _, logs)) =
  logs

let tyCtxWithSerial serial (TyCtx (_, vars, tys, tyDepths, letDepth, traitBounds, logs)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

let tyCtxWithVars vars (TyCtx (serial, _, tys, tyDepths, letDepth, traitBounds, logs)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

let tyCtxWithTys tys (TyCtx (serial, vars, _, tyDepths, letDepth, traitBounds, logs)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

let tyCtxWithTyDepths tyDepths (TyCtx (serial, vars, tys, _, letDepth, traitBounds, logs)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

let tyCtxWithLetDepth letDepth (TyCtx (serial, vars, tys, tyDepths, _, traitBounds, logs)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

let tyCtxWithTraitBounds traitBounds (TyCtx (serial, vars, tys, tyDepths, letDepth, _, logs)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)

let tyCtxWithLogs logs (TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, _)): TyCtx =
  TyCtx (serial, vars, tys, tyDepths, letDepth, traitBounds, logs)
