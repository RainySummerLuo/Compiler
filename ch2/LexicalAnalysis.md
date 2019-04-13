# Lexical Analysis

## Introduction

Lexer is simply a function that is called by the parser.

The value of the lexeme itself can be passed to the parser through the symbol table, if necessary (or through some global variable like `yylval`)

![1555138210243](C:\Users\rainy\AppData\Roaming\Typora\typora-user-images\1555138210243.png)

In addition to matching input, the lexer is also usually in charge of removing comments and white spaces from the source program (some programming languages, like Python or Haskell, rely on spaces to determine the start and end of blocks of statements, so lexers for Python or Haskell have to produce tokens representing spaces).

The lexer is also in charge of putting identifiers in the symbol table of the compiler. In addition to the identifier itself, the lexer will also put in the symbol table entry the line number in the source program where the identifier appears.

## Tokens, Patterns, Lexemes, Attributes

An **alphabet** is a set of symbols. (exp: C uses the ASCII alphabet, Java uses the Unicode alphabet.)

A **string** is defined as a finite sequence of symbols from the source alphabet (the alphabet for source programs). Note that a string of length zero (ε) is fine.

A **token** is then a set of strings over the source alphabet. Some tokens represent sets of finite size while some other tokens represent sets which are infinite in size.

A **pattern** is a mathematical rule that describes the set of strings for a token. We will use regular expressions to specify a pattern for each token.

A **lexeme** is then a sequence of alphabet symbols (a string) from the source program that is matched by a pattern, and therefore belongs to the set of strings for the corresponding token. This means that a token is the set of all the possible lexemes that are matched by the corresponding pattern (regular expression). 

Note: A lexeme is a piece of the source program, and the corresponding token, is a set of lexemes.

### Token Attributes

If a token corresponds to more than one lexeme then the lexer has to save more information about the token.

Each piece of extra information associated with a given token is called an **attribute**. In practice all the attributes for a given token are usually stored as entries in the symbol table, and the lexer returns to the parser not just simple tokens but pairs containing both a token and a pointer to the associated symbol table entry.

### Specification of Tokens

#### Strings

An alphabet (usually written as $Σ​$) is a set of symbols. A string over some alphabet $Σ​$ is then a finite sequence of symbols from Σ. We will write $|s|​$ to represent the length of the string $s​$. The **empty string** is then the string of length zero, which we write as $ε​$: $|ε| = 0​$ by definition.

A **prefix** of a string $s​$ is formed by removing zero or more symbols from the end of $s​$. From this definition, every string is also a prefix of itself. The empty string $ε​$ is a prefix of every string.

Symmetrically, a **suffix** of a string $s$ is formed by removing zero or more symbols from the beginning of $s$. Every string is also a suffix of itself. The empty string $ε$ is a suffix of every string.

A **substring** of a string $s$ is formed by removing both a prefix and a suffix from $s$. The prefix and suffix which are removed can both be the empty string, so every string is also a substring of itself. The empty string **ε** is a substring of every string.

A proper prefix / suffix / substring of a string $s$ is any non-empty string $t$ which is a prefix / suffix / substring of $s$ and such that $s$ and $t$ are different.

The **concatenation** of two strings $s​$ and $t​$ is the string obtained by appending the sequence of symbols in $t​$ to the sequence of symbols in $s​$, and is written $st​$. Note that $εs = sε = s​$.

The **exponentiation** of a string s is written as **$s^i$** and is defined as follows: **$s^i = ε$**, and **$s^i$ = $ss^{i-1}$** for $i > 0​$.

#### Languages

A **language** is a set of strings over some alphabet $Σ$. In this definition each string in the set is meant to represent a possible program, so a language is the set of all the possible programs.

The **union** $L∪M$ of two languages $L$ and $M$ is the set of strings s such that $s$ is either in $L$ or in $M$.

The **concatenation** $LM​$ of two languages $L​$ and $M​$ is the set of strings $st​$ where $s​$ is a string in $L​$ and $t​$ is a string in $M​$.

The **exponentiation** $L^i​$ of a language $L​$ is the language defined as follows: $L^0 = \{ε\}​$, and $L^i = LL^{i−1}​$ for $i > 0​$. From this definition, $L^1 = LL^0 = L\{ε\} = L​$. Similarly, $L^3 = LLL​$, which is the set of strings $stu​$ where $s​$, $t​$, and $u​$ are all strings in $L​$ (note that this is different from the set of strings $sss​$ where $s​$ is in $L​$).

The **Kleene closure** $L^*​$ of a language $L​$ is the language defined as $\bigcup_{i=0}^\infty L^i​$. In other words, $L^* = L^0 \cup L^1 \cup L^2 \cup L^3 \cup L^4 \cup . . .​$  Since $L^*​$ includes $L^0​$, it means $L^*​$ always includes $ε​$. For example, if $L​$ is $\{a, b\}​$, then $L^0​$ is $\{ε\}​$, $L^1​$ is $\{a, b\}​$, $L^2​$ is $\{aa, ab, ba, bb\}​$, $L^3​$ is $\{aaa, aab, aba, abb, baa, bab, bba, bbb\}​$, etc., and $L^*​$ is then the union of all these sets: $\{ε, a, b, aa, ab, ba, bb, aaa, aab, aba, abb, baa, bab, bba, bbb, . . . , abbabbaaaaba, . . . \}​$. So $L^*​$ is the set of all possible strings of $a​$s and $b​$s, including the empty string $ε​$.

The **positive closure** $L^+​$ of a language $L​$ is the language defined as $\bigcup_{i=1}^\infty  L^i​$. In other words, $L^* = L^1 \cup L^2 \cup L^3 \cup L^4 \cup . . .​$ Since $L^+​$ does no includes $L^0​$ it means that $L^+​$ includes $ε​$ if and only if $L​$ itself includes $ε​$. So $L^+​$ is the set of all possible non-empty strings of $a​$s and $b​$s.

From the definition of $L^*$ and $L^+$ we have the obvious relation $L^* = L + \cup\{ε\}$. Given such definitions, if $L$ is the set of letters and $D$ the set of digits, then $L(L\cup D)^*​$ is the set of all strings of letters and digits that start with a letter (i.e. what is often defined to be the set of identifiers).

#### Regular Expressions
**Regular expressions** are a notation that allows us to easily specify languages. Each regular expression $r$ denotes (is a notation for) a language $L(r)$. A regular expression $r$ is often built by combining simpler regular expressions together. The corresponding language $L(r)$ is then defined by combining the languages corresponding to the simpler regular expressions using a set of rules that we now describe.

Regular expressions over an alphabet $Σ$ are defined as follows:

- $ε​$ is the regular expression that denotes the language $\{ε\}​$, i.e. the language that only contains the empty string. 
- If $a$ is a symbol in $Σ$, then $a$ is a regular expression denoting the language $\{a\}$.
- If $r$ is a regular expression that denotes $L(r)$ and $s$ is a regular expression that denotes $L(s)$, then:
  - $(r)|(s)$ denotes the language $L(r) \cup L(s)$. In short, the symbol $|$ in a regular expression acts as an "or" operator.
  - $(r)(s)$ denotes the language $L(r)L(s)$. In short, the concatenation of regular expressions corresponds to the concatenation of the denoted languages.
  - $(r)^*$ denotes the language $(L(r))^*$. The $ ^∗$ operator in a regular expression is called the Kleene star and corresponds to the Kleene closure of the denoted language. In short, the symbol $^*$ in a regular expression means "zero or more instances of".
  - $(r)$ denotes the same language $L(r)$ as $r$ does. In short, extra parentheses do not matter in a regular expression.

This definition of regular expression is recursive. It works in fact by induction on the structure of a regular expression.

To avoid writing too many parentheses we use the following extra rules:

- The $^*$ operator has the highest precedence and is left associative.
- Concatenation has the next highest precedence and is left associative.
- The $|​$ operator has the lowest precedence and is left associative.

Regular expressions have the following algebraic properties:

- $r|s$ = $s|r$: the $|$ operator is commutative.
- $r|(s|t)$ = $(r|s)|t$: the $|$ operator is associative.
- $r(st) = (rs)t$: concatenation is associative.
- $r(s|t) = rs|rt$ and $(s|t)r = sr|tr$: concatenation distributes over the $|$ operator.
- $εr = r = rε$: the regular expression $ε$ is the identity element for regular expression concatenation (just like the empty string $ε$ is the identity element for string concatenation).
- $r^* = (r|ε)^*​$: relation between $ε​$ and the Kleene star.
- $r^{**} = r^*​$: the Kleene star is idempotent.

To simplify things even further, we can defined some new notation for some regular expressions:
- $r^+ = rr^*$: the + operator means "one or more instance of". This operator corresponds to the positive closure of the corresponding language. We then have the following algebraic property: $r^* = r^+|ε$.
- $r^? = r|ε$: the $?$ operator means "zero or one instance of".
- $0|1|2|3|4|5|6|7|8|9 = [0−9]$: classes of characters (like digits, or letters) can be abbreviated using an interval notation.

To simplify the definition of regular expressions, it is often convenient to use regular definitions, which are regular expressions that are given names: 

<center>
digit → 0|1|2|3|4|5|6|7|8|9
</center>
<center>
natural → digit digit*
</center>
<center>
unsigned rational → natural(ε|.natural)
</center>
<center>
signed rational → (+|-|ε)unsigned rational
</center><br/>

### Tokens and Regular Expressions

we can therefore also use a regular expression to describe a token. In fact this is exactly how you are going to define the set of lexemes that form a token when you are going to implement a lexer: by creating a regular expression that describes that set of lexemes. In essence the regular expression will define a pattern and every input string that is matched by the pattern will be part of the token corresponding to the regular expression.

## From Regular Expressions to Lexical Analyzers

The process to go from a regular expression to the code of a lexer is going to involve three steps:

- first the regular expression (RE) will be transformed into a nondeterministic finite automaton (NFA) that can recognize input strings that are matched by the RE;
- since computers are deterministic machines, we will then have to transform the NFA into a deterministic finite automaton (DFA);
- finally we will see how to implement a DFA using simple C code, which will then be the C code of a lexer that can recognize input strings that are matched by the original RE.

### Using Deterministic Finite Automata to Match Input
