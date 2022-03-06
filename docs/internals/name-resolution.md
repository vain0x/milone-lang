# Name Resolution

**Name resolution** is a pass to associate names with definitions.

## Input and Output

Input is "name resolution intermediate representation" (NIR). List of layered modules. Modules are topologically sorted; that is, modules depend on only modules in earlier layers.

Output is combination of:

- "Typed intermediate representation" (TIR) modules
- Symbol definitions
- Compile errors

## Key Points

### Declaration and Definition

Declaration and definition are distinctly defined here.

**Declaration** is a syntactic element such as type statement that defines some symbol.

**Definition** is an instance of defined symbol that contains detailed data about the symbol.

Key difference is that declaration is a syntactic element. Definition is a semantic information.

### Symbol

**Symbol** is a value as a reference to a symbol definition.

Symbols are categorized to values and types:

- *Value* symbol is a reference to value definition such as variable.
- *Type* symbol is a reference to type definition such as record type.

### Environment, Scope, Namespace

Environment, scope and namespace are distinctly defined here. Be careful of them to not confuse. Understanding the three is important to understand name resolution clearly.

**Environment** is a data structure, mapping from name to symbols. Environment separately stores value names and type names. It also stores NsOwner symbols separately from values and types for namespace merging. Environment is owned by either scope or namespace.

**Scope** is a certain area where a particular set of symbols are accessible. Scope is associated with a syntactic element such as let expressions. Scope owns an environment. As long as a symbol is accessible from current scope, such symbol can be referred to by unqualified name.

Scopes form a tree structure. Path from a leaf to the root is called **scope chain**. 

**Namespace** (`ns` for short) is a set of symbols that are associated to other symbol that is considered parent. For example, a module contains several functions and types as members and then namespace of that module has an environment for contained functions and types.

Differences of scope and namespace are:

- Scope is looked up to resolve unqualified names.
    Namespace is looked up to resolve qualified names.
- Scope inherits environment from its parent.
    Namespace doesn't.
- Scope is related to syntactic element.
    Namespace is related to symbols.
- Scope is transient; not accessible from outside of corresponding syntactic element.
    Namespace is persistent; accessible from downstream modules.

### Namespace Owner

**Namespace owner** (`nsOwner` in code) is a symbol that owns its namespace. Discriminated union types and modules are namespace owners.

### Shadowing

*Shadowing* is a behavior that a scope chain makes a name unreachable when a symbol of the same name is added.

Let a scope chain have a symbol S with a name X and another symbol T be added to current scope with the name X. Name X is now resolved to T. In other words, the symbol S is now unreachable by name X.

Value symbols and type symbols shadow.

### Namespace Merging

In contrast of shadowing, NsOwner symbols are merged. Newly added NsOwner symbols are preferred in a scope chain but other NsOwner symbols are still used as fallback.

Let a scope chain have a NsOwner symbol Q with a name X and another NsOwner symbol R is added with the same name to scope. Name `X.y` is now resolved to `Q.y` or `R.y`. That is, name `X` behaves like union of namespaces Q and R.

### Hoisting

*Hoisting* is a behavior that some symbols are added to current scope before its declaration. The declaration is called *hoisted*.

Recursive module *hoists* all declarations in it so that they can refer to each other.

## Control of Name Resolution

Name resolution consists of the two parts:

- Collect declarations (`collectDecls` or `cdXxx` in code)
- Resolve expressions (`resolveXxx` or `nameResXxx` in code)

The separation is necessary so that symbols can occur *before* their declaration (*forward referencing*).

**Collect declaration** is a preparation routine to traverse declarations and collect information enough to resolve forward referencing names. It doesn't create complete symbol definitions.

**Resolve expressions** is the main routine of name resolution. It traverses entire program to resolve all names that occur in a program; type ascriptions, patterns, expressions, type declarations. It creates symbol definitions such as variables and types.

## Details of Resolution

WIP: To be written.

----
----

## Remarks

### Symbol table

The term "symbol table" is frequently used in textbooks. It isn't used here because it isn't a two-dimensional table.

### Different meaning of namespace

The term *namespace* is typically used in the two different meaning.

One is **structure of names**. Typically a tree of names. One of examples is "domain namespaces"; `www.example.com` represents a path `/com/example/www`. Another example is the "module" feature in Rust. **The term "namespace" is used here in this meaning**.

The other one is **kind of names**. Kinds are typically values and types. Different kind of symbols live in different "namespaces" (in this meaning) so that such names don't collide. For example, both of function `int` and type `int` can exist in the same scope. **This meaning is NOT used here** for less confusion.

Mentioning the "namespace" feature in C++ for more understanding of the distinction. C++ namespace owns an 'namespace' (as the definition in this document) but also affects 'scope' in non-trivial way. 'Scope' of an namespace block automatically includes all symbols in the namespace. That behavior allows to split a set of declarations to multiple namespace blocks without 'import'ing symbols declared in other blocks.

```cpp
// First block of namespace animal.
namespace animal {
    // Declaration of animal.Dog class.
    class Dog;
}

// Second block of namespace animal.
namespace animal {
    // Refer to the Dog class via unqualified name.
    void use_dog(Dog *dog);
}
```

### Namespace is graph

Unlike domain namespaces, namespaces here don't form a tree but form a graph. Open declarations and module synonyms can make single name accessible from multiple modules.

### Alias

**Alias** is a name that is stored as key in environment.

### Let Declaration and Let Expression

*let* is an expression but is also a declaration if it's put directly in a module. Difference is that *let* expressions have `in` clause but *let* declaration doesn't.

### Fields

Currently fields aren't counted as symbols.
Fields are resolved in type check.
