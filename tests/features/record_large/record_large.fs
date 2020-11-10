module rec record_large.Program

type GitCommitOptions =
  { All: bool
    Patch: bool
    ReuseMessage: string option
    ReeditMessage: string option
    Fixup: string option }
// and more...

let defaultOptions (): GitCommitOptions =
  { All = false
    Patch = false
    ReuseMessage = None
    ReeditMessage = None
    Fixup = None }

let main _ =
  let _options = defaultOptions ()

  0
