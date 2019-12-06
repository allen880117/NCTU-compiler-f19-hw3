# Project Assignment 4 - Semantic Definitions

**Introduction to Compiler Design by Prof. Yi-Ping You**

Due Date: **23:59, December 27, 2019**

Your assignment is to perform semantic analyses for a `P` program. In the previous project, you have constructed an abstract syntax tree (AST). In this assignment, you will do some simple checking of semantic correctness. Code generation will be performed in the last phase of the project.

**Table of Contents**
- [Project Assignment 4 - Semantic Definitions](#project-assignment-4---semantic-definitions)
	- [Assignment](#assignment)
	- [Pseudocomments](#pseudocomments)
	- [Symbol Table](#symbol-table)
	- [Semantic Definition](#semantic-definition)
	- [What Should Your Parser Do?](#what-should-your-parser-do)
	- [Project Structure](#project-structure)
	- [Submitting the Assignment](#submitting-the-assignment)

## Assignment

You first need to construct your symbol table when your parser visits a node related to adding a new scope. More specifically, the parser should be able to perform the following tasks:

- Push a symbol table when entering a scope and pop it when exiting the scope.
- Insert entries for (constant) variables, functions, and program declarations.
- Lookup entries in the symbol table.

After that, you need to perform semantic analyses with the help of symbol tables by performing post-order traversal on the AST, following the semantic definitions described below.

In summary, you need to implement the construction of symbol tables and semantic analyses based on the AST you constructed in the previous assignment by traversing the AST in preorder and postorder, respectively.

## Pseudocomments

In the first assignment, we have defined:

- `S`
	- `&S+` turns on source program listing, and `&S-` turns it off.
- `T`
	- `&T+` turns on token (which will be returned to the parser) listing, and `&T-` turns it off.

In this assignment, one more option is added:

- `D`
	- Dump the contents of the symbol table associated with a block when exiting from that block.
	- `&D+` turns on symbol table dumping, and `&D-` turns it off.
	- By default, this option is on.

## Symbol Table

To perform semantic analyses, you should maintain a symbol table per scope in your parser. Each entry of a symbol table is an identifier associated with its attributes, such as its name, kind (program, function, parameter, variable, or constant), scope (local or global), type, the value of constant, etc.

In effect, the role of a symbol table is to pass information from declarations to uses. A semantic action "puts" information about identifier `x` into the symbol table when the declaration of `x` is analyzed. Subsequently, a semantic action associated with reference of the identifier "gets" information about the identifier from the symbol table.

### Components

Each entry of a symbol table consists of the name, kind, scope level, type, value, and additional attributes of a symbol. Symbols are placed in the symbol table in order of their appearance in the input file. Precise definitions of each entry are as follows.

| Field | Description |
| ----- | ----------- |
| Name | The name of the symbol. Each symbol have the length between 1 to 32. |
| Kind | The name type of the symbol. There are **six** kinds of symbols: program, function, parameter, variable, loop\_var, and constant. |
| Level | The scope level of the symbol. 0 represents the global scope. Local scope levels start from 1, and the scope level is incremented at the start of a scope and decremented at the end of the scope.  |
| Type | The type of the symbol. Each symbol is of types integer, real, boolean, string, or the signature of an array. (Note that this field can be used for the return type of a function ) |
| Attribute | Other attributes of the symbol, such as the value of a constant, list of the types of the formal parameters of a function, etc. |

### Output Format

```c
void dumpDemarcation(const char chr) {
  for (size_t i = 0; i < 110; ++i) {
    printf("%c", chr);
  }
  puts("");
}

void dumpSymbol(void) {
  dumpDemarcation('=');
  printf("%-33s%-11s%-11s%-17s%-11s\n", "Name", "Kind", "Level", "Type",
                                        "Attribute");
  dumpDemarcation('-')
  {
    printf("%-33s", "func");
    printf("%-11s", "function");
    printf("%d%-10s", 0, "(global)");
    printf("%-17s", "boolean");
    printf("%-11s", "integer, real [2][3]");
    puts("");
  }
  dumpDemarcation('-')
}
```

### Sample Output

For example, given the input:

```
 1: test;
 2:
 3: // no global declaration(s)
 4:
 5: func( a:integer ; b:array 1 to 2 of array 2 to 4 of real ): boolean;
 6: begin
 7:     var c: "hello world!";
 8:     begin
 9:         var d: real;
10:         return (b[1][4] >= 1.0);
11:     end
12: end
13: end func
14:
15: begin
16:     var a: integer;
17: begin
18:     var a: boolean;  // outer ’a’ has been hidden in this scope
19: end
20: end
21: end test
```

After parsing the compound statement in function `func` (at line 11), you should output the symbol table with the following format.

```
==============================================================================================================
Name                             Kind       Level      Type             Attribute
--------------------------------------------------------------------------------------------------------------
d                                variable   2(local)   real
--------------------------------------------------------------------------------------------------------------
```

After parsing the definition of function `func` (at line 13), you should output the symbol table with the following format.

```
==============================================================================================================
Name                             Kind       Level      Type             Attribute
--------------------------------------------------------------------------------------------------------------
a                                parameter  1(local)   integer
b                                parameter  1(local)   real [1][2]
c                                constant   1(local)   string           "hello world!"
--------------------------------------------------------------------------------------------------------------
```

After parsing the compound statement in the main block (at line 19), you should output the symbol table with the following format.

```
==============================================================================================================
Name                             Kind       Level      Type             Attribute
--------------------------------------------------------------------------------------------------------------
a                                variable   2(local)   boolean
--------------------------------------------------------------------------------------------------------------
```

After parsing the main block (at line 20), you should output the symbol table with the following format.

```
==============================================================================================================
Name                             Kind       Level      Type             Attribute
--------------------------------------------------------------------------------------------------------------
a                                variable   1(local)   integer
--------------------------------------------------------------------------------------------------------------
```

After parsing the program's definition (at line 21), you should output the symbol table with the following format.

```
==============================================================================================================
Name                             Kind       Level      Type             Attribute
--------------------------------------------------------------------------------------------------------------
test                             program    0(global)  void
func                             function   0(global)  boolean          integer, real [1][2]
--------------------------------------------------------------------------------------------------------------
```

#### Note that your parser should dump the symbol table to `stdout`.

## Semantic Definition

This section describes only the semantic definitions. When your parser encounters a semantic error, the parser should report an error with relevant error messages and format, which are described in [error-message.md](./error-message.md).

Note that **once your parser has found a semantic error in a child node of an AST node, the parser doesn't check semantic errors related to the child node of the AST node.**

### Program Unit

The two program units are the *program* and the *function*.

#### Program

- The identifier after the **end** of a program declaration must be the same as the name given at the beginning of the declaration. Besides, it must be the same as the file name. For example, for the input file "test.p", the identifier at the beginning and the end of the program declaration must be "test".

- A program has no return value, thus any return statement that appeared in the main block of the program is illegal.

#### Function

- The identifier after the **end** of a function declaration must be the same as the name given at the beginning of the declaration.

- The type of the return statement inside the function must be the same as the return type of the function declaration.

### Scope Rules

- Scope rules are similar to C.

- Name must be unique within a given scope. Within the inner scope, the identifier designates the entity declared in the inner scope; the entity declared in the outer scope is hidden within the inner scope.

- A compound statement forms an inner scope. Note that declarations inside a compound statement are local to the statements in the block and no longer exist after the block is exited.

- A counting iterative control statement has a variable, called the **loop variable**, in which the count value is maintained. The loop variable is implicitly declared at the **for** statement and implicitly undeclared after loop termination. As a result, there is a scope in the loop with **only one symbol of loop var kind**.

- Unlike the normal variable, the symbol of a loop variable **can not** be redeclared whether it's in the same scope or the inner scope.

### Variable Declaration and Reference

- In an array declaration, the index of the lower bound must be smaller than that of the upper bound. Both of the indices must be greater than or equal to zero; actually, a non-conforming input was already blocked according to the syntactic definition.

- If there is an error in the array declaration, further checking is unnecessary when visiting the Variable Reference Node which is a reference to that array.

- Each index of an array reference must be of the integer type. Further checking regarding the array reference is unnecessary if an incorrect index was found within the array reference. The order of index checking is from left to right. Bound checking is not performed at compile time as in C language.

- An over array subscript is not allowed, that is, the number of indices of an array reference cannot be greater than the number of dimensions in the declaration.

### Expression

- For an arithmetic operator (+, -, *, or /), the operands must be an integer or real type, and the operation produces an integer or real value. The type of operands of operation may be different. Check out the *Type Coercion and Comparison* subsection for more details.

- For a **mod** operator, the operands must be an integer type, and it produces an integer value.

- For a Boolean operator (**and**, **or**, or **not**), the operands must be Boolean types, and the operation produces only Boolean value.

- For a relational operator (**<**, **<=**, **=**, **>=**, **>**, or **<>**), the operands must be an integer or real type, and the operation produces only Boolean value. Operands must be of the same type after appropriate type coercion.

- String operands can only appear in "+" operations (string concatenations), assignment statements, print statements and read statements. Notice that when doing string concatenation, both operands must be a string type.

### Type Coercion and Comparison

- An integer type can be implicit converted into a real type due to several situations, such as assignments, parameter passing, or arithmetic expressions.

- The result of an arithmetic operation will be real type if at least one of the operands is the real type. For example, `1.2 + 1`, `3 - 1.2`, and `1.2 * 3.4` are all result in real type.

- Two arrays are considered to be the same type if they have the same number of elements. More specifically, they have the same number of dimensions and the same size for each dimension and the type of element is the same.

### Statement

There are 7 distinct kinds of statements: compound, simple, conditional, while, for, return, and function call.

#### Simple

- Variable references of **print** or **read** statements must be scalar type.

- In assignment statements, the type of the left-hand side must be the same as that of the right-hand side unless type coercion is permitted.

- Assignment to constant and array assignment are not allowed.

#### If and While

- The conditional expression part of **if** and **while** statements must be Boolean types.

#### For

- The value of the loop variable can not be changed inside the loop.

- In a loop scope, the loop variable must be different from any other variable declaration including the nested loop variable.

- The **loop parameters** used to compute an iteration count must be in the incremental order and greater than or equal to zero; actually, a non-conforming form of the latter rule was already blocked according to the syntactic definition.

#### Return

- Check the definitions about return value in Sections [Program](#program) and [Function](#function).

#### Function Call

- A procedure is a function that has no return value.

- The number of actual parameters must be the same as the number of formal parameters in the function declaration.

- The types of actual parameters must be identical to the types of formal parameters in the function declaration.

### Identifier

- The first 32 characters are significant. That is, the additional part of an identifier will be discarded by the parser.

## What Should Your Parser Do?

If the input file is syntactically and semantically correct, output the following message.

```
|---------------------------------------------|
|  There is no syntactic and semantic error!  |
|---------------------------------------------|
```

Once the parser encounters a semantic error, output the related error message.

Notice that semantic errors should **not** cause the parser to stop its execution. You should let the parser keep working on finding semantic errors as much as possible.

## Project Structure

- `README.md`
- /src
	- Makefile
	- `scanner.l`
	- `parser.y`
	- /include
		- /AST
		- /semantic
		- /visitor
	- /src
		- /AST
		- /semantic
		- /visitor
	- Other modules you may add
- /report
	- `README.md`

In this assignment, you have to do the following tasks:

- Revise `parser.y` and add some modules (e.g., `SymbolTable.[hc]`, `SemanticAnalyzer.[hc]`) to perform a semantic analysis.
- Write a report in `report/README.md`. The report should at least describe the changes you have made in `parser.y` and the abilities of your AST.

If you want to preview your report in GitHub style markdown before pushing to GitHub, [`grip`](https://github.com/joeyespo/grip) might be the tool you need.

## Submitting the Assignment

You should push all your commits to the designated repository (hw4-\<Name of your GitHub account\>) under the compiler-f19 GitHub organization by the deadline (given in the very beginning of this assignment description).
At any point, you may save your work and push commits to your repository. You **must** commit your final version to the **master branch**, and we will grade the commit which is last pushed on your master branch. The **push time** of that commit will be your submission time, so you should not push any commits to the master branch after the deadline if you have finished your assignment; otherwise, you will get a late penalty.

Note that the penalty for late homework is **15% per day** (weekends count as 1 day). Late homework will not be accepted after sample codes have been posted.

In addition, homework assignments **must be individual work**. If we detect what we consider to be intentional plagiarism in any assignment, the assignment will receive reduced or, usually, **zero credit**.
