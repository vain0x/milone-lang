module rec Std.StdLoopBase

type private Folder<'S, 'T> = 'S -> 'T -> bool * 'S
type private Loop<'S, 'T> = Folder<'S, Folder<'S, 'T>>

let shareLoop (xs: Loop<obj, 'T>) : Loop<'S, 'T> =
  fun (state: 'S) folder ->
    let ok, state =
      xs (box (state: 'S)) (fun state (item: 'T) ->
        let ok, state = folder (unbox state: 'S) item
        ok, box (state: 'S))

    ok, (unbox state: 'S)
