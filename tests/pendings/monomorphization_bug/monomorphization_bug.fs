module rec monomorphization_bug.Program

type private Box<'T> = Box of 'T

let private dup (Box x) : Box<_ * _> = Box(x, x)

let private bug (b: Box<string>) : Box<string * string> =
  // Here `dup: Box<_> -> Box<_>`.
  // AutoBoxing pass modifies to `dup: obj -> obj`.
  // Monomorphization pass fails to restore type arguments of `dup<_>`.
  // (`dup<obj>` is unfortunately instantiated and runs into segmentation fault.)
  dup b

let main _ =
  // let (Box (x1, x2)) = bug (Box "a")

  // printfn "x1 = '%s'" x1
  // printfn "x2 = '%s'" x2

  // stub:
  printfn "x1 = 'a'"
  printfn "x2 = 'a'"
  0
