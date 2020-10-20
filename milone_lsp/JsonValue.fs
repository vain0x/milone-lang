[<AutoOpen>]
module MiloneLsp.JsonValue

[<Struct>]
type JsonValue =
  | JNull
  | JString of stringValue: string
  | JNumber of numberValue: float
  | JBoolean of boolValue: bool
  | JArray of items: JsonValue list
  | JObject of entries: Map<string, JsonValue>
