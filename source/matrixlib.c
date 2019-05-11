#include "matrixlib.h"
#include <stdio.h>
#include <stdlib.h>

matrix newMatrix(int l, int c, int read) {
	matrix m;
	m.l = l;
	m.c = c;
	allocMatrix(&m);
	if (read) readMatrix(m);
	return m;
}

void allocMatrix(matrix *m) {
	if (m->l) {
		(*m).mem = malloc((*m).l*(*m).c*sizeof(double));
	}
}

void readMatrix(matrix m) {
	if (m.l) {
		int i=0, lc=m.l*m.c;
		while (i<lc && scanf("%lf", m.mem + (i++)));
	}
}

void printMatrix(matrix m) {
	if (!m.l) {
		printf("INVALID MATRIX\n");
	} else {
		int i=0, lc=m.l*m.c;
		while (i<lc && printf("%2.2lf", m.mem[i]) && putchar(++i % m.c == 0 ? '\n':'\t'));
	}
}

void freeMatrix(matrix m) {
	free(m.mem);
}

matrix cloneMatrix(matrix m) {
	return multiplyMatrix(m, 1);
}

matrix multiplyMatrix(matrix a, double k) {
	matrix m;
	if (a.l) {
		m = newMatrix(a.l, a.c, 0);
		int i, lc=a.l*a.c;
		for (i=0; i<lc; i++){
			m.mem[i] = k*a.mem[i];
		}
	} else {
		m.l = 0;
	}
	return m;
}

matrix addMatrix(matrix a, matrix b) {
	matrix m;
	if (a.l == b.l && a.c == b.c){
		m = newMatrix(a.l, a.c, 0);
		int i, lc=a.l*a.c;
		for (i=0; i<lc; i++) {
			m.mem[i] = a.mem[i] + b.mem[i];
		}
	} else {
		m.l = 0;
	}
	return m;
}

matrix productMatrix(matrix a, matrix b) {
	matrix P;
	if (a.c == b.l){
		int m = a.l, n = b.c, t = a.c;
		P = newMatrix(m, n, 0);
		int x, k, i, j;
		for (k=0; k<m*n; k++) {
			P.mem[k] = 0;
			i = k/n;
			j = k%n;
			for (x=0; x<t; x++) {
				P.mem[k] += a.mem[i*n + x] * b.mem[x*n + j];
			}
		}
	} else {
		P.l = 0;
	}
	return P;
}

matrix transposeMatrix(matrix a) {
	matrix m;
	if (a.l) {
		m = newMatrix(a.c, a.l, 0);
		int x, lc=a.l*a.c;
		int i, j;
		for (x=0; x<lc; x++){
			i = x/a.l;
			j = x%a.l;
			m.mem[x] = a.mem[j*a.c + i];
		}
	} else {
		m.l = 0;
	}
	return m;
}

double getElement(matrix m, int i, int j) {
	return m.mem[i*m.c + j];
}