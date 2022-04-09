# Internals

Documentation about design and implementation of the compiler.

- Development Environment -> [dev_env.md](dev_env.md)
- [ARCHITECTURE](../../ARCHITECTURE.md)
- [#Passes](#Passes)
- Also
    - [Plans](plans.md)
    - [Design Policy](design_policy.md)
    - [Glossary](glossary.md)
    - [nursery](nursery): Experimental projects written in milone-lang

## Passes

*Pass* is a routine to validate and/or transform a program.

Validation:

- Per-file:
    - [tokenize](tokenize.md)
    - ~~parse~~
    - ~~nir_gen~~
- [ast_bundle](ast_bundle.md)
- [name_resolution](name_resolution.md)
- ~~type_check~~
- [arity_check](arity_check.md)
- ~~linear_check~~

Transformation:

- ~~record_resolution~~
- ~~derive~~
- ~~closure_conversion~~
- ~~eta_expansion~~
- ~~auto_box~~
- ~~monomorphization~~
- ~~mir_gen~~
- ~~cir_gen~~
- ~~cir_dump~~

See also header comments in implementation files.

----

- [Misc](misc.md) (not interesting)
- [TODO list](https://github.com/vain0x/milone-lang/projects/1) (recently not updated)
