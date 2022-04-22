namespace Std

module StdError =
  type Never = private | Never

  let never Never = failwith "never"

module Vector =
  type Vector<'T> = private | Vector

  module Vector =
    let alloc (_capacity: int) = Vector
    let dispose Vector = ()
    let length (v: Vector<'T>) = 0, v
    let forceGet (_index: int) (v: Vector<'T>) : 'T * Vector<'T> = failwith "", v
    let forceSet (_index: int) (_item: 'T) (v: Vector<'T>) = v
    let push (_item: 'T) (v: Vector<'T>) = v
    let ofList (_xs: 'T list) : Vector<'T> = Vector

module IO =
  type IO = internal | IO

  module IO =
    let exec action =
      let (IO) = action IO
      exit 0

namespace Competitive

open Std.IO

module Scan =
  let scanInt IO = 0, IO
  let scanList _scanner _len IO = [], IO
