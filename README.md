# C-Compiler
Minimal C subset compiler in C++ with support for integer literals, variables, assignments, return statements, and arithmetic. Implemented lexing, parsing, AST generation, and x86-64 code-generation (Linux ABI).

## How to run:
1. Must install CMake to run
2. Navigate to root folder and create build folder
```
  mkdir build
  cd build
  cmake .. 
```
3. Build the project with CMake
```
cmake --build . --config Release
```
4. Create your test folder or use the given test.c in root/tests/
5. Run compiler to create assembly output
```
cd ..
./build/bin/Release/CCompiler_CPP.exe ./test/test.c > test.s
```
6. Create executable
```
gcc -o cprogram test.s
```
7. Run executable (may need to change permissions with chmod)
```
./cprogram
```
8. View return value
```
echo $?
```
