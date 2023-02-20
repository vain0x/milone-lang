module internal MyBuildTool.Util

open System

module internal StringExt =
  let split (sep: string) (s: string) = s.Split(sep) |> Array.toList
  let trim (s: string) = s.Trim()

module internal IO =
  open System.IO

  let join (s: string) (t: string) = Path.Combine(s, t)
  let basename (s: string) = Path.GetFileName(s)
  let dirname (s: string) = Path.GetDirectoryName(s)
  let extname (s: string) = Path.GetExtension(s)

module internal Sha256 =
  open System.Security.Cryptography

  let compute (bytes: byte[]) : string =
    use h = SHA256.Create()
    let hash = h.ComputeHash(bytes)

    BitConverter.ToString(hash).Replace("-", "").ToLower()
