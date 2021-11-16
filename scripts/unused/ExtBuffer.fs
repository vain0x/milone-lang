module rec CmdHttpServer.ExtBuffer

type Span = __nativeType<``struct Span``>

type SpanMut = __nativeType<``struct SpanMut``>

type Buffer = __nativeType<``struct Buffer``>

module Span =
  let take (len: unativeint) (itemSize: unativeint) (span: Span) : Span =
    __nativeFun ("span_take", span, len, itemSize)

module SpanMut =
  let asConst (span: SpanMut) : Span = __nativeFun ("span_mut_as_const", span)

module Buffer =
  let create (cap: unativeint) (itemSize: unativeint) : Buffer =
    __nativeFun ("buffer_new", cap, itemSize)

  let zeroCreate (len: unativeint) (itemSize: unativeint) : Buffer =
    __nativeFun ("buffer_new_uninit", len, len, itemSize)

  let append (src: Span) (itemSize: unativeint) (buffer: Buffer) : Buffer =
    __nativeFun ("buffer_append_nonmut", buffer, src, itemSize)

  let sliceMut (start: unativeint) (endIndex: unativeint) (itemSize: unativeint) (buffer: Buffer) : SpanMut =
    __nativeFun ("buffer_slice_mut", buffer, start, endIndex, itemSize)

  let asString (buffer: Buffer) : string =
    __nativeFun ("buffer_as_string", buffer)
