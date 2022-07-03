# BrainHeck
Just the casual brainfuck but improved

# Concept
It should be able to be compiled into standalone executable file<br/>
And have compiler functions, that are not user-defined.

#### Functions
Any function is defined by compiler and starts with \ symbol.<br/>
Basic functions:<br/>
```
\h   - Display help about functions (should be used in the interpreter only)
\d   - Print the current pointer value as decimal number
\n   - Print the current pointer position
\q   - Exit the program
\\   - No-op, if you want to use \ symbol in comments about code so desperately
\s() - Run some system command, like \s(clear) will clear the screen
\p() - Print message, like \p(Hello world) is a basic hello world in brainHeck
\q() - Exit program with exit code, like \q(60) will exit the program with exit code 60. Non-number value like \q(abc) should produce a critical error.
\j() - Jump to pointer value, like \j(2) will jump to pointer at index 2 (3rd position in array)
\f() - Write the pointer value to file in append mode.
\a() - Delete file
\s() - Jump to char at index
\i() - Include contents of another file
```
For now, none of these functions are implemented.

#### Program array and pointer
Program array should not be of a fixed size. It should dynamically reallocate if necessary.<br/>
Pointer could be implemented in any way possible
