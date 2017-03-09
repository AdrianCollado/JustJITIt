# Just JIT It
Just JIT It is a tutorial on implementing a simple JIT compiler. It currently runs only on *nix systems, but this is more of an issue with build systems and toolchains rather than the code itself.

## Build Instructions
- Clone the repository.
- Run `make` from the main directory.
- Profit (executable is in the `Build` folder as `Build/jj`)

## Usage Instructions
### AOT Compilation
- Compiling: `Build/jj -a -o <OUTPUT> [-f <NAME>]`
- Running: `Build/jj -a -r <NAME>`

#### Naive Optimizations
- Compiling: `Build/jj -an -o <OUTPUT> [-f <NAME>]`
- Running: `Build/jj -an -r <NAME>`

#### Better Optimizations
- Compiling: `Build/jj -ao -o <OUTPUT> [-f <NAME>]`
- Running: `Build/jj -ao -r <NAME>`

### JIT Compilation
`Build/jj -j [-f <NAME>]`

#### Naive Optimizations
`Build/jj -jn [-f <NAME>]`

#### Better Optimizations
`Build/jj -jo [-f <NAME>]`

### Interpretation
`Build/jj -i [-f <NAME>]`