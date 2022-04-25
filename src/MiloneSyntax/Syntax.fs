/// # Syntax
///
/// Provides functions for types defined in SyntaxTypes.
module rec MiloneSyntax.Syntax

open MiloneShared.SharedTypes
open Std.StdMap
open MiloneSyntaxTypes.SyntaxTypes

// -----------------------------------------------
// TokenizeError
// -----------------------------------------------

let tokenizeErrorToString error =
  match error with
  | InvalidCharLitError -> "Invalid char literal."
  | InvalidStringLitError -> "Invalid string literal."
  | InvalidRawIdentError -> "Invalid raw identifier. Hint: ``write like this``."
  | BadTokenError -> "Invalid characters."

  | UnknownEscapeSequenceError ->
    "Unknown escape sequence. After `\\`, one of these chars is only allowed: `\\` `'` `\"` t r n x."

  | UndefinedOpTokenError -> "Undefined operator."

  | ReservedWordError ->
    "This word can't be used as identifier, because it's reserved for future expansion of the language."

  | UnimplNumberSuffixError -> "Some of number literal suffixes are unimplemented yet."
  | OtherTokenizeError msg -> msg

// -----------------------------------------------
// Keywords
// -----------------------------------------------

type private KeywordMap = TreeMap<Ident, Token>

// See also <https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/keyword-reference>.
let private keywordMapBuild () : KeywordMap =
  let miloneKeywords =
    [ "as", AsToken
      "else", ElseToken
      "false", FalseToken
      "fun", FunToken
      "if", IfToken
      "in", InToken
      "let", LetToken
      "match", MatchToken
      "module", ModuleToken
      "of", OfToken
      "open", OpenToken
      "private", PrivateToken
      "public", PublicToken
      "rec", RecToken
      "then", ThenToken
      "true", TrueToken
      "type", TypeToken
      "when", WhenToken
      "with", WithToken ]

  let fsharpKeywords =
    [ "abstract"
      "and"
      "base"
      "begin"
      "class"
      "const"
      "default"
      "delegate"
      "do"
      "done"
      "downcast"
      "downto"
      "elif"
      "end"
      "exception"
      "extern"
      "finally"
      "fixed"
      "for"
      "function"
      "global"
      "inherit"
      "inline"
      "interface"
      "internal"
      "lazy"
      "member"
      "mutable"
      "namespace"
      "new"
      "null"
      "or"
      "override"
      "return"
      "static"
      "struct"
      "to"
      "try"
      "upcast"
      "use"
      "val"
      "void"
      "while"
      "yield" ]

  let ocamlKeywords =
    [ "asr"
      "land"
      "lor"
      "lsl"
      "lsr"
      "lxor"
      "mod"
      "sig" ]

  let reservedWords =
    [ "break"
      "checked"
      "component"
      "const"
      "constraint"
      "continue"
      "event"
      "external"
      "include"
      "mixin"
      "parallel"
      "process"
      "protected"
      "pure"
      "sealed"
      "tailcall"
      "trait"
      "virtual" ]

  let reservedToken = ErrorToken ReservedWordError

  let map = TMap.empty compare

  let map =
    miloneKeywords
    |> List.fold (fun map (name, token) -> TMap.add name token map) map

  let map =
    fsharpKeywords
    |> List.fold (fun map name -> TMap.add name reservedToken map) map

  let map =
    ocamlKeywords
    |> List.fold (fun map name -> TMap.add name reservedToken map) map

  let map =
    reservedWords
    |> List.fold (fun map name -> TMap.add name reservedToken map) map

  map

// -----------------------------------------------
// Host
// -----------------------------------------------

let tokenizeHostNew () : TokenizeHost =
  let keywordMap = keywordMapBuild ()

  { FindKeyword = fun ident -> keywordMap |> TMap.tryFind ident }

// -----------------------------------------------
// Module dependencies
// -----------------------------------------------

let findDependentModules ast : (ProjectName * ModuleName * Pos) list =
  let rec onDecl decl =
    match decl with
    | AOpenDecl ([ Name (p, _); Name (m, _) ], pos) -> Some(p, m, pos)
    | AModuleSynonymDecl (_, [ Name (p, _); Name (m, _) ], pos) -> Some(p, m, pos)
    | AAttrDecl (_, next, _) -> onDecl next
    | _ -> None

  let (ARoot (_, decls)) = ast

  decls |> List.choose onDecl
