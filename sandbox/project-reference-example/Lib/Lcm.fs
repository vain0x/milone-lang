module rec Lib.Lcm

open Lib.Gcd

let lcm (x: int) (y: int) = (x / gcd x y) * y
