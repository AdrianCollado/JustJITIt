# Just JIT It
Just JIT It is a tutorial on implementing a simple JIT compiler. It currently runs only on *nix systems, but this is more of an issue with build systems and toolchains rather than the code itself.

## Build Instructions
- Clone the repository.
- Run `make` from the main directory.
- Profit!

## Usage Instructions
### AOT Compilation
- Compiling: `jj -a -o <OUTPUT> [-f <NAME>]`
- Running: `jj -a -r <NAME>`

#### Naive Optimizations
- Compiling: `jj -an -o <OUTPUT> [-f <NAME>]`
- Running: `jj -an -r <NAME>`

#### Better Optimizations
- Compiling: `jj -ao -o <OUTPUT> [-f <NAME>]`
- Running: `jj -ao -r <NAME>`

### JIT Compilation
`jj -j [-f <NAME>]`

#### Naive Optimizations
`jj -jn [-f <NAME>]`

#### Better Optimizations
`jj -jo [-f <NAME>]`

### Interpretation
`jj -i [-f <NAME>]`