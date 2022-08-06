module rec record_generic.Program

module S = Std.StdString

/// Just wraps a value.
type GenericWrapper<'T> = { GenericField: 'T }

let private gwWrap value : GenericWrapper<_> = { GenericField = value }

let private gwUnwrap (r: GenericWrapper<_>) = r.GenericField

let private gwMap f (r: GenericWrapper<_>) : GenericWrapper<_> = { GenericField = f r.GenericField }

let private testGenericWrapper () =
  let wrappedInt = gwWrap 42
  assert (gwUnwrap wrappedInt = 42)

  let wrappedString = gwWrap "john"
  assert (gwUnwrap wrappedString = "john")

  assert ((gwMap string wrappedInt).GenericField = "42")

/// Recursive generic record.
type private Node<'T> = { Value: 'T; Children: Node<'T> list }

let private newNode value children : Node<_> = { Value = value; Children = children }

let private nodePrint toString node =
  let rec go (node: Node<_>) =
    let value = toString node.Value

    if List.isEmpty node.Children then
      value
    else
      value
      + "("
      + (node.Children |> List.map go |> S.concat " ")
      + ")"

  go node

let private testRecusive () =
  let node =
    newNode
      "add"
      [ newNode "f" [ newNode "x" [] ]
        newNode "y" [] ]

  assert (nodePrint id node = "add(f(x) y)")

  // Try update.
  let other = { node with Value = "mul" }

  assert (nodePrint id other = "mul(f(x) y)")

let main _ =
  testGenericWrapper ()
  testRecusive ()
  0
