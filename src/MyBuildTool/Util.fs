module internal MyBuildTool.Util

open System

module internal StringExt =
  let split (sep: string) (s: string) = s.Split(sep) |> Array.toList
  let trim (s: string) = s.Trim()

module internal Sha256 =
  open System.Security.Cryptography

  let compute (bytes: byte []) : string =
    use h = SHA256.Create()
    let hash = h.ComputeHash(bytes)

    BitConverter
      .ToString(hash)
      .Replace("-", "")
      .ToLower()
