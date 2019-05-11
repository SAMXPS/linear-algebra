#ifndef MATRIXLIB_H
#define MATRIXLIB_H

struct _matrix {
	int l;			// number of lines
	int c;			// number of collums
	double *mem;	// pointer to the values in memory
};

typedef struct _matrix matrix;

matrix newMatrix(int l, int c, int read);
void allocMatrix(matrix *m);
void readMatrix(matrix m);
void printMatrix(matrix m);
void freeMatrix(matrix m);

matrix cloneMatrix(matrix m);
matrix multiplyMatrix(matrix a, double m);
matrix addMatrix(matrix a, matrix b);
matrix productMatrix(matrix a, matrix b);
matrix transposeMatrix(matrix a);

double getElement(matrix m, int i, int j);

#endif