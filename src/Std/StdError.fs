module rec Std.StdError

let __dump (info: 'T) : string = sprintf "%A" info

let __writeError (s: string) : unit = eprintf "%s" s

let __writeErrorLine (s: string) : unit = __writeError (s + "\n")

/// Only for debugging. Prints to stderr.
let __trace (msg: string) : unit = eprintf "%s" (msg + "\n")

/// Only for debugging. Adds context to error info if thrown.
let __context (info: 'T) (action: unit -> 'A) : 'A =
  try
    action ()
  with
  | ex -> raise (exn (sprintf "%A" info, ex))

// -----------------------------------------------
// Exceptions
// -----------------------------------------------

/// Never executed.
let unreachable context = failwithf "NEVER: %A" context

/// Not implemented.
let todo context = failwithf "Not implemented: %A" context

// -----------------------------------------------
// Never
// -----------------------------------------------

/// Placeholder of result type of diverging function.
type Never = private | Never

/// Never happens.
let never Never : 'A = unreachable ()
