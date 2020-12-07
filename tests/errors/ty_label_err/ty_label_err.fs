module rec ty_label_err.Program

// Labeled types can be used inside of payload type.

type U = V of (label: int)

let main _ = 0
