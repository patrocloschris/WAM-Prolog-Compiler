# WAM Prolog Compiler/Interpreter

A basic Prolog compiler & interpreter to WAM machine code

# Description
That implementation is a basic compiler to wam machine code and interpreter of that output code.
As a first version work expecting only oneline of Prolog code(Program or Query) as input.

The main.c file is making the central management. Open and validate the input file. If all are right then calls the analyser which is looking for syntax errors. In case of a syntax error returns a error message and the execution stops, otherwise returns OK and continues to compiling precedure.
The compiler construct a dictionary which keeps information for every variable or fact. The compile is based on that dictionary, the depth and
kind of table it and if it is a program or query.
If no error message displayed then the user can execute the WAM interpreter of the output result.
Interpreter's expected result is Yes/No

# Requirements
 - Gcc (4+)

# Compile
`make`

# Execute a simple example
`./prologIC` use as input example.pl

