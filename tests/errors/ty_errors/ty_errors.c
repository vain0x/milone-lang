#error ty_errors:1:1 Type mismatch: 'unit' <> 'int'. Occurred while unifying 'unit' to 'int'.
#error ty_errors:3:5 Undefined variable f
#error ty_errors:7:24 Type mismatch: 'string' <> 'int'. Occurred while unifying '((int * string) * int)' to '((int * int) * int)'.
#error ty_errors:13:17 Recursive type occurred while unifying '{?11}@ty_errors:13:13' to '{?13}@ty_errors:13:3 -> {?22}@ty_errors:13:17'.
