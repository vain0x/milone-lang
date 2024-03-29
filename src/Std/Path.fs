module rec Std.Path

module C = Std.StdChar
module S = Std.StdString

module Pathname =
  /// Checks if a pathname contains a drive letter.
  /// E.g. `C:/Windows`
  let hasDriveLetter (pathname: string) : bool =
    pathname.Length >= 2
    && C.isAlphabetic pathname.[0]
    && pathname.[1] = ':'

  /// Checks if a pathname starts with a root segment.
  /// E.g. `/`, `/path/to`, `C:/Windows`
  let hasRoot (pathname: string) : bool =
    S.startsWith "/" pathname
    || (pathname.Length >= 3
        && hasDriveLetter pathname
        && pathname.[2] = '/')

  /// Splits a pathname into the root part and the rest.
  ///
  /// This is a kind of inverse of join:
  ///
  /// ```fsharp
  ///   let root, relative = cutRoot absolute
  ///   assert (join root relative) = absolute
  /// ```
  ///
  /// If the specified pathname is a root itself,
  /// this returns a root and ".";
  /// e.g. `/` → `/`, `.`
  ///
  /// If the specified pathname is an absolute path (and isn't a root),
  /// this returns its root part and its relative part; e.g.
  ///
  /// - `/path/to` → `/`, `path/to`
  /// - `C:/path/to` → `C:/`, `path/to`
  ///
  /// If the specified pathname is a relative path or single filename,
  /// this returns "." as root and the pathname; e.g.
  ///
  /// - `my/relative` → `.`, `my/relative`
  /// - `dir/` → `.`, `dir/`
  /// - `file.txt` → `.`, `file.txt`
  let cutRoot (pathname: string) : string * string =
    if hasDriveLetter pathname then
      let root, rest = S.splitAt 3 pathname
      let rest = if rest.Length <> 0 then rest else "."
      root, rest
    else
      let pathname, slash = S.stripStart "/" pathname

      if slash then
        let rest =
          if pathname.Length <> 0 then
            pathname
          else
            "."

        "/", rest
      else
        ".", pathname

  /// Splits a pathname into the first part and the rest.
  ///
  /// This is a kind of inverse of join:
  ///
  /// ```fsharp
  ///   let head, tail = cut pathname
  ///   assert (join head tail) = pathname
  /// ```
  ///
  /// If the specified pathname is an absolute path,
  /// this returns its root and its relative part
  /// (same as cutRoot); e.g.
  ///
  /// - `/` → `/`, `.`
  /// - `/path/to` → `/`, `path/to`
  ///
  /// If the specified pathname is a relative path
  /// and contains a non-trailing separator "/",
  /// this returns the directory part and the rest;
  /// e.g. `path/to/filename` → `path`, `to/filename`
  ///
  /// Otherwise the specified pathname is single segment
  /// that is optionally followed by trailing separators.
  /// This returns `.` as head and the basename as tail; e.g.
  ///
  /// - `dirname/` → `.`, `dirname`
  /// - `filename.txt` → `.`, `filename.txt`
  let cut (pathname: string) : string * string =
    let root, pathname = cutRoot pathname

    if root <> "." then
      // Pathname is absolute.
      root, pathname
    else
      let rec go (pathname: string) =
        let len = pathname.Length

        match S.findIndex "/" pathname with
        | Some i ->
          // Pathname can't start with "/".
          assert (i >= 1)

          if i < len - 1 then
            pathname.[0..i - 1], pathname.[i + 1..len - 1]
          else
            // pathname endsWith "/".
            go pathname.[0..len - 2]

        | None -> ".", pathname

      go pathname

  /// Splits a pathname into its basename part and the rest.
  ///
  /// This is a kind of inverse of join:
  ///
  /// ```fsharp
  ///   let parent, basename = cutLast pathname
  ///   assert (join parent basename) = pathname
  /// ```
  ///
  /// - `/` → `/`, `.`
  /// - `/path/to` → `/path`, `to`
  /// - `.` → `.`, `.`
  /// - `..` → `.`, `..`
  /// - `dirname/` → `.`, `dirname`
  /// - `filename.txt` → `.`, `filename.txt`
  let cutLast (pathname: string) : string * string =
    let len = pathname.Length

    match S.findLastIndex "/" pathname with
    | Some 0 when len = 1 -> "/", "."

    | Some 0 ->
      // pathname = "/foo"
      "/", pathname.[1..pathname.Length - 1]

    | Some i when i = len - 1 ->
      // pathname endsWith "/"
      cutLast pathname.[0..len - 2]

    | Some i ->
      // pathname = ".../foo"
      pathname.[0..i - 1], pathname.[i + 1..pathname.Length - 1]

    | _ -> ".", pathname

  /// Removes `.` and `..` segments in the middle of pathname.
  ///
  /// - `./foo` → `foo`
  /// - `../foo` → `foo`
  let private contract (pathname: string) : string =
    let rec go acc (xs: string list) =
      match acc, xs with
      | _, "." :: xs -> go acc xs
      | x :: acc, ".." :: xs -> go acc xs

      | _, [] -> acc
      | _, x :: xs -> go (x :: acc) xs

    match cutRoot pathname with
    | _, "." -> pathname

    | root, pathname ->
      let pathname =
        pathname
        |> S.split "/"
        |> go []
        |> List.rev
        |> S.concat "/"

      if root <> "." then
        root + pathname
      else
        pathname

  /// Concatenates two pathnames in the order.
  ///
  /// If the right-hand side is absolute then
  /// the result is r.
  ///
  /// This function always uses "/" even on Windows.
  let join (l: string) (r: string) : string =
    if hasRoot r then
      // remove trailing sep unless r is root
      r
    else
      let rec go (l: string) (r: string) =
        if not (hasRoot l) && S.endsWith "/" l then
          go l.[0..l.Length - 2] r
        else if r = "." then
          l
        else
          match cut r with
          | ".", rr when rr <> r -> go l rr

          | ".", ".." ->
            let ll, lr = cutLast l

            if lr <> "." then ll
            else if ll = "/" then "/.."
            else if ll <> "." then ll + "/.."
            else ".."

          | "..", rr ->
            let ll, lr = cutLast l

            if lr <> "." then go ll rr
            else if ll <> "." then go ll r
            else r

          | _ when l = "/" -> l + r
          | _ -> l + "/" + r

      go l r

  /// Normalizes pathname syntactically.
  ///
  /// Disclaimer: UNC path on Windows is unsupported.
  let normalize (pathname: string) : string =
    let pathname =
      if S.contains "\\" pathname then
        S.replace "\\" "/" pathname
      else
        pathname

    // Upper drive letter.
    let pathname =
      if hasDriveLetter pathname then
        S.upperFirst pathname
      else
        pathname

    let pathname =
      let rec removeDoubleSlashes (s: string) =
        if S.contains "//" s then
          removeDoubleSlashes (S.replace "//" "/" s)
        else
          s

      removeDoubleSlashes pathname

    contract pathname

  /// Gets the basename part of a pathname.
  /// E.g. basename `path/to/foo.txt` is `foo.txt`
  let basename (pathname: string) : string =
    let _, it = cutLast pathname
    it

  /// Gets the dirname part of a pathname.
  /// E.g. dirname `path/to/foo.txt` is `path/to`
  let dirname (pathname: string) : string =
    let it, _ = cutLast pathname
    it

  /// Gets the stem part of a pathname.
  /// E.g. stem `path/to/foo.txt.orig` is `foo`.
  let stem (pathname: string) : string =
    let name = basename pathname

    match S.findLastIndex "." name with
    | Some i when 0 < i && i + 1 < name.Length -> name.[0..i - 1]
    | _ -> name
