# Semantic Error

When your parser encounters a semantic error, it should report the error with corresponding error message defined below.

The format of a semantic error:

```
<Error> Found in line x, column y: <error message>
    <source code>
    <notation>
```

- \<error message>: specific error message corresponding to the semantic error.
- \<source code>: source code of the semantic error.
- \<notation>: character "``^``" which points to the position of the error.

**Table of Contents**
- [Abstract Syntactic Definitions](#abstract-syntactic-definitions)
	- [Error Detection](#error-detection)
		- [Symbol Table](#symbol-table)
		- [Program Node](#program-node)
		- [Function Node](#function-node)
		- [Variable Node](#variable-node)
		- [Variable Reference Node](#variable-reference-node)
		- [Binary Operator Node](#binary-operator-node)
		- [Unary Operator Node](#unary-operator-node)
		- [Return Node](#return-node)
		- [Assignment Node](#assignment-node)
		- [Print Node](#print-node)
		- [Read Node](#read-node)
		- [If Node](#if-node)
		- [While Node](#while-node)
		- [For Node](#for-node)
		- [Function Call Node](#function-call-node)

## Error Detection

The following subsections describe what semantics should be checked for each AST node or the symbol table and the corresponding error messages. Each check inside a node should be performed in the order as described.

### Symbol Table

- Symbol redeclared.

	```
	<Error> Found in line x, column y: symbol 'a' is redeclared
	    var a;
	        ^
	```

### Program Node

- Program name should be the same as the input file name.

	```
	<Error> Found in line x, column y: program name must be the same as filename
	    test;
	    ^
	```

- The identifier after the **end** of a program declaration must be the same as the name given at the beginning of the declaration.

	```
	<Error> Found in line x, column y: identifier at the end of program must be the same as identifier at the beginning of program
	    end tesy
	        ^
	```

### Function Node

- The identifier after the **end** of a function declaration must be the same as the name given at the beginning of the declaration.

	```
	<Error> Found in line x, column y: identifier at the end of function must be the same as identifier at the beginning of function
	    end tesy
	        ^
	```

### Variable Node

- In an array declaration, the index of the lower bound must be smaller than that of the upper bound. Both of the indices must be greater than or equal to zero; actually, a non-conforming input was already blocked according to the syntactic definition.

	```
	<Error> Found in line x, column y: 'arr' declared as an array with a lower bound greater or equal to upper bound
	    var arr: array 55146 to 80 of integer;
	        ^
	```

### Variable Reference Node

- Identifier should be in the symbol table.

	```
	<Error> Found in line x, column y: use of undeclared identifier 'a'
	    read a;
	         ^
	```

- Each index of array references must be an integer.

	```
	<Error> Found in line x, column y: index of array reference must be an integer
	    read a["SSLAB"];
	           ^
	```

- An over array subscript is not allowed.

	```
	<Error> Found in line 10, column 13: there is an over array subscript
	    return (b[1][4][1] >= 1.0);
	            ^
	```

### Binary Operator Node

- Errors related to binary operation. (check out [Expression](./README.md#expression))

	```
	<Error> Found in line x, column y: invalid operands to binary operation '+' ('string' and 'integer')
	    a := b + c;
	           ^
	```

### Unary Operator Node

- Errors related to unary operation. (check out [Expression](./README.md#expression))

	```
	<Error> Found in line x, column y: invalid operand to unary operation 'not' ('string')
	    a := not "SSLAB";
	         ^
	```

### Return Node

- The program and procedure should not have return value.

	```
	<Error> Found in line x, column y: program/procedure should not return a value
	    return 10;
	    ^
	```

- The type of the return value inside the function must be the same as the return type of the function declaration.

	```
	<Error> Found in line x, column y: return 'string' from a function with return type 'real'
	    return "SSLAB";
	           ^
	```

### Assignment Node

- Constant variable can not be assigned.

	```
	<Error> Found in line x, column y: cannot assign to variable 'a' which is a constant
	    a := 10;
	    ^
	```

- The value of the loop variable cannot be changed inside the loop.

	```
	<Error> Found in line x, column y: the value of loop variable cannot be modified inside the loop
	    i := 10;
	    ^
	```

- Array assignment is not allowed. (**prior to the type consistency check**)

	```
	<Error> Found in line x, column y: array assignment is not allowed
	    arr1 := a2;
	    ^

	<Error> Found in line x, column y: array assignment is not allowed
	    a1 := arr2;
	          ^
	```

- In assignment statements, the type of the left-hand side must be the same as that of the right-hand side unless type coercion is permitted.

	```
	<Error> Found in line x, column y: assigning to 'int' from incompatible type 'string'
	    int := stringgg;
	           ^
	```

### Print Node

- Variable reference in the print statement must be scalar type.

	```
	<Error> Found in line x, column y: variable reference of print statement must be scalar type
	    print a[1];
	          ^
	```

### Read Node

- Variable reference in the read statement cannot be a constant variable reference.

	```
	<Error> Found in line x, column y: variable reference of read statement cannot be a constant variable reference
	    read c;
	         ^
	```

- The value of the loop variable cannot be changed inside the loop.

	```
	<Error> Found in line x, column y: the value of loop variable cannot be modified inside the loop
	    read i;
	         ^
	```

- Variable reference in the read statement must be scalar type.

	```
	<Error> Found in line x, column y: variable reference of read statement must be scalar type
	    read a[1];
	         ^
	```

### If Node and While Node

- The conditional expression part of if and while statements must be Boolean type.

	```
	<Error> Found in line x, column y: the expression of condition must be boolean type
	    if a + 10 then
	         ^
	```

### For Node

- The loop parameters used to compute an iteration count must be in the incremental order and greater than or equal to zero.

	```
	<Error> Found in line x, column y: the lower bound of iteration count must be smaller than or equal to the upper bound
	    for idx := 10 to 1 do
	    ^
	```

### Function Call Node

- Identifier should be in the symbol table.

	```
	<Error> Found in line x, column y: used of undeclared function 'func1'
	    func1(10);
	    ^
	```

- The number of the actual parameters must be identical to the number of the formal parameters in the function declaration.

	```
	<Error> Found in line x, column y: too few/much arguments to function invocation
	    func1();
	    ^
	```

- The types of the actual parameters must be identical to the types of the formal parameters in the function declaration.

	```
	<Error> Found in line x, column y: incompatible types passing 'integer' to parameter of type 'boolean'
	    func1(10);
	          ^
	```
