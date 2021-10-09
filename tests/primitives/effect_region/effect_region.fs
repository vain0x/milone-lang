module rec effect_region.Program

let doAction () =
  __inRegion
    (fun () ->
      let rec go acc i =
        if i >= 0 then
          acc
        else
          go (i :: acc) (i + 1)

      let result = go [] 0
      0)

let main _ =
  let _ = doAction ()
  0
