module rec std_opts.Program

module OC = MiloneStd.StdOptsCore
module Opts = MiloneStd.StdOpts
module M = MiloneStd.StdMap
module S = MiloneStd.StdString

let format (s: string) (args: string list) =
  let _, s =
    args
    |> List.fold
         (fun (i, s) arg ->
           let s =
             s |> S.replace ("{" + string i + "}") arg

           i + 1, s)
         (0, s)

  s

let parseForTest (args: string list) (hasParam: string -> bool) : string =
  let ofName name =
    match name with
    | OC.PropName.Long name -> format "long `{0}`" [ name ]
    | OC.PropName.Short name -> format "short `{0}`" [ string name ]

  let myUpdate msg acc =
    match msg with
    | OC.Msg.Binding (name, None) -> format "flag {0}" [ ofName name ] :: acc

    | OC.Msg.Binding (name, Some value) ->
        format "binding {0} = `{1}`" [ ofName name; value ]
        :: acc

    | OC.Msg.Positional value -> format "pos `{0}`" [ value ] :: acc

  let myHasParam name (_: string list) =
    match name with
    | OC.PropName.Long name -> hasParam name
    | OC.PropName.Short name -> hasParam (string name)

  let acc, result = OC.run args [] myHasParam myUpdate

  let acc =
    match result with
    | OC.Result.Ok -> acc

    | OC.Result.NoValueError name ->
        format "error (no-value) {0}" [ ofName name ]
        :: acc

    | OC.Result.RedundantValueError (name, value) ->
        format "error (invalid-value) {0} = `{1}`" [ ofName name; value ]
        :: acc

  acc |> List.rev |> S.concat "; "

let testCore () =
  assert (format "" [] = "")
  assert (format "{0} + {0} = {1}" [ "1"; "2" ] = "1 + 1 = 2")

  let noParam = fun (_: string) -> false

  // Empty.
  assert (parseForTest [] noParam = "")

  // Short flag.
  assert (parseForTest [ "-h" ] noParam = "flag short `h`")

  // Long flag.
  assert (parseForTest [ "--help" ] noParam = "flag long `help`")

  // Composite flags.
  assert (parseForTest [ "-abc" ] noParam = "flag short `a`; flag short `b`; flag short `c`")

  // Positional.
  assert (parseForTest [ "foo" ] noParam = "pos `foo`")

  // Short bindings.
  let hasParam =
    fun (name: string) -> name = "n" || S.startsWith "set-" name

  assert (parseForTest [ "-n"; "10" ] hasParam = "binding short `n` = `10`")

  // Short binding with '='.
  assert (parseForTest [ "-n=-1" ] hasParam = "binding short `n` = `-1`")

  // Short flags and binding.
  assert (parseForTest [ "-mn"; "1" ] hasParam = "flag short `m`; binding short `n` = `1`")
  assert (parseForTest [ "-mn=1" ] hasParam = "flag short `m`; binding short `n` = `1`")

  // Long bindings.
  assert (parseForTest [ "--set-name"; "john" ] hasParam = "binding long `set-name` = `john`")
  assert (parseForTest [ "--set-name=john-doe" ] hasParam = "binding long `set-name` = `john-doe`")

  // Separator.
  assert (parseForTest [ "--" ] noParam = "")
  assert (parseForTest [ "--"; "--help" ] noParam = "pos `--help`")

  // Edges.
  assert (parseForTest [ "-"; "-=" ] noParam = "pos `-`; pos `-=`")

  // Error.
  assert (parseForTest [ "-n" ] hasParam = "error (no-value) short `n`")
  assert (parseForTest [ "-n"; "--" ] hasParam = "error (no-value) short `n`")
  assert (parseForTest [ "-x=foo"; "-" ] hasParam = "error (invalid-value) short `x` = `foo`")

let testParseOpts () =
  let def = [ "help"; "*user"; "?level" ]

  let display (opts: Opts.Opts) =
    let s =
      opts.Flags
      |> List.fold (fun s name -> name :: s) []

    let s =
      opts.Bindings
      |> List.fold (fun s (name, value) -> format "{0}=`{1}`" [ name; value ] :: s) s

    let s =
      opts.Positional
      |> List.fold (fun s value -> format "`{0}`" [ value ] :: s) s

    let s =
      match opts.Error with
      | Some error -> "error " + error :: s
      | None -> s

    s |> List.rev |> S.concat "; "

  assert (Opts.parseOpts
            def
            [ "--user"
              "john"
              "foOC.txt"
              "--level=0"
              "bar.txt" ]
          |> display = "level=`0`; user=`john`; `bar.txt`; `foOC.txt`")

let main _ =
  testCore ()
  testParseOpts ()
  0
