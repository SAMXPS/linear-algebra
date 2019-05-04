#include "linearlib.h"
#include <stdlib.h>
#include <stdio.h>

int getLeadPos(struct matrix m, int line) {
	int j, k0 = line * m.c;
	for (j=0; j<m.c; j++) {
		if (m.mem[k0 + j] != 0) return j;
	}
	return -1;
}

int* getLeads(struct matrix m) {
	int *leads = malloc(m.l*sizeof(int)), i;
	for(i=0; i<m.l; i++){
		leads[i]=getLeadPos(m, i);
	}
	return leads;
}

double* lineAlloc(int size){
	double *line = (double *) malloc(size * sizeof(double));
	return line;
}

double* lineMultiply(struct matrix m, int l, double k) {
	int x;
	double *line = lineAlloc(m.c);
	for (x=0; x<m.c; x++){
		line[x] = m.mem[l*m.c+x] * k;
	}
	return line;
}

void linePlace(struct matrix m, int l, double* values) {
	int x;
	for (x=0; x<m.c; x++){
		m.mem[l*m.c+x] = values[x];
	}
}

void lineSwap(struct matrix m, int line1, int line2){
	double* vl1 = lineMultiply(m, line1, 1);
	double* vl2 = lineMultiply(m, line2, 1);
	linePlace(m, line1, vl2);
	linePlace(m, line2, vl1);
	free(vl1);
	free(vl2);
}

void lineSum(struct matrix m, int lineA, int lineB, double kA, double kB){
	double* vlA = lineMultiply(m, lineA, kA);
	double* vlB = lineMultiply(m, lineB, kB);
	double* vlN = lineAlloc(m.c);
	int x;
	
	for (x=0; x<m.c; x++){
		vlN[x] = vlA[x] + vlB[x];
	}
	
	linePlace(m, lineA, vlN);
	
	free(vlA);
	free(vlB);
	free(vlN);
} 

void sortByLeads(struct matrix m) {
	int* leads = getLeads(m);
	int x, y, tmp, size = m.l;

	for (x=0; x<size; x++){
		for(y=0; y<size-x-1; y++) {
			if(leads[y] < 0 || (leads[y] > leads[y+1] && leads[y+1] >= 0)){
				tmp = leads[y];
				leads[y] = leads[y+1];
				leads[y+1] = tmp;
				lineSwap(m, y, y+1);
			}
		}
	}
	
	free(leads);
}

void normalizeLeads(struct matrix m) {
	int* leads = getLeads(m);
	int x, size = m.l;

	for (x=0; x<size; x++){
		int lpos = leads[x];
		if (lpos >= 0) {
			linePlace(m, x, lineMultiply(m, x, 1.0/getElement(m, x, lpos)));
		}
	}
	
	free(leads);
}

void removeRepeatedLeads(struct matrix m, int col) {
	int* leads = getLeads(m);
	int x, size = m.l, firstlead = -1;
	
	for (x=0; x<size; x++) {
		if(leads[x] == col) {
			if (firstlead == -1){
				firstlead = x;
			}
			else {
				lineSum(m, x, firstlead, 1, -1);
			}
		}
	}	
	if (col > 0) {
		for (x=0; x<firstlead; x++) {
			lineSum(m, x, firstlead, 1, -1 * getElement(m, x, col));
		}
	}
	
	free(leads);
}

void scaleAndReduce(struct matrix m) {
	int x = 0, size = m.c;
	for(x = 0; x < size; x++) {
		sortByLeads(m);
		normalizeLeads(m);
		removeRepeatedLeads(m, x);
	}
}