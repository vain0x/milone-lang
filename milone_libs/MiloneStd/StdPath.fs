module rec MiloneStd.StdPath

module S = MiloneStd.StdString

/// Any kind of file path or name.
///
/// Relative or absolute.
/// Regular file, directory, link or any other type.
/// File does or doesn't exist.
/// With or without extension.
type Path = Path of string

module Path =
  let ofString (s: string) : Path =
    let s =
      if S.contains "\\" s then
        S.replace "\\" "/" s
      else
        s

    Path s

  let toString (Path s) : string = s

  /// Removes trailing path separators.
  let trimEndSep (path: Path) : Path =
    let (Path s) = path
    Path(S.trimEndIf (fun c -> c = '/') s)

  /// Gets the final component.
  let basename (path: Path) : Path =
    let (Path s) = path

    match S.findLastIndex "/" s with
    | Some i -> Path(S.skip i s)
    | None -> path

  /// Removes last extension.
  let popExt (path: Path) : Path =
    let (Path s) = path

    match s |> S.findLastIndex "." with
    | Some i when 0 < i && i < s.Length -> Path(S.slice 0 i s)
    | _ -> Path s

  /// Gets the basename excluding last extension.
  let fileStem (path: Path) : Path = popExt (basename path)

  /// Starts with `./` or `../`
  let isRelative (Path s) : bool =
    (s |> S.startsWith "./")
    || (s |> S.startsWith "../")
