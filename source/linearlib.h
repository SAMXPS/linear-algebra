#ifndef LINEARLIB_H
#define LINEARLIB_H
#include "matrixlib.h"
#define maxuint (~(unsigned int)0x0)-(1<<((sizeof(unsigned int))*8)-1)
#define doubles (sizeof(double))
#define ints (sizeof(int))

struct _prog
{
	char* p;
	int len;
};
typedef struct _prog prog;
extern prog prog_p; //Prorotype program (used for initializing)

int getLeadPos(struct matrix m, int line); // j of the first non-zero element in the line or -1 if all zeros
int* getLeads(struct matrix m);

void exportProg(prog *_p,char* n);
int addToProg(prog* _p,char* pr,int len);
int addIntToProg(prog* _p,int a);
int addDoubleToProg(prog* _p,double a);
void exec(struct matrix m,prog* _p);

double* lineAlloc(int size);
double* lineMultiply(struct matrix m, int line, double k);
void linePlace(struct matrix m, int line, double* values);
void lineSwap(struct matrix m, int line1, int line2);
void lineSum(struct matrix m, int lineA, int lineB, double kA, double kB); // lineSum: A -> kA*A + kB*B

prog sortByLeads(struct matrix m);

prog scaleAndReduce(struct matrix m);
#endif