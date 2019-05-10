# linear-algebra
A simple c library for basic operations with matrices.

---

This library provides the following functions and types:

### Types & Structs

* ```struct matrix```
. A simple matrix.
. Contains:
-- ```int l``` = Height (lines)
-- ```int c``` = Breadth (collumns)
-- ```double* mem``` = The matrix data itself

* ```struct _prog / type prog```
. A sequence of operations to be done with a matrix.
. Contains:
-- ```char* p``` = The program itself (binary string)
-- ```int len``` = Length of the program
. A default ```prog```

### Functions

{TODO: Document everything else}

* ```int addToProg(prog* _p, char* pr, int len)```
. Appends the binary string ```char* pr``` to ```prog _p```. Returns the length of the program.
* ```int addIntToProg(prog* _p,int a)```
. Appends the ```sizeof(int)```-sized value ```int a``` to ```prog _p```, treating it as a byte array. Returns the length of the program.
* ```int addDoubleToProg(prog* _p,double a)```
. Appends the ```sizeof(double)```-sized value ```double a``` to ```prog _p```, treating it as a byte array. Returns the length of the program.
* ```void exec(struct matrix m,prog* _p)```
. Performs the operations specified in ```*_p``` in the matrix ```struct matrix m```.
* ```exportProg(prog *_p,char* n)```
. Saves ```prog *_p``` to a file named ```*(char* n)```.
