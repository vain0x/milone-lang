debugging with gdb

```sh
$ gdb --args milone run tests/features/record_large

# set break points
> (gdb) b milone_assert

# start running
> (gdb) start

# when stop at breakpoint
> (gdb) backtrace
```
