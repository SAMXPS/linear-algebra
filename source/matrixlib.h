#ifndef MATRIXLIB_H
#define MATRIXLIB_H

struct matrix {
	int l;			// number of lines
	int c;			// number of colloms
	double *mem;	// pointer to the values in memory
};

struct matrix newMatrix(int l, int c, int read);
void allocMatrix(struct matrix *m);
void readMatrix(struct matrix m);
void printMatrix(struct matrix m);
void freeMatrix(struct matrix m);

struct matrix cloneMatrix(struct matrix m);
struct matrix multiplyMatrix(struct matrix a, double m);
struct matrix addMatrix(struct matrix a, struct matrix b);
struct matrix productMatrix(struct matrix a, struct matrix b);
struct matrix transposeMatrix(struct matrix a);

double getElement(struct matrix m, int i, int j);

#endif