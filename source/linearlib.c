#include "linearlib.h"
#include <stdlib.h>
#include <stdio.h>

prog prog_p={{0},0};
//LinALang - A [Li]near [A]lgebra basic matrix operations specification [Lang]uage
/*
Format:
C1xyz...C2xyz...
C1,C2 = Commands
xyz... = Arguments

!!!Arguments are pure bytes!!!
###A program is a binary string###

Example:
Swapping lines 1 and 2 = {'S',0x01,0x02}
Adding Line 1*K1 and Line 2*k2 = {'A',1*(k1),2*(k2)}

*/

void exportProg(prog *_p,char* n) {
	FILE *out=fopen(n,"wb");
	fwrite((*_p).p,sizeof(char),(*_p).len,out);
	fclose(out);
}

int addToProg(prog* _p,char* pr,int len) {	
	int i,j;
	prog p=*_p;
	if(len==0)return p.len;
	char* np=malloc(p.len+len);
	for(i=0;i<p.len;i++)np[i]=p.p[i];
	j=i;
	for(i=0;i<len;i++)np[i+j]=pr[i];
	p.len+=len;
	p.p=np;
	*_p=p;
	return p.len;
}

int addIntToProg(prog* _p,int a) {
	int l=sizeof(a);
	char*buf=malloc(l);
	*(int*)&buf[0]=a;
	return addToProg(_p,buf,l);
}

int addDoubleToProg(prog* _p,double a) {
	int l=sizeof(a);
	char*buf=malloc(l);
	*(double*)&buf[0]=a;
	return addToProg(_p,buf,l);
}

void exec(matrix m,prog* _p) {
	unsigned int pc=0; //Program counter (like in assembly)
	prog p=*_p;
	while(pc<p.len) {
		switch(p.p[pc++]) {
			case 'S':
				lineSwap(m,*(int*)&p.p[pc],*(int*)&p.p[pc+ints]);
				pc+=2*ints;
				break;
			case 'A':
				lineSum(m,*(int*)&p.p[pc],*(int*)&p.p[pc+ints],*(double*)&p.p[pc+2*ints],*(double*)&p.p[pc+2*ints+doubles]);
				pc+=2*doubles+2*ints;
				break;
			case 'M':
				linePlace(m,*(int*)&p.p[pc],lineMultiply(m,*(int*)&p.p[pc],*(double*)&p.p[pc+ints]));
				pc+=doubles+ints;
				break;
			default:
				goto except;
				break;
		}
	}
	return;
	except:
	printf("Parsing Error on position 0x%.16x.",pc);
	return;
}

//Operations
int getLeadPos(matrix m, int line) {
	int j, k0 = line * m.c;
	for (j=0; j<m.c; j++) {
		if (m.mem[k0 + j] != 0) return j;
	}
	return -1;
}

int* getLeads(matrix m) {
	int *leads = malloc(m.l*sizeof(int)), i;
	for(i=0; i<m.l; i++){
		leads[i]=getLeadPos(m, i);
	}
	return leads;
}

double* lineAlloc(int size) {
	double *line = (double *) malloc(size * sizeof(double));
	return line;
}

double* lineMultiply(matrix m, int l, double k) {
	int x;
	double *line = lineAlloc(m.c);
	for (x=0; x<m.c; x++){
		line[x] = m.mem[l*m.c+x] * k;
	}
	return line;
}

void linePlace(matrix m, int l, double* values) {
	int x;
	for (x=0; x<m.c; x++){
		m.mem[l*m.c+x] = values[x];
	}
}

void lineSwap(matrix m, int line1, int line2) {
	double* vl1 = lineMultiply(m, line1, 1);
	double* vl2 = lineMultiply(m, line2, 1);
	linePlace(m, line1, vl2);
	linePlace(m, line2, vl1);
	free(vl1);
	free(vl2);
}

void lineSum(matrix m, int lineA, int lineB, double kA, double kB) {
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

prog sortByLeads(matrix m) {
	prog ret=prog_p;
	int* leads = getLeads(m);
	int x, y, tmp, size = m.l;

	for (x=0; x<size; x++){
		for(y=0; y<size-x-1; y++) {
			if(leads[y] < 0 || (leads[y] > leads[y+1] && leads[y+1] >= 0)){
				tmp = leads[y];
				leads[y] = leads[y+1];
				leads[y+1] = tmp;
				lineSwap(m, y, y+1);
				addToProg(&ret,"S",1);
				addIntToProg(&ret,y);
				addIntToProg(&ret,y+1);
			}
		}
	}
	
	free(leads);
	return ret;
}

prog normalizeLeads(matrix m) {
	prog ret=prog_p;
	int* leads = getLeads(m);
	int x, size = m.l;
	double val;

	for (x=0; x<size; x++){
		int lpos = leads[x];
		if (lpos >= 0) {
			val=(1.0/getElement(m, x, lpos));
			linePlace(m, x, lineMultiply(m, x, val));
			addToProg(&ret,"M",1);
			addIntToProg(&ret,x);
			addDoubleToProg(&ret,val);
		}
	}
	
	free(leads);
	return ret;
}

prog removeRepeatedLeads(matrix m, int col) {
	prog ret=prog_p;
	int* leads = getLeads(m);
	int x, size = m.l, firstlead = -1;
	double val;
	
	for (x=0; x<size; x++) {
		if(leads[x] == col) {
			if (firstlead == -1){
				firstlead = x;
			}
			else {
				lineSum(m, x, firstlead, 1, -1);
				addToProg(&ret,"A",1);
				addIntToProg(&ret,x);
				addIntToProg(&ret,firstlead);
				addDoubleToProg(&ret,1);
				addDoubleToProg(&ret,-1);
			}
		}
	}	
	if (col > 0) {
		for (x=0; x<firstlead; x++) {
			val=-1 * getElement(m, x, col);
			lineSum(m, x, firstlead, 1, val);
			addToProg(&ret,"A",1);
			addIntToProg(&ret,x);
			addIntToProg(&ret,firstlead);
			addDoubleToProg(&ret,1);
			addDoubleToProg(&ret,val);
		}
	}
	
	free(leads);
	return ret;
}

prog scaleAndReduce(matrix m) {
	prog ret=prog_p;
	prog temp;
	int x = 0, size = m.c;
	for(x = 0; x < size; x++) {
		temp=sortByLeads(m);
		addToProg(&ret,temp.p,temp.len);
		temp=normalizeLeads(m);
		addToProg(&ret,temp.p,temp.len);
		temp=removeRepeatedLeads(m, x);
		addToProg(&ret,temp.p,temp.len);
	}
	return ret;
}