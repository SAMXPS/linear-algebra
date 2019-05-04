#ifndef LINEARLIB_H
#define LINEARLIB_H
#include "matrixlib.h"

int getLeadPos(struct matrix m, int line); // j of the first non-zero element in the line or -1 if all zeros
int* getLeads(struct matrix m);

double* lineAlloc(int size);
double* lineMultiply(struct matrix m, int line, double k);
void linePlace(struct matrix m, int line, double* values);
void lineSwap(struct matrix m, int line1, int line2);
void lineSum(struct matrix m, int lineA, int lineB, double kA, double kB); // lineSum: A -> kA*A + kB*B

void sortByLeads(struct matrix m);

void scaleAndReduce(struct matrix m);

#endif