module rec generalize_bug.Program

// Repro. Issue about type inference and forward use of mutually recursive function.

// type Pat =
//   | Pat
//   | OtherPat

// let private anotherFun pat = inferPat pat // Here inferPat has provisional type 'a and (in previous implementation) 'a is generalized and levels downs to 10^9.

// // Type should be `Pat list -> Pat list` but was inferred to `'a list -> Pat list`.
// let private doInferPats pats =
//   let rec go acc pats =
//     match pats with
//     | [] -> acc

//     | pat :: pats ->
//       let pat = inferPat pat // inferPat: 'b -> 'c; Both 'b and 'c are bound to Pat later. Since inferPat is defined at level 1, 'c should be level 1, but didn't, because level of 'a (provisional type of inferPat) is at 10^9, written as above.
//       go (pat :: acc) pats

//   // go is generalized for some reason, go is instantiated here 'b1 -> 'c1. That fresh meta type remains as generic until the end of typing. Not substituted even after 'b is bound to Pat in inferPat. Therefore it degenerates to unit.
//   go [] pats

// // Pat -> Pat
// let inferPat pat : Pat = pat

// let main _ =
//   let _ = doInferPats [ Pat ]
//   // ^ In generated code, the type of _ is unit list for some reason.

//   0
