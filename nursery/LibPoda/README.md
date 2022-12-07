# LibPoda

**Poda** (POrtable DAta) is a data type that has defined memory layout, to be used for interoperability with other languages such as C.

Poda enables other languages to (1) send non-trivial data to milone-lang and (2) receive non-trivial data from milone-lang.

## What

(See `Poda.milone` and `milone_poda.h` for details.)

Poda consists of:

- **basic types**: null, boolean, int, uint64, int64, float64, string
- **compound types**:
    - array (of Poda values)
    - map (from strings to Poda values)
- foreign (opaque pointer)

### Runtime Representation

A Poda value is a pair of an integer (type) and a union value (payload) as specified in the header.
The layout is stable, that is, doesn't change in newer versions.

### Remark

- 64-bit float value is called **float64** here to avoid confusion.
