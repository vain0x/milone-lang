module rec MiloneStd.StdOpts

module S = MiloneStd.StdString

type CliOptionKind =
  | Flag
  | Prop of defaultValue: string option
  | List

type CliOption =
  { Long: string option
    Short: char option
    Kind: CliOptionKind
    Description: string }

type CliOptsSchema =
  { SkipFirst: bool
    Options: CliOption list }

type CliOptionName =
  | Long of string
  | Short of char
  | LongShort of string * char

module OptsCore =
  [<RequireQualifiedAccess; NoEquality; NoComparison>]
  type PropName =
    | Long of string
    | Short of char

  [<RequireQualifiedAccess; NoEquality; NoComparison>]
  type Msg =
    | Binding of PropName * string option
    | Positional of string
    | NoValueError of PropName
    | InvalidValueError of PropName * string

  [<RequireQualifiedAccess; NoEquality; NoComparison>]
  type Result =
    | Ok
    | NoValueError of PropName
    | RedundantValueError of PropName * string

  /// Gets whether a string can be used as parameter of option.
  /// It can't be a value if it starts with a '-', except for "-" and "-=".
  let private isValueArg (arg: string) =
    not (arg.Length >= 1 && arg.[0] = '-')
    || arg.Length = 1
    || arg.[2] = '='

  let run (args: string list) (init: 'S) (hasParam: PropName -> 'S -> bool) (update: Msg -> 'S -> 'S) : 'S * Result =
    let addPositional (state: 'S) value = update (Msg.Positional value) state

    let addPositionalList (state: 'S) args = args |> List.fold addPositional state

    let addBinding (state: 'S) name valueOpt =
      update (Msg.Binding(name, valueOpt)) state

    // Tries to take next argument as value of option.
    let take args =
      match args with
      | [] -> None, []
      | "--" :: value :: args -> Some value, "--" :: args
      | value :: args when isValueArg value -> Some value, args
      | _ -> None, args

    let addWithValueOpt (state: 'S) name valueOpt args : 'S * string list * Result =
      match hasParam name state, valueOpt with
      | true, Some _
      | false, None -> addBinding state name valueOpt, args, Result.Ok

      | false, Some value -> state, args, Result.RedundantValueError(name, value)

      | true, None ->
          let valueOpt, args = take args

          match valueOpt with
          | Some _ -> addBinding state name valueOpt, args, Result.Ok
          | None -> state, args, Result.NoValueError name

    let rec go args (state: 'S) : 'S * Result =
      match args with
      | [] -> state, Result.Ok

      | "--" :: args -> args |> List.fold addPositional state, Result.Ok

      // Long option.
      | arg :: args when S.startsWith "--" arg ->
          let arg = arg.[2..arg.Length - 1]

          let name, valueOpt =
            match S.findIndex "=" arg with
            | None -> arg, None
            | Some i -> arg.[0..i - 1], Some arg.[i + 1..arg.Length - 1]

          let state, args, result =
            addWithValueOpt state (PropName.Long name) valueOpt args

          match result with
          | Result.Ok -> go args state
          | _ -> state, result

      // Short option.
      | arg :: args when not (isValueArg arg) ->
          let arg = arg.[1..arg.Length - 1]

          let flags, last, valueOpt =
            match S.findIndex "=" arg with
            | Some i -> arg.[0..i - 2], arg.[i - 1], Some arg.[i + 1..arg.Length - 1]
            | None -> arg.[0..arg.Length - 2], arg.[arg.Length - 1], None

          let state =
            let rec gogo (i: int) (state: 'S) : 'S =
              if i = flags.Length then
                state
              else
                let name = PropName.Short flags.[i]

                if hasParam name state then
                  update (Msg.NoValueError name) state
                else
                  addBinding state name None |> gogo (i + 1)

            gogo 0 state

          let state, args, result =
            addWithValueOpt state (PropName.Short last) valueOpt args

          match result with
          | Result.Ok -> go args state
          | _ -> state, result

      | value :: args -> addPositional state value |> go args

    go args init
