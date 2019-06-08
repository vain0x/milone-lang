module rec modules_dep

open modules_dep.second
open modules_dep.third

let main _ =
  second () + third ()
