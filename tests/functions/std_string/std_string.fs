module rec std_string.Program

open MiloneCore.List

module S = MiloneStd.StdString

let replaceTest () =
  assert (S.replace "a" "A" "abaca" = "AbAcA")
  assert (S.replace "xy" "yx" "xyxyx" = "yxyxx")
  assert (S.replace "" "" "as is" = "as is")
  assert (S.replace "aa" "a" "aaaaa" = "aaa")

let main _ =
  replaceTest ()
  0
