module rec vis_private_err.Program

// Private definitions should not be visible to outside of module.

open vis_private_err.vis_private_sub

let main _ =
  vis_private_sub.privateFun ()
  0
