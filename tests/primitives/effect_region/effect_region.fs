module rec effect_region.Program

open Std.Region

let private testRegionRun () =
  Region.run (fun () ->
    let rec go acc i =
      if i >= 0 then
        acc
      else
        go (i :: acc) (i + 1)

    let result = go [] 0
    0)
  |> ignore

let private staticVars () =
  __nativeDecl
    """
      static char s_mark[64];
      static int s_index;
    """

let private testRegionDefer () =
  let mark (i: int) =
    __nativeStmt (
      """
        s_mark[s_index++] = '0' + {0};
      """,
      i
    )

  Region.run (fun () ->
    mark 1
    Region.defer (fun () -> mark 2)
    mark 3

    Region.run (fun () ->
      mark 4
      Region.defer (fun () -> mark 5)
      mark 6
      0)
    |> ignore

    Region.run (fun () ->
      Region.defer (fun () -> mark 7)
      0)
    |> ignore

    Region.defer (fun () -> mark 8)
    mark 9
    0)
  |> ignore

  let s: string =
    __nativeExpr "string_of_raw_parts(s_mark, s_index)"

  assert (s = "134657982")

let main _ =
  testRegionRun ()
  testRegionDefer ()
  0
