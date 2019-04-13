# Lexical Analysis

## Introduction

Lexer is simply a function that is called by the parser.

The value of the lexeme itself can be passed to the parser through the symbol table, if necessary (or through some global variable like `yylval`)

![1555138210243](C:\Users\rainy\AppData\Roaming\Typora\typora-user-images\1555138210243.png)

In addition to matching input, the lexer is also usually in charge of removing
comments and white spaces from the source program (some programming languages, like Python or Haskell, rely on spaces to determine the start and end of blocks of statements, so lexers for Python or Haskell have to produce tokens representing spaces).

The lexer is also in charge of putting identifiers in the symbol table of the
compiler. In addition to the identifier itself, the lexer will also put in the symbol
table entry the line number in the source program where the identifier appears.

## Tokens, Patterns, Lexemes, Attributes

An **alphabet** is a set of symbols. (exp: C uses the ASCII alphabet, Java uses the Unicode alphabet.)

A **string** is defined as a finite sequence of symbols from the source alphabet
(the alphabet for source programs). Note that a string of length zero (ε) is fine.

A **token** is then a set of strings over the source alphabet. Some tokens represent sets of finite size while some other tokens represent sets which are infinite in size.

A **pattern** is a mathematical rule that describes the set of strings for a token.
We will use regular expressions to specify a pattern for each token.

A **lexeme** is then a sequence of alphabet symbols (a string) from the source
program that is matched by a pattern, and therefore belongs to the set of strings
for the corresponding token. This means that a token is the set of all the possible
lexemes that are matched by the corresponding pattern (regular expression).