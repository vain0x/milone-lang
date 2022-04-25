namespace Std

module Block =
  type Block<'T> = private | Block

  module Block =
    let init (_len: int) (_f: int -> 'T) : Block<'T> = Block
    let replicate (_count: int) (_item: 'T) : Block<'T> = Block
    let length (_block: Block<_>) = 0
    // let forceGet (_index: int) (v: Vector<'T>) : 'T * Vector<'T> = failwith "", v
    // let forceSet (_index: int) (_item: 'T) (v: Vector<'T>) = v
    let tryItem (_index: int) (_block: Block<'T>) : 'T option = None
    let ofList (_xs: 'T list) : Block<'T> = Block

module StdError =
  let unreachable () = failwith ""

  type Never = private | Never

  let never Never = failwith "never"

module Vector =
  open Block

  type Vector<'T> = private | Vector

  module Vector =
    let alloc (_capacity: int) = Vector
    let replicate (_count: int) (_item: 'T) : Vector<'T> = failwith ""
    let dispose Vector = ()
    let length (v: Vector<'T>) = 0, v
    let forceGet (_index: int) (v: Vector<'T>) : 'T * Vector<'T> = failwith "", v
    let forceSet (_index: int) (_item: 'T) (v: Vector<'T>) = v
    let push (_item: 'T) (v: Vector<'T>) = v
    let ofList (_xs: 'T list) : Vector<'T> = Vector
    let toList (v: Vector<'T>) : 'T list * Vector<'T> = [], v
    let ofBlock (_: Block<'T>) : Vector<'T> = Vector
    let toBlock (_: Vector<'T>) : Block<'T> * Vector<'T> = failwith ""

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
