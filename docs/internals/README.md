# Internals

Documentation about design and implementation of the compiler.

## Passes

*Pass* is a routine to validate and/or transform a program.

Validation:

- ~~parse~~
- [name_resolution](name_resolution.md)
- ~~type_check~~
- [arity_check](arity_check.md)

Transformation:

- ~~record_resolution~~
- etc.

See also header comments in implementation files.
