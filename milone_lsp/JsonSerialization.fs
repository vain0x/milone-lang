module MiloneLsp.JsonSerialization

open Utf8Json
open MiloneLsp.JsonValue

type private JsonValueFormatter() =
  interface IJsonFormatter<JsonValue> with
    override _.Serialize(writer: byref<JsonWriter>, value: JsonValue, formatterResolver: IJsonFormatterResolver) =
      match value with
      | JNull -> writer.WriteNull()

      | JNumber value ->
          formatterResolver
            .GetFormatter()
            .Serialize(&writer, value, formatterResolver)

      | JString value ->
          formatterResolver
            .GetFormatter()
            .Serialize(&writer, value, formatterResolver)

      | JBoolean value ->
          formatterResolver
            .GetFormatter()
            .Serialize(&writer, value, formatterResolver)

      | JArray array ->
          writer.WriteBeginArray()
          let mutable first = true

          for item in array do
            if first then
              first <- false
            else
              writer.WriteValueSeparator()

            formatterResolver
              .GetFormatter()
              .Serialize(&writer, item, formatterResolver)

          writer.WriteEndArray()

      | JObject map ->
          writer.WriteBeginObject()
          let mutable first = true

          for KeyValue (key, value) in map do
            if first then
              first <- false
            else
              writer.WriteValueSeparator()

            writer.WriteString(key)
            writer.WriteNameSeparator()

            formatterResolver
              .GetFormatter()
              .Serialize(&writer, value, formatterResolver)

          writer.WriteEndObject()

    override _.Deserialize(reader: byref<JsonReader>, formatterResolver: IJsonFormatterResolver) =
      match reader.GetCurrentJsonToken() with
      | JsonToken.Null ->
          reader.ReadNext()
          JNull

      | JsonToken.String -> reader.ReadString() |> JString

      | JsonToken.Number -> reader.ReadDouble() |> JNumber

      | JsonToken.True ->
          reader.ReadNext()
          JBoolean true

      | JsonToken.False ->
          reader.ReadNext()
          JBoolean false

      | JsonToken.BeginArray ->
          let mutable array = ResizeArray()

          // eprintfn "JsonValue de: begin array"
          reader.ReadNext() // Skip '['.

          let mutable running =
            reader.GetCurrentJsonToken() <> JsonToken.EndArray

          while running do
            let item =
              formatterResolver
                .GetFormatter<JsonValue>()
                .Deserialize(&reader, formatterResolver)

            array.Add(item)

            if reader.ReadIsValueSeparator() then
              // eprintfn "JsonValue de: array continue"
              () // Skip ',' and continue.
            else
              running <- false // Break.

          // eprintfn "JsonValue de: end array"
          reader.ReadIsEndArrayWithVerify() // Skip ']'.

          JArray(List.ofSeq array)

      | JsonToken.BeginObject ->
          let mutable array = ResizeArray()

          // eprintfn "JsonValue de: begin object"
          reader.ReadNext() // Skip '{'.

          let mutable running =
            reader.GetCurrentJsonToken()
            <> JsonToken.EndObject

          while running do
            let key = reader.ReadString()
            // eprintfn "JsonValue de: key = %s" key
            reader.ReadIsNameSeparatorWithVerify() // Skip ':'.
            // eprintfn "JsonValue de: ':'"

            let value =
              formatterResolver
                .GetFormatter<JsonValue>()
                .Deserialize(&reader, formatterResolver)

            // eprintfn "JsonValue de: value"

            array.Add((key, value))

            if reader.ReadIsValueSeparator() then
              // eprintfn "JsonValue de: object continue"
              () // Skip ',' and continue.
            else
              running <- false // Break.

          // eprintfn "JsonValue de: '}'"
          reader.ReadIsEndObjectWithVerify() // Skip '}'.

          JObject(Map.ofSeq array)

      | token -> failwithf "Invalid JSON input %A." token

let private jsonResolver: IJsonFormatterResolver =
  let formatters =
    [| JsonValueFormatter() :> IJsonFormatter |]

  let resolvers =
    [| Resolvers.StandardResolver.CamelCase |]

  Resolvers.DynamicCompositeResolver.Create(formatters, resolvers)

let jsonDisplay (value: JsonValue): string =
  JsonSerializer.PrettyPrint(JsonSerializer.Serialize(value, jsonResolver))

let jsonDeserializeBytes (json: byte []): JsonValue =
  JsonSerializer.Deserialize(json, jsonResolver)

let jsonDeserializeString (json: string): JsonValue =
  JsonSerializer.Deserialize(json, jsonResolver)
