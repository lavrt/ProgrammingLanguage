# Custom Programming Language

A from-scratch implementation of a custom programming language featuring lexing, parsing, bytecode generation, and execution on a custom virtual machine.

## Key Features

**Toolchain Implementation**:
- Lexical analyzer (lexer)
- Recursive descent parser
- Bytecode compiler
- Custom virtual machine executor

**Language Syntax Support**:
- Integer variables and arithmetic
- Control flow (loops, conditional statements)
- Function definitions and calls
- Basic I/O operations

**Sample Program**:
Factorial calculation
```
def f ( n )
{
    k = 1 ;
    i = 0 ;
    while ( i < n )
    {
        i = i + 1 ;
        k = k * i ;
        if ( n == i )
        {
            return k ;
        } ;
    } ;
} ;
n = 5 ;
k = call f ( n ) ;
print ( k ) ;
end
```
Output: `120`

## Build Instructions
```bash
git clone https://github.com/lavrt/ProgrammingLanguage
cd ProgrammingLanguage
./build.sh
```

## Tools Used
- C programming language
- GNU Make build system
