module rec MiloneCore.String

// NOTE: Exponentiation by squaring is fast enough, but we should use StringBuilder once available
//       since just using mutable buffer is ~5x faster.

let init (count: int) (f: int -> string) : string =
  assert (count >= 0)

  let rec stringInitAux l r =
    assert (l < r)

    if r - l = 1 then
      f l
    else
      let m = l + (r - l) / 2
      stringInitAux l m + stringInitAux m r

  match count with
  | 0 -> ""
  | 1 -> f 0
  | _ -> stringInitAux 0 count

let replicate (count: int) (s: string) : string =
  assert (count >= 0)

  // n times `s`
  let rec stringReplicateAux n =
    assert (n >= 1)

    if n = 1 then
      s
    else
      let t = stringReplicateAux (n / 2)
      if n % 2 = 0 then t + t else t + t + s

  if count = 0 then
    ""
  else
    stringReplicateAux count

let length (s: string) : int = s.Length
