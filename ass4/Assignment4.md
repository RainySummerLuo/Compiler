# Assignment 4 
Consider the following context-free grammar for simple bitwise expressions
in the C programming language:
```
B -> T | B ^ T
T -> F | T & F
F -> ˜ F | ( B ) | 1 | 0
```
where ```'^'``` (the C bitwise "xor" operator), ```'&'``` (the C bitwise "and"
operator), ```'˜'``` (the C bitwise negation operator), ```'('```, ```')'```, ```'1'```, and ```'0'```
are tokens, and B is the start symbol for the grammar.
Note: this grammar does not contain the ```'|'``` C bitwise "or" operator so that
you do not confuse it with the symbol | that we use to separate grammar
productions.

1. Using the grammar above, construct a leftmost derivation and a parse
   tree for the following input:
   ```˜ ( 1 ^ 0 )```

   The list of grammar productions in the output of the parsing algorithm:

   | Stack | Input           | Output |
   | ----- | --------------- | ------ |
   | $B    | ~ ( 1 ^ 0 ) $ |  |
   | $T  | ~ ( 1 ^ 0 ) $ | B -> T |
   | $F |             ~ ( 1 ^ 0 ) $ |T -> F|
   | $F˜ | ~ ( 1 ^ 0 ) $ | F -> ˜ F |
   | $F | ( 1 ^ 0 ) $ |  |
   | $)B( | ( 1 ^ 0 ) $ | F -> ( B ) |
   | $)B | 1 ^ 0 ) $ |        |
   | $)T^B | 1 ^ 0 ) $     | B -> B ^ T |
   | $)T^T |1 ^ 0 ) $|B -> T|
   | $)T^F |1 ^ 0 ) $|T -> F|
   | $)T^1 |1 ^ 0 ) $|F -> 1|
   | $)T^ |^ 0 ) $||
   | $)T |0 ) $||
   | $)F |0 ) $|T -> F|
   | $)0 |0 ) $|F -> 0|
   | $) |) $||
   | $ |$||

   Construct the leftmost derivation of the input:

   ​	      B

   ​	⇒    T

   ​	⇒    F

   ​	⇒    ˜ F

   ​	⇒    ˜ ( B )

   ​	⇒    ˜ ( B ^ T )

   ​	⇒    ˜ ( T ^ T )

   ​	⇒    ˜ ( F ^ T )

   ​	⇒    ˜ ( 1 ^ T )

   ​	⇒    ˜ ( 1 ^ F )

   ​	⇒    ˜ ( 1 ^ 0 )

   From this leftmost derivation construct the parse tree:

   ​	![下载 (assets/下载 (1).png)](../../../../Downloads/下载 (2).png)

2. Eliminate left-recursion from the grammar (if necessary) and left-factor
   the grammar (if necessary). Explain step by step how you do it.

   The original grammar is:

   ```
   B -> T | B ^ T
   T -> F | T & F
   F -> ˜ F | ( B ) | 1 | 0
   ```

   

3. Use the new grammar from Question 2 to construct a leftmost derivation and a parse tree for the same input as in Question 1.

4. Compute the FIRST and FOLLOW sets for the new grammar from Question 2. Explain step by step how you do it.
   Note: for FIRST, list the tokens in the following order from left to right:
   ```1, 0 , ˜, ^, &, (, )```
   For FIRST and FOLLOW, list the nonterminals in the following order from left to right: 

   ```B, B', T, T', F```

5. Use the FIRST and FOLLOW sets computed in Question 4 to create a parsing table for a top-down non-recursive predictive parser.
   Explain step by step how you do it.
   Note: for the columns and rows, list the tokens and nonterminals in the same order as in Question 4.
   Note: there is no need to do any error recovery in the parsing table.

6. Use the parsing table from Question 5 to parse the input from Question 1. Show the content of the stack at each step and the output of the parser. There is no need to explain each step.

    The input is: ```˜ ( 1 ^ 0 )```

7. Use the output computed by the parser in Question 6 to create a derivation and a parse tree for the parser's input. Compare the result with your answer to Question 3.