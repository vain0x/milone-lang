module rec MiloneStd.StdOpts

module OptsCore = MiloneStd.StdOptsCore
module S = MiloneStd.StdString
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

type private Kind =
  | Flag
  | Required
  | Optional

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Opts =
  { Positional: string list
    Flags: string list
    Bindings: (string * string) list
    Error: string option }

let private emptyOpts : Opts =
  { Positional = []
    Flags = []
    Bindings = []
    Error = None }

/// Easy way to parse command line arguments.
///
/// def: List of valid parameter names in the form of:
///
/// - `name`: flag
/// - `*name`: required
/// - `?name`: optional
let parseOpts (def: string list) (args: string list) : Opts =
  let nameToString name =
    match name with
    | OptsCore.PropName.Long name -> name
    | OptsCore.PropName.Short c -> string c

  let defMap, missed =
    def
    |> List.fold
         (fun (defMap, missed) def ->
           let name, kind =
             if S.startsWith "*" def then
               S.skip 1 def, Required
             else if S.startsWith "?" def then
               S.skip 1 def, Optional
             else
               def, Flag

           let defMap = defMap |> TMap.add name kind

           let missed =
             match kind with
             | Required -> missed |> TSet.add name
             | _ -> missed

           defMap, missed)
         (TMap.empty compare, TSet.empty compare)

  let hasParam name (_: Opts, _: TSet.TreeSet<string>, _: string list) =
    match defMap |> TMap.tryFind (nameToString name) with
    | Some Optional
    | Some Required -> true

    | _ -> false

  let update msg (opts: Opts, missed, redundant) =
    match msg with
    | OptsCore.Msg.Binding (name, valueOpt) ->
        let name = nameToString name

        match TMap.tryFind name defMap, valueOpt with
        | None, _ -> opts, missed, name :: redundant

        | Some Flag, _ -> { opts with Flags = name :: opts.Flags }, missed, redundant

        | Some Optional, Some value ->
            { opts with
                Bindings = (name, value) :: opts.Bindings },
            missed,
            redundant

        | Some Required, Some value ->
            let _, missed = missed |> TSet.remove name

            { opts with
                Bindings = (name, value) :: opts.Bindings },
            missed,
            redundant

        | _ ->
            assert false // unreachable
            exit 1

    | OptsCore.Msg.Positional value ->
        { opts with
            Positional = value :: opts.Positional },
        missed,
        redundant

  let (opts, missed, redundant), result =
    OptsCore.run args (emptyOpts, missed, []) hasParam update

  let error =
    match result with
    | OptsCore.Result.Ok ->
        let missedError missed =
          "Missed options: " + S.concat ", " missed + "."

        let redundantError redundant =
          "Redundant flags: "
          + S.concat ", " redundant
          + "."

        match TSet.toList missed, redundant with
        | [], [] -> None
        | missed, [] -> Some(missedError missed)
        | [], redundant -> Some(redundantError redundant)
        | missed, redundant ->
            Some(
              missedError missed
              + " "
              + redundantError redundant
            )

    | OptsCore.Result.NoValueError name -> Some("Specify value of option: " + nameToString name)

    | OptsCore.Result.RedundantValueError (name, _) ->
        Some(
          "Don't specify value for flag: "
          + nameToString name
        )

  { opts with Error = error }
