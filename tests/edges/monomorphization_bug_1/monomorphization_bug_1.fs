module rec monomorphization_bug_1.Program

type private Box<'T> = Box of 'T

let private dup (Box x) : Box<_ * _> = Box(x, x)

let private bug (b: Box<string>) : Box<string * string> = dup b

let main _ =
  let (Box (x1, x2)) = bug (Box "a")

  printfn "x1 = '%s'" x1
  printfn "x2 = '%s'" x2
  0
