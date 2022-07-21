// Check if `Region` deallocates memories correctly
// by running this program with address sanitizer enabled.

open Std.Region

// Produce a large list to allocate some memory. (Using Collatz conjecture.)
let rec produce acc t i =
  if t = 1 && i <= 0 then
    acc
  else if t % 2 = 0 then
    produce (i :: acc) (t / 2) (i - 1)
  else
    produce (i :: acc) (t * 3 + 1) (i - 1)

// Consume a large list to not optimizer removing the allocation.
let rec consume h xs =
  match xs with
  | [] -> h

  | x :: xs -> consume (h + x) xs

let stress (i: int) =
  // printfn "stress i=%d" i
  consume i (produce [] i i)

let main _ =
  let rec go h i =
    if i = 0 then
      h
    else
      printfn "go i=%d" i
      let h = h + (Region.run (fun () -> stress i))
      go h (i - 1)

  Region.run (fun () -> (go 0 10 % 100) - 84)
