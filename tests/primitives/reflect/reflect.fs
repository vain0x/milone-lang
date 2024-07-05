module rec reflect.Program

// reflect<'T> object

let private unreachable () = failwith "unreachable"

let main _ =
  let reflectInt = reflect<int>
  let reflectString = reflect<string>

  let reflectTuple = reflect<int * string>

  match reflectTuple with
  | Reflect.Tuple argTys ->
    assert (List.length argTys = 2)

    match argTys with
    | [ Reflect.Int; Reflect.String ] -> ()
    | _ -> unreachable ()

  | _ -> unreachable ()

  0
