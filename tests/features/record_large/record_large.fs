module rec record_large.Program

// An example of large record type.

type GitCommitOptions =
  { All: bool
    Patch: bool
    ReuseMessage: string option
    ReeditMessage: string option
    Fixup: string option
    Squash: string option
    ResetAuthor: bool }
// and more...

let defaultOptions () : GitCommitOptions =
  { All = false
    Patch = false
    ReuseMessage = None
    ReeditMessage = None
    Fixup = None
    Squash = None
    ResetAuthor = false }

let main _ =
  let _options = defaultOptions ()

  0
