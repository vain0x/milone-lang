# Profiling

This is a note how to profile the compiler.

## Prerequisites

- Ubuntu (Linux)
- `gprof` (GNU prof)
- `python3`
- `graphviz`
- [gprof2dot](https://github.com/jrfonseca/gprof2dot), visualizer

```sh
sudo apt install python3 graphviz

GPROF2DOT='https://raw.githubusercontent.com/jrfonseca/gprof2dot/master/gprof2dot.py'
curl -sL "$GPROF2DOT" -o ~/.local/bin/gprof2dot && chmod +x ~/.local/bin/gprof2dot
```

## Script

In a nutshell, do on the repository root:

```sh
scripts/prof
```

and `target/prof.png` is generated.

---

## Explanation

> 1\. `make worktree && test -f "$MILONE_CMD"`

We need to have a pre-built milone-lang compiler. Generate one by building the worktree:

> 2\.
> ```sh
> CC='gcc -pg' MILONE_HOME=$PWD "$MILONE_CMD" build --release 'src/MiloneCli' --target-dir 'target/MiloneProf' -o 'target/milone-prof'
> ```

Next, compile the milone-lang compiler with *instrumentation* enabled by passing `-pg` flag to GCC.
The environment variable `CC` is used to compile C source files internally.

Target directory is modified to another directory (`target/MiloneProf`) than the default one (`target/MiloneCli`).
This avoids overwriting intermediate object files in that directory.

`-o` is specified to ensure the output executable is available at the specified path.

> 3\.
> ```sh
> MILONE_HOME=$PWD target/milone-prof check src/MiloneCli && \
>     test -f gmon.out && \
>     mv gmon.out target/gmon.out
> ```

This runs the compiler built on the previous step.
As an effect of `-pg` flag, the command will emit an extra file named `gmon.out` on the working directory after successful exit.
`test` command makes it explicit.
The following `mv` command move that file to the target directory just because we don't want to scatter files in the repository root and ensure not to commit.

The `gmon.out` file records the profiling data while the command is running.
Data, what functions are called, how many times they are called, how long they spend time, etc.

> 4\.
> ```sh
> gprof target/milone-prof target/gmon.out | \
>    tee target/prof.txt | \
>    gprof2dot | \
>    dot -Tpng -o target/prof.png
> ```

Finally convert the record to a human-readable format.
`gprof` command generates a plain text file, which is written to `target/prof.txt`.

`gprof2dot` command converts the text (piped from gprof) to another format called dot language, which describes relationship of entities, i.e.
a graph that consists of functions and connection from callee ones to callers.
`dot` command (from graphviz package) converts the dot to a PNG image, which is a visualized form of the profiling data.

#### Legends

In the image, functions are associated with several numbers.

```
    SomeFun
     42%
    (5.3%)
     64x
```

- First row (`SomeFun`): Mangled name of the function
- Second row (`42%`): Total time spent while the function is called, including other functions that it called to
- Third row (`(5.3%)`): Time spent while the function is called itself, excluding the other functions
- Last row (`64x`): The number of times the function is called
