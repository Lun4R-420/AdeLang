# AdeLang

A small programming language and its compiler, `adec`, written from scratch in C++20. It compiles `.adel` source files directly to x86-64 assembly, with no LLVM or other compiler backend, and uses `gcc` only to assemble and link the result.

The front end is based on [Crafting Interpreters](https://craftinginterpreters.com/), but AdeLang generates native code instead of interpreting. The project is in progress.

## Example

```
fun fib(n: int) -> int {
    if n < 2 {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

var i = 0;
while i < 10 {
    print fib(i);
    i = i + 1;
}
```

```
0
1
1
2
3
5
8
13
21
34
```

## What works

- Integer arithmetic, comparisons and unary operators
- `print` and expression statements
- Variables with lexical scopes and shadowing
- `if` / `else if` / `else` and `while`, with Go-style conditions (no parentheses, braces required)
- Functions with parameters, return values and recursion, including calls to functions declared later in the file

Type annotations are parsed, but they are not checked yet.

## How it works

```
source.adel -> scanner -> parser -> AST -> codegen -> source.s -> gcc -> executable
```

| File | Role |
| --- | --- |
| `src/scanner.cpp` | Turns source text into tokens |
| `src/parser.cpp` | Recursive-descent parser that builds the AST |
| `src/ast.hpp` | AST nodes, modeled with `std::variant` |
| `src/ast_printer.cpp` | Prints expression trees for debugging |
| `src/codegen.cpp` | Generates AT&T syntax assembly for the System V ABI |
| `src/main.cpp` | Command line driver, calls `gcc` on the generated assembly |

The generated `.s` file is kept next to the output, so you can read exactly what the compiler produced.

## Build and run

You need Linux on x86-64 (WSL works), `g++` with C++20 support, `gcc` and `make`.

```bash
cd src
make
./adec ../playground/funcs.adel -o ../playground/funcs
../playground/funcs
```

`make test` compiles and runs every program in `playground/`. Some of those programs fail with a compile error on purpose, to exercise error reporting.

## Roadmap

- Type checker with local type inference
- Booleans, strings and floats
- Later: arrays, optional types instead of null, and a garbage collector

## License

[MIT](LICENSE)
