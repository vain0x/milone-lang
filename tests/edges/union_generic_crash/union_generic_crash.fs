module rec union_generic_crash.Program

// Repro. Generic union caused a compile to crash
//        while computing mangled name.

type private GU<'T> = GU of GU<'T> option

let main _ =
  let _: GU<int> = GU None
  0
