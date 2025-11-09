# C-Compiler
Minimal C subset compiler in C / C++ with support for integer literals, variables, assignments, return statements, and arithmetic. Implemented lexing, parsing, AST generation, and x86-64 code-generation (Linux ABI).

## How to run:
1. Navigate to root folder and create build folder
```
  mkdir build
  cd build
  cmake .. 
```
2. Build the project with CMake
```
cmake --build . --config Release
```
3. Create your test folder or use the given test.c in root/tests/
4. Run compiler to create assembly output
```
cd ..
.\build\toycc_cpp.exe .\tests\test.c > test.s
```
5. Create executable
```
gcc -o test test.s
```
6. Run executable (may need to change permissions with chmod)
```
./test
```
