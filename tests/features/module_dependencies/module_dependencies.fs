module rec module_dependencies.Program

// Module dependencies are resolved transitively.

open module_dependencies.second
open module_dependencies.third

let main _ = second () + third ()
