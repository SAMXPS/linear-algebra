#include "matrixlib.h"
#include <stdio.h>
#include <stdlib.h>

struct matrix newMatrix(int l, int c, int read) {
	struct matrix m;
	m.l = l;
	m.c = c;
	allocMatrix(&m);
	if (read) readMatrix(m);
	return m;
}

void allocMatrix(struct matrix *m) {
	if (m->l) {
		(*m).mem = malloc((*m).l*(*m).c*sizeof(double));
	}
}

void readMatrix(struct matrix m) {
	if (m.l) {
		int i=0, lc=m.l*m.c;
		while (i<lc && scanf("%lf", m.mem + (i++)));
	}
}

void printMatrix(struct matrix m) {
	if (!m.l) {
		printf("INVALID MATRIX\n");
	} else {
		int i=0, lc=m.l*m.c;
		while (i<lc && printf("%2.2lf", m.mem[i]) && putchar(++i % m.c == 0 ? '\n':'\t'));
	}
}

void freeMatrix(struct matrix m) {
	free(m.mem);
}

struct matrix cloneMatrix(struct matrix m) {
	return multiplyMatrix(m, 1);
}

struct matrix multiplyMatrix(struct matrix a, double k) {
	struct matrix m;
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

struct matrix addMatrix(struct matrix a, struct matrix b){
	struct matrix m;
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

struct matrix productMatrix(struct matrix a, struct matrix b){
	struct matrix P;
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

struct matrix transposeMatrix(struct matrix a) {
	struct matrix m;
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

double getElement(struct matrix m, int i, int j){
	return m.mem[i*m.c + j];
}