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
      * NameTree
      * NameTree
      * ScopeSerial
      * Scope
      * LetDepth

let scopeCtxGetSerial (ScopeCtx (serial, _, _, _, _, _, _, _, _, _, _)) =
  serial

let scopeCtxGetNameMap (ScopeCtx (_, nameMap, _, _, _, _, _, _, _, _, _)) =
  nameMap

let scopeCtxGetVars (ScopeCtx (_, _, vars, _, _, _, _, _, _, _, _)) =
  vars

let scopeCtxGetVarDepths (ScopeCtx (_, _, _, varDepths, _, _, _, _, _, _, _)) =
  varDepths

let scopeCtxGetTys (ScopeCtx (_, _, _, _, tys, _, _, _, _, _, _)) =
  tys

let scopeCtxGetTyDepths (ScopeCtx (_, _, _, _, _, tyDepths, _, _, _, _, _)) =
  tyDepths

let scopeCtxGetVarNs (ScopeCtx (_, _, _, _, _, _, varNs, _, _, _, _)) =
  varNs

let scopeCtxGetTyNs (ScopeCtx (_, _, _, _, _, _, _, tyNs, _, _, _)) =
  tyNs

let scopeCtxGetLocalSerial (ScopeCtx (_, _, _, _, _, _, _, _, localSerial, _, _)) =
  localSerial

let scopeCtxGetLocal (ScopeCtx (_, _, _, _, _, _, _, _, _, local, _)) =
  local

let scopeCtxGetLetDepth (ScopeCtx (_, _, _, _, _, _, _, _, _, _, letDepth)) =
  letDepth

let scopeCtxWithSerial serial (ScopeCtx (_, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithNameMap nameMap (ScopeCtx (serial, _, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithVars vars (ScopeCtx (serial, nameMap, _, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithVarDepths varDepths (ScopeCtx (serial, nameMap, vars, _, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithTys tys (ScopeCtx (serial, nameMap, vars, varDepths, _, tyDepths, varNs, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithTyDepths tyDepths (ScopeCtx (serial, nameMap, vars, varDepths, tys, _, varNs, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithVarNs varNs (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, _, tyNs, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithTyNs tyNs (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, _, localSerial, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithLocalSerial localSerial (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, _, local, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithLocal local (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, _, letDepth)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

let scopeCtxWithLetDepth letDepth (ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, _)): ScopeCtx =
  ScopeCtx (serial, nameMap, vars, varDepths, tys, tyDepths, varNs, tyNs, localSerial, local, letDepth)

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

type TyElaborationCtx =
  | TyElaborationCtx
    of AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * AssocMap<TySerial, (Ty * AssocMap<Ident, int * Ty>)>

let tyElaborationCtxGetVars (TyElaborationCtx (vars, _, _)) =
  vars

let tyElaborationCtxGetTys (TyElaborationCtx (_, tys, _)) =
  tys

let tyElaborationCtxGetRecordMap (TyElaborationCtx (_, _, recordMap)) =
  recordMap

let tyElaborationCtxWithVars vars (TyElaborationCtx (_, tys, recordMap)): TyElaborationCtx =
  TyElaborationCtx (vars, tys, recordMap)

let tyElaborationCtxWithTys tys (TyElaborationCtx (vars, _, recordMap)): TyElaborationCtx =
  TyElaborationCtx (vars, tys, recordMap)

let tyElaborationCtxWithRecordMap recordMap (TyElaborationCtx (vars, tys, _)): TyElaborationCtx =
  TyElaborationCtx (vars, tys, recordMap)

type KnownCtx =
  | KnownCtx
    of AssocSet<FunSerial>
      * AssocSet<VarSerial>
      * AssocSet<VarSerial>

let knownCtxGetKnown (KnownCtx (known, _, _)) =
  known

let knownCtxGetLocals (KnownCtx (_, locals, _)) =
  locals

let knownCtxGetRefs (KnownCtx (_, _, refs)) =
  refs

let knownCtxWithKnown known (KnownCtx (_, locals, refs)): KnownCtx =
  KnownCtx (known, locals, refs)

let knownCtxWithLocals locals (KnownCtx (known, _, refs)): KnownCtx =
  KnownCtx (known, locals, refs)

let knownCtxWithRefs refs (KnownCtx (known, locals, _)): KnownCtx =
  KnownCtx (known, locals, refs)

type CcCtx =
  | CcCtx
    of Serial
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * KnownCtx
      * AssocMap<FunSerial, KnownCtx>

let ccCtxGetSerial (CcCtx (serial, _, _, _, _)) =
  serial

let ccCtxGetVars (CcCtx (_, vars, _, _, _)) =
  vars

let ccCtxGetTys (CcCtx (_, _, tys, _, _)) =
  tys

let ccCtxGetCurrent (CcCtx (_, _, _, current, _)) =
  current

let ccCtxGetFuns (CcCtx (_, _, _, _, funs)) =
  funs

let ccCtxWithSerial serial (CcCtx (_, vars, tys, current, funs)): CcCtx =
  CcCtx (serial, vars, tys, current, funs)

let ccCtxWithVars vars (CcCtx (serial, _, tys, current, funs)): CcCtx =
  CcCtx (serial, vars, tys, current, funs)

let ccCtxWithTys tys (CcCtx (serial, vars, _, current, funs)): CcCtx =
  CcCtx (serial, vars, tys, current, funs)

let ccCtxWithCurrent current (CcCtx (serial, vars, tys, _, funs)): CcCtx =
  CcCtx (serial, vars, tys, current, funs)

let ccCtxWithFuns funs (CcCtx (serial, vars, tys, current, _)): CcCtx =
  CcCtx (serial, vars, tys, current, funs)

type EtaCtx =
  | EtaCtx
    of Serial
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>

let etaCtxGetSerial (EtaCtx (serial, _, _)) =
  serial

let etaCtxGetVars (EtaCtx (_, vars, _)) =
  vars

let etaCtxGetTys (EtaCtx (_, _, tys)) =
  tys

let etaCtxWithSerial serial (EtaCtx (_, vars, tys)): EtaCtx =
  EtaCtx (serial, vars, tys)

let etaCtxWithVars vars (EtaCtx (serial, _, tys)): EtaCtx =
  EtaCtx (serial, vars, tys)

let etaCtxWithTys tys (EtaCtx (serial, vars, _)): EtaCtx =
  EtaCtx (serial, vars, tys)

type TailRecCtx =
  | TailRecCtx
    of AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * FunSerial option
      * AssocSet<VarSerial>

let tailRecCtxGetVars (TailRecCtx (vars, _, _, _)) =
  vars

let tailRecCtxGetTys (TailRecCtx (_, tys, _, _)) =
  tys

let tailRecCtxGetCurrentFun (TailRecCtx (_, _, currentFun, _)) =
  currentFun

let tailRecCtxGetTailRecFuns (TailRecCtx (_, _, _, tailRecFuns)) =
  tailRecFuns

let tailRecCtxWithVars vars (TailRecCtx (_, tys, currentFun, tailRecFuns)): TailRecCtx =
  TailRecCtx (vars, tys, currentFun, tailRecFuns)

let tailRecCtxWithTys tys (TailRecCtx (vars, _, currentFun, tailRecFuns)): TailRecCtx =
  TailRecCtx (vars, tys, currentFun, tailRecFuns)

let tailRecCtxWithCurrentFun currentFun (TailRecCtx (vars, tys, _, tailRecFuns)): TailRecCtx =
  TailRecCtx (vars, tys, currentFun, tailRecFuns)

let tailRecCtxWithTailRecFuns tailRecFuns (TailRecCtx (vars, tys, currentFun, _)): TailRecCtx =
  TailRecCtx (vars, tys, currentFun, tailRecFuns)

type MonoCtx =
  | MonoCtx
    of Serial
      * (Log * Loc) list
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * AssocMap<TySerial, LetDepth>
      * AssocMap<FunSerial, Ty list>
      * AssocMap<FunSerial * Ty, FunSerial>
      * MonoMode
      * bool
      * int

let monoCtxGetSerial (MonoCtx (serial, _, _, _, _, _, _, _, _, _)) =
  serial

let monoCtxGetLogs (MonoCtx (_, logs, _, _, _, _, _, _, _, _)) =
  logs

let monoCtxGetVars (MonoCtx (_, _, vars, _, _, _, _, _, _, _)) =
  vars

let monoCtxGetTys (MonoCtx (_, _, _, tys, _, _, _, _, _, _)) =
  tys

let monoCtxGetTyDepths (MonoCtx (_, _, _, _, tyDepths, _, _, _, _, _)) =
  tyDepths

let monoCtxGetGenericFunUseSiteTys (MonoCtx (_, _, _, _, _, genericFunUseSiteTys, _, _, _, _)) =
  genericFunUseSiteTys

let monoCtxGetGenericFunMonoSerials (MonoCtx (_, _, _, _, _, _, genericFunMonoSerials, _, _, _)) =
  genericFunMonoSerials

let monoCtxGetMode (MonoCtx (_, _, _, _, _, _, _, mode, _, _)) =
  mode

let monoCtxGetSomethingHappened (MonoCtx (_, _, _, _, _, _, _, _, somethingHappened, _)) =
  somethingHappened

let monoCtxGetInfiniteLoopDetector (MonoCtx (_, _, _, _, _, _, _, _, _, infiniteLoopDetector)) =
  infiniteLoopDetector

let monoCtxWithSerial serial (MonoCtx (_, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithLogs logs (MonoCtx (serial, _, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithVars vars (MonoCtx (serial, logs, _, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithTys tys (MonoCtx (serial, logs, vars, _, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithTyDepths tyDepths (MonoCtx (serial, logs, vars, tys, _, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithGenericFunUseSiteTys genericFunUseSiteTys (MonoCtx (serial, logs, vars, tys, tyDepths, _, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithGenericFunMonoSerials genericFunMonoSerials (MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, _, mode, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithMode mode (MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, _, somethingHappened, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithSomethingHappened somethingHappened (MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, _, infiniteLoopDetector)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

let monoCtxWithInfiniteLoopDetector infiniteLoopDetector (MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, _)): MonoCtx =
  MonoCtx (serial, logs, vars, tys, tyDepths, genericFunUseSiteTys, genericFunMonoSerials, mode, somethingHappened, infiniteLoopDetector)

type KirGenCtx =
  | KirGenCtx
    of Serial
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * (Log * Loc) list
      * FunSerial option
      * KJointBinding list
      * KFunBinding list

let kirGenCtxGetSerial (KirGenCtx (serial, _, _, _, _, _, _)) =
  serial

let kirGenCtxGetVars (KirGenCtx (_, vars, _, _, _, _, _)) =
  vars

let kirGenCtxGetTys (KirGenCtx (_, _, tys, _, _, _, _)) =
  tys

let kirGenCtxGetLogs (KirGenCtx (_, _, _, logs, _, _, _)) =
  logs

let kirGenCtxGetMainFunSerial (KirGenCtx (_, _, _, _, mainFunSerial, _, _)) =
  mainFunSerial

let kirGenCtxGetJoints (KirGenCtx (_, _, _, _, _, joints, _)) =
  joints

let kirGenCtxGetFuns (KirGenCtx (_, _, _, _, _, _, funs)) =
  funs

let kirGenCtxWithSerial serial (KirGenCtx (_, vars, tys, logs, mainFunSerial, joints, funs)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

let kirGenCtxWithVars vars (KirGenCtx (serial, _, tys, logs, mainFunSerial, joints, funs)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

let kirGenCtxWithTys tys (KirGenCtx (serial, vars, _, logs, mainFunSerial, joints, funs)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

let kirGenCtxWithLogs logs (KirGenCtx (serial, vars, tys, _, mainFunSerial, joints, funs)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

let kirGenCtxWithMainFunSerial mainFunSerial (KirGenCtx (serial, vars, tys, logs, _, joints, funs)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

let kirGenCtxWithJoints joints (KirGenCtx (serial, vars, tys, logs, mainFunSerial, _, funs)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

let kirGenCtxWithFuns funs (KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, _)): KirGenCtx =
  KirGenCtx (serial, vars, tys, logs, mainFunSerial, joints, funs)

type KirPropagateCtx =
  | KirPropagateCtx
    of AssocMap<VarSerial, KVarDef>
      * AssocMap<VarSerial, int>

let kirPropagateCtxGetVarDefs (KirPropagateCtx (varDefs, _)) =
  varDefs

let kirPropagateCtxGetVarUses (KirPropagateCtx (_, varUses)) =
  varUses

let kirPropagateCtxWithVarDefs varDefs (KirPropagateCtx (_, varUses)): KirPropagateCtx =
  KirPropagateCtx (varDefs, varUses)

let kirPropagateCtxWithVarUses varUses (KirPropagateCtx (varDefs, _)): KirPropagateCtx =
  KirPropagateCtx (varDefs, varUses)

type KirToMirCtx =
  | KirToMirCtx
    of Serial
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * FunSerial option
      * Serial
      * AssocMap<JointSerial, Label * VarSerial list>
      * MStmt list list
      * int
      * MStmt list
      * (Log * Loc) list

let kirToMirCtxGetSerial (KirToMirCtx (serial, _, _, _, _, _, _, _, _, _)) =
  serial

let kirToMirCtxGetVars (KirToMirCtx (_, vars, _, _, _, _, _, _, _, _)) =
  vars

let kirToMirCtxGetTys (KirToMirCtx (_, _, tys, _, _, _, _, _, _, _)) =
  tys

let kirToMirCtxGetMainFunSerial (KirToMirCtx (_, _, _, mainFunSerial, _, _, _, _, _, _)) =
  mainFunSerial

let kirToMirCtxGetLabelSerial (KirToMirCtx (_, _, _, _, labelSerial, _, _, _, _, _)) =
  labelSerial

let kirToMirCtxGetJointMap (KirToMirCtx (_, _, _, _, _, jointMap, _, _, _, _)) =
  jointMap

let kirToMirCtxGetLabels (KirToMirCtx (_, _, _, _, _, _, labels, _, _, _)) =
  labels

let kirToMirCtxGetLabelCount (KirToMirCtx (_, _, _, _, _, _, _, labelCount, _, _)) =
  labelCount

let kirToMirCtxGetStmts (KirToMirCtx (_, _, _, _, _, _, _, _, stmts, _)) =
  stmts

let kirToMirCtxGetLogs (KirToMirCtx (_, _, _, _, _, _, _, _, _, logs)) =
  logs

let kirToMirCtxWithSerial serial (KirToMirCtx (_, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithVars vars (KirToMirCtx (serial, _, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithTys tys (KirToMirCtx (serial, vars, _, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithMainFunSerial mainFunSerial (KirToMirCtx (serial, vars, tys, _, labelSerial, jointMap, labels, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithLabelSerial labelSerial (KirToMirCtx (serial, vars, tys, mainFunSerial, _, jointMap, labels, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithJointMap jointMap (KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, _, labels, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithLabels labels (KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, _, labelCount, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithLabelCount labelCount (KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, _, stmts, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithStmts stmts (KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, _, logs)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

let kirToMirCtxWithLogs logs (KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, _)): KirToMirCtx =
  KirToMirCtx (serial, vars, tys, mainFunSerial, labelSerial, jointMap, labels, labelCount, stmts, logs)

type MirCtx =
  | MirCtx
    of Serial
      * AssocMap<VarSerial, VarDef>
      * AssocMap<TySerial, TyDef>
      * Serial
      * (Label * VarSerial list) option
      * MStmt list
      * (Log * Loc) list

let mirCtxGetSerial (MirCtx (serial, _, _, _, _, _, _)) =
  serial

let mirCtxGetVars (MirCtx (_, vars, _, _, _, _, _)) =
  vars

let mirCtxGetTys (MirCtx (_, _, tys, _, _, _, _)) =
  tys

let mirCtxGetLabelSerial (MirCtx (_, _, _, labelSerial, _, _, _)) =
  labelSerial

let mirCtxGetCurrentFun (MirCtx (_, _, _, _, currentFun, _, _)) =
  currentFun

let mirCtxGetStmts (MirCtx (_, _, _, _, _, stmts, _)) =
  stmts

let mirCtxGetLogs (MirCtx (_, _, _, _, _, _, logs)) =
  logs

let mirCtxWithSerial serial (MirCtx (_, vars, tys, labelSerial, currentFun, stmts, logs)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

let mirCtxWithVars vars (MirCtx (serial, _, tys, labelSerial, currentFun, stmts, logs)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

let mirCtxWithTys tys (MirCtx (serial, vars, _, labelSerial, currentFun, stmts, logs)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

let mirCtxWithLabelSerial labelSerial (MirCtx (serial, vars, tys, _, currentFun, stmts, logs)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

let mirCtxWithCurrentFun currentFun (MirCtx (serial, vars, tys, labelSerial, _, stmts, logs)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

let mirCtxWithStmts stmts (MirCtx (serial, vars, tys, labelSerial, currentFun, _, logs)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

let mirCtxWithLogs logs (MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, _)): MirCtx =
  MirCtx (serial, vars, tys, labelSerial, currentFun, stmts, logs)

type CirCtx =
  | CirCtx
    of AssocMap<VarSerial, VarDef>
      * AssocMap<VarSerial, Ident>
      * AssocMap<Ty, CTyInstance * CTy>
      * AssocMap<TySerial, TyDef>
      * AssocMap<Ty, Ident>
      * CStmt list
      * CDecl list
      * (Log * Loc) list

let cirCtxGetVars (CirCtx (vars, _, _, _, _, _, _, _)) =
  vars

let cirCtxGetVarUniqueNames (CirCtx (_, varUniqueNames, _, _, _, _, _, _)) =
  varUniqueNames

let cirCtxGetTyEnv (CirCtx (_, _, tyEnv, _, _, _, _, _)) =
  tyEnv

let cirCtxGetTys (CirCtx (_, _, _, tys, _, _, _, _)) =
  tys

let cirCtxGetTyUniqueNames (CirCtx (_, _, _, _, tyUniqueNames, _, _, _)) =
  tyUniqueNames

let cirCtxGetStmts (CirCtx (_, _, _, _, _, stmts, _, _)) =
  stmts

let cirCtxGetDecls (CirCtx (_, _, _, _, _, _, decls, _)) =
  decls

let cirCtxGetLogs (CirCtx (_, _, _, _, _, _, _, logs)) =
  logs

let cirCtxWithVars vars (CirCtx (_, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithVarUniqueNames varUniqueNames (CirCtx (vars, _, tyEnv, tys, tyUniqueNames, stmts, decls, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithTyEnv tyEnv (CirCtx (vars, varUniqueNames, _, tys, tyUniqueNames, stmts, decls, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithTys tys (CirCtx (vars, varUniqueNames, tyEnv, _, tyUniqueNames, stmts, decls, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithTyUniqueNames tyUniqueNames (CirCtx (vars, varUniqueNames, tyEnv, tys, _, stmts, decls, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithStmts stmts (CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, _, decls, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithDecls decls (CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, _, logs)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

let cirCtxWithLogs logs (CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, _)): CirCtx =
  CirCtx (vars, varUniqueNames, tyEnv, tys, tyUniqueNames, stmts, decls, logs)

type CliHost =
  | CliHost
    of string list
      * (unit -> Profiler)
      * (string -> Profiler -> unit)
      * (string -> string option)

let cliHostGetArgs (CliHost (args, _, _, _)) =
  args

let cliHostGetProfileInit (CliHost (_, profileInit, _, _)) =
  profileInit

let cliHostGetProfileLog (CliHost (_, _, profileLog, _)) =
  profileLog

let cliHostGetFileReadAllText (CliHost (_, _, _, fileReadAllText)) =
  fileReadAllText

let cliHostWithArgs args (CliHost (_, profileInit, profileLog, fileReadAllText)): CliHost =
  CliHost (args, profileInit, profileLog, fileReadAllText)

let cliHostWithProfileInit profileInit (CliHost (args, _, profileLog, fileReadAllText)): CliHost =
  CliHost (args, profileInit, profileLog, fileReadAllText)

let cliHostWithProfileLog profileLog (CliHost (args, profileInit, _, fileReadAllText)): CliHost =
  CliHost (args, profileInit, profileLog, fileReadAllText)

let cliHostWithFileReadAllText fileReadAllText (CliHost (args, profileInit, profileLog, _)): CliHost =
  CliHost (args, profileInit, profileLog, fileReadAllText)
