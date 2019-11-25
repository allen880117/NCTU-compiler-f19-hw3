# Abstract Syntactic Definitions

We will give you the guidelines to construct an AST. You should define your own data structure that stores sufficient information in order to conform to the designated output format of the AST and to perform semantic analyses in the next assignment. Therefore, you are highly recommended to read the next assignment in advance to know what you will need.

Notice that the following guidelines intend to give you a sense of what an AST node looks like. Each guideline lists the fields that an AST node should have and shows the output format of the AST node. You may extend the fields of a node if necessary.

**Table of Contents**
- [Abstract Syntactic Definitions](#abstract-syntactic-definitions)
  - [Program Node](#program-node)
  - [Declaration Node](#declaration-node)
  - [Variable Node](#variable-node)
  - [Constant Value Node](#constant-value-node)
  - [Function Node](#function-node)
  - [Compound Statement Node](#compound-statement-node)
  - [Assignment Node](#assignment-node)
  - [Print Node](#print-node)
  - [Read Node](#read-node)
  - [Variable Reference Node](#variable-reference-node)
  - [Binary Operator Node](#binary-operator-node)
  - [Unary Operator Node](#unary-operator-node)
  - [If Node](#if-node)
  - [While Node](#while-node)
  - [For Node](#for-node)
  - [Return Node](#return-node)
  - [Function Call Node](#function-call-node)
  - [Nodes that are classified as statement nodes](#nodes-that-are-classified-as-statement-nodes)
  - [Nodes that are classified as expression nodes](#nodes-that-are-classified-as-expression-nodes)

## Program Node

A program node should have the following information:

- Location
	- Line and column numbers of the program name
- Name
- Return type
- Global variable and constant declarations
	- A list of declaration nodes (zero or more)
- Function declarations
	- A list of function nodes (zero or more)
- Body
	- A compound statement node
- Location
	- Line and column numbers of the program name after keyword `end`
- End name

**Output Format**

```C#
program <line: <line_number>, col: <col_number>> <program_name> void
  <zero or more outputs of declaration node>
  <zero or more outputs of function node>
  <output of compound statement node>
```

**Sample Output**

```C#
program <line: 1, col: 1> test void
  compound statement <line: 6, col: 1>
```

## Declaration Node

A declaration node should have the following information:

- Location
	- Line and column numbers of keyword `var`
- Variables
	- A list of variable nodes

There is at least one variable node in a declaration node.

**Output Format**

```C#
declaration <line: <line_number>, col: <col_number>>
  <zero or more outputs of (constant) variable node>
```

**Sample Output**

```C#
declaration <line: 10, col: 1>
  variable <line: 10, col: 5> b1 integer
    constant <line: 10, col: 10> 10
```

## Variable Node

A variable node should have the following information:

- Location
	- Line and column numbers of the variable name
- Name
- Type
- Constant value (zero or one)
	- A constant value node

A variable node represents a normal variable or a constant variable.

**Output Format**

```C#
variable <line: <line_number>, col: <col_number>> <variable_name> <type>
  <optional output of constant value node>
```

**Sample Output**

```C#
variable <line: 6, col: 5> a1 integer
```

## Constant Value Node

A constant value node should have the following information:

- Location
	- Line and column numbers of the constant value
- Constant value

**Output Format**

```C#
constant <line: <line_number>, col: <col_number>> <constant_value>
```

**Sample Output**

```C#
constant <line: 10, col: 10> 10
```

## Function Node

A function node should have the following information:

- Location
	- Line and column numbers of the function name
- Name
- Parameters
	- A list of declaration nodes (zero or more)
- Return type
- Body
	- A compound statement node
- Location
	- Line and column numbers of the function name after keyword `end`
- End name

**Output Format**

```C#
function declaration <line: <line_number>, col: <col_number>> <function_name> <function_prototype>
  <zero or more outputs of declaration node>
  <output of compound statement node>
```

**Sample Output**

```C#
function declaration <line: 26, col: 1> func5 void (integer, string)
  declaration <line: 26, col: 7>
    variable <line: 26, col: 7> b integer
    variable <line: 26, col: 10> c string
  compound statement <line: 27, col: 1>
```

## Compound Statement Node

A compound statement node should have the following information:

- Location
	- Line and column numbers of keyword `begin`
- Local variable and constant declarations
	- A list of declaration nodes (zero or more)
- Statements
	- A list of statement nodes (zero or more)

**Output Format**

```C#
compound statement <line: <line_number>, col: <col_number>>
  <zero or more outputs of declaration node>
  <zero or more outputs of statement node>
```

**Sample Output**

```C#
compound statement <line: 21, col: 1>
  declaration <line: 22, col: 5>
    variable <line: 22, col: 9> a integer[515...3500]
  print statement <line: 23, col: 5>
    variable reference <line: 23, col: 11> a
    [
      constant <line: 23, col: 13> 30
    ]
  print statement <line: 24, col: 5>
    constant <line: 24, col: 11> "dagakotowaru"
```

## Assignment Node

An assignment node should have the following information:

- Location
	- Line and column numbers of ':='
- Lvalue
	- A variable reference node
- Expression
	- An expression node:

**Output Format**

```C#
assignment statement<line: <line_number>, col: <col_number>>
  <output of variable reference node>
  <output of expression node>
```

**Sample Output**

```C#
assignment statement <line: 15, col: 7>
  variable reference <line: 15, col: 5> b
  constant <line: 15, col: 10> false
```

## Print Node

A print node should have the following information:

- Location
	- Line and column numbers of keyword `print`
- Target
	- An expression node

**Output Format**

```C#
print statement <line: <line_number>, col: <col_number>>
  <output of expression node>
```

**Sample Output**

```C#
print statement <line: 24, col: 5>
  constant <line: 24, col: 11> "dagakotowaru"
```

## Read Node

A read node should have the following information:

- Location
	- Line and column numbers of keyword `read`
- Target
	- A variable reference node

**Output Format**

```C#
read statement <line: <line_number>, col: <col_number>>
  <output of variable reference node>
```

**Sample Output**

```C#
read statement <line: 27, col: 5>
  variable reference <line: 27, col: 10> a
  [
    constant <line: 27, col: 12> 35
  ]
```

## Variable Reference Node

A variable reference node should have the following information:

- Location
	- Line and column numbers of the variable name
- Name
- Indices
	- A list of expression nodes

**Output Format**

```C#
variable reference <line: <line_number>, col: <col_number>> <variable_name>
<zero or more outputs of array subscript>

// array subscript
[
  <output of expression node>
]
```

**Sample Output**

```C#
variable reference <line: 27, col: 10> a
[
  constant <line: 27, col: 12> 35
]
```

## Binary Operator Node

A binary operator node should have the following information:

- Location
	- Line and column numbers of the operator
- Operator
- Left operand
	- An expression node
- Right operand
	- An expression node

**Output Format**

```C#
binary operator <line: <line_number>, col: <col_number>> <operator>
  <output of expression node>
  <output of expression node>
```

**Sample Output**

```C#
binary operator <line: 19, col: 14> <>
  constant <line: 19, col: 11> 10
  constant <line: 19, col: 17> 4
```

## Unary Operator Node

A unary operator node should have the following information:

- Location
	- Line and column numbers of the operator
- Operator
- Operand
	- An expression node

**Output Format**

```C#
unary operator <line: <line_number>, col: <col_number>> <operator>
  <output of expression node>
```

**Sample Output**

```C#
unary operator <line: 20, col: 11> not
  constant <line: 20, col: 15> true
```

## If Node

An if node should have the following information:

- Location
	- Line and column numbers of keyword `if`
- Condition
	- An expression node
- Body
	- A list of statement nodes (zero or more)
- Body of else
	- A list of statement nodes (zero or more)

**Output Format**

```C#
if statement <line: <line_number>, col: <col_number>>
  <output of expression node>
  <zero or more outputs of statement node>
```

or

```C#
if statement <line: <line_number>, col: <col_number>>
  <output of expression node>
  <zero or more outputs of statement node>
else
  <zero or more outputs of statement node>
```

**Sample Output**

```C#
if statement <line: 11, col: 3>
  binary operator <line: 11, col: 9> >
    constant <line: 11, col: 7> 1
    constant <line: 11, col: 11> 0
  print statement <line: 12, col: 5>
    constant <line: 12, col: 11> true
else
  print statement <line: 14, col: 5>
    constant <line: 14, col: 11> false
```

## While Node

A while node should have the following information:

- Location
	- Line and column numbers of keyword `while`
- Condition
	- An expression node
- Body
	- A list of statement nodes (zero or more)

**Output Format**

```C#
while statement <line: <line_number>, col: <col_number>>
  <output of expression node>
  <zero or more outputs of statement node>
```

**Sample Output**

```C#
while statement <line: 23, col: 3>
  binary operator <line: 23, col: 17> <
    variable reference <line: 23, col: 9> counter
    constant <line: 23, col: 19> 10
  print statement <line: 24, col: 5>
    constant <line: 24, col: 11> "Taiwan No.1\n"
```

## For Node

A for node should have the following information:

- Location
	- Line and column numbers of keyword `for`
- Loop variable declaration
	- A declaration node
- Initial statement
	- An assignment node
- Condition
	- An expression node
- Body
	- A list of statement nodes (zero or more)

**Output Format**

```C#
for statement <line: <line_number>, col: <col_number>>
  <output of declaration node>
  <output of assignment node>
  <output of expression node>
  <zero or more outputs of statement node>
```

**Sample Output**

```C#
for statement <line: 28, col: 3>
  declaration <line: 28, col: 7>
    variable <line: 28, col: 7> idx integer
  assignment statement <line: 28, col: 11>
    variable reference <line: 28, col: 7> idx
    constant <line: 28, col: 14> 0
  constant <line: 28, col: 19> 10
  compound statement <line: 29, col: 5>
    declaration <line: 30, col: 7>
      variable <line: 30, col: 11> idx integer
        constant <line: 30, col: 16> 10
    print statement <line: 31, col: 7>
      constant <line: 31, col: 13> "ISA (Ideology State Automaton)\n"
```

## Return Node

A return node should have the following information:

- Location
	- Line and column numbers of keyword `return`
- Return value
	- An expression node

**Output Format**

```C#
return statement <line: <line_number>, col: <col_number>>
  <output of expression node>
```

**Sample Output**

```C#
return statement <line: 38, col: 3>
  constant <line: 38, col: 10> 11
```

## Function Call Node

A function call node should have the following information:

- Location
	- Line and column numbers of the function name
- Name
- Arguments
	- A list of expression nodes (zero or more)

**Output Format**

```C#
function call statement <line: <line_number>, col: <col_number>> <function_name>
  <zero or more outputs of expression node>
```

**Sample Output**

```C#
function call statement <line: 17, col: 3> call
  constant <line: 17, col: 8> 20
  constant <line: 17, col: 12> 30
```

## Nodes that are classified as statement nodes

- Compound statement node
- Assignment node
- Print node
- Read node
- If node
- While node
- For node
- Return node
- Function call node

## Nodes that are classified as expression nodes

- Binary operator node
- Unary operator node
- Constant value node
- Variable reference node
- Function call node
