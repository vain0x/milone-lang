module rec octet_literal_bug.Program

// Bug. Int literals with leading zeros are octet literals in C.
// Leading zeros should be stripped.

// note: avoid doing "0" -> "", "0x1" -> "x1", "0e-1" -> "e-1".

let main _ =
  // assert (042 = 42)
  0
