module rec ModuleRecTy.Program

// Use of type reference defined later.
type SynonymB = SynonymA

type UnionB = | T of UnionA list

// Mutually recursive types.
// FIXME: can't compile due to stack overflow.
// type RecB = | T of RecA list
// type RecA = | T of RecB list

let main _ =
  let _: SynonymB = 0
  let _: UnionB = UnionB.T [UnionA.T]

  match UnionX.VariantY with
  | VariantX -> // Is a variant pattern rather than variable
    assert false
  | _ ->
    ()

  0

type SynonymA = int

type UnionA = | T

type UnionX = | VariantX | VariantY
