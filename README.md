# BrainHeck
Just the casual brainfuck but improved<br/>
This code was tested with `gcc main.c` with gcc v12.1.0 running on windows 10<br/>
*More compiler info down there*

# Concept
It should be able to be compiled into standalone executable file<br/>
And have compiler functions, that are not user-defined.

#### Functions
Any function is defined by compiler and starts with \ symbol.<br/>
Basic functions:<br/>
```
\h   - Display help about functions (should be used in the interpreter only) [IMPLEMENTED]
\d   - Print the current pointer value as decimal number [IMPLEMENTED]
\n   - Print the current pointer position [IMPLEMENTED]
\q   - Exit the program [IMPLEMENTED]
\\   - No-op, if you want to use \ symbol in comments about code so desperately [IMPLEMENTED]
\s() - Run some system command, like \s(clear) will clear the screen [IMPLEMENTED]
\p() - Print message, like \p(Hello world) is a basic hello world in brainHeck [IMPLEMENTED]
\q() - Exit program with exit code, like \q(60) will exit the program with exit code 60. Non-number value like \q(abc) should produce a critical error. [IMPLEMENTED]
\j() - Jump to pointer value, like \j(2) will jump to pointer at index 2 (3rd position in array) [IMPLEMENTED]
\f() - Write the pointer value to file in append mode. [IMPLEMENTED]
\a() - Delete file [IMPLEMENTED]
\l() - Jump to char at index [IMPLEMENTED]
```
For now, all of these functions are implemented in the interpreter.<br/>
You are free to suggest any new features/functions, use the issues menu for that.

#### Program array and pointer
Program array should not be of a fixed size. It should dynamically reallocate if necessary.<br/>
Pointer could be implemented in any way possible

---

## Basic programs
#### Hello world
`\p(Hello world!)` - Using a brainHeck function `\p()`<br/>
`++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.` - In the plain old brainfuck<br/>
`++++++++++[>+++++++>++++++++++>+++<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.` - Another hello world in brainfuck(but this is 5 chars shorter)<br/>

---
## Compiler info
```Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=C:/mingw64/bin/../libexec/gcc/x86_64-w64-mingw32/12.1.0/lto-wrapper.exe
Target: x86_64-w64-mingw32
Configured with: ../../../src/gcc-12.1.0/configure --host=x86_64-w64-mingw32 --build=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --prefix=/mingw64 --with-sysroot=/c/buildroot/x86_64-1210-win32-sjlj-rt_v10-rev3/mingw64 --enable-host-shared --enable-targets=all --enable-multilib --enable-languages=c,c++,fortran,lto --enable-libstdcxx-time=yes --enable-threads=win32 --enable-libgomp --enable-libatomic --enable-lto --enable-graphite --enable-checking=release --enable-fully-dynamic-string --enable-version-specific-runtime-libs --enable-libstdcxx-filesystem-ts=yes --enable-sjlj-exceptions --disable-libstdcxx-pch --disable-libstdcxx-debug --enable-bootstrap --disable-rpath --disable-win32-registry --disable-nls --disable-werror --disable-symvers --with-gnu-as --with-gnu-ld --with-arch-32=i686 --with-arch-64=nocona --with-tune-32=generic --with-tune-64=core2 --with-libiconv --with-system-zlib --with-gmp=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-mpfr=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-mpc=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-isl=/c/buildroot/prerequisites/x86_64-w64-mingw32-static --with-pkgversion='x86_64-win32-sjlj-rev3, Built by MinGW-W64 project' --with-bugurl=https://sourceforge.net/projects/mingw-w64 CFLAGS='-O2 -pipe -fno-ident -I/c/buildroot/x86_64-1210-win32-sjlj-rt_v10-rev3/mingw64/opt/include -I/c/buildroot/prerequisites/x86_64-zlib-static/include -I/c/buildroot/prerequisites/x86_64-w64-mingw32-static/include' CXXFLAGS='-O2 -pipe -fno-ident -I/c/buildroot/x86_64-1210-win32-sjlj-rt_v10-rev3/mingw64/opt/include -I/c/buildroot/prerequisites/x86_64-zlib-static/include -I/c/buildroot/prerequisites/x86_64-w64-mingw32-static/include' CPPFLAGS=' -I/c/buildroot/x86_64-1210-win32-sjlj-rt_v10-rev3/mingw64/opt/include -I/c/buildroot/prerequisites/x86_64-zlib-static/include -I/c/buildroot/prerequisites/x86_64-w64-mingw32-static/include' LDFLAGS='-pipe -fno-ident -L/c/buildroot/x86_64-1210-win32-sjlj-rt_v10-rev3/mingw64/opt/lib -L/c/buildroot/prerequisites/x86_64-zlib-static/lib -L/c/buildroot/prerequisites/x86_64-w64-mingw32-static/lib ' LD_FOR_TARGET=/c/buildroot/x86_64-1210-win32-sjlj-rt_v10-rev3/mingw64/bin/ld.exe --with-boot-ldflags=' -Wl,--disable-dynamicbase -static-libstdc++ -static-libgcc'
Thread model: win32
Supported LTO compression algorithms: zlib
gcc version 12.1.0 (x86_64-win32-sjlj-rev3, Built by MinGW-W64 project)```
