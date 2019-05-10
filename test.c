#include "source/matrixlib.h"
#include "source/linearlib.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	int l, c;
	int i;
	int AMOUNT;
	scanf("%d", &AMOUNT);
	struct matrix* m = malloc(sizeof(struct matrix) * AMOUNT), MT, TM;
	prog PROG;
	
	for(i = 0; i < AMOUNT; i++) {
		scanf("%d %d", &l, &c);
		m[i] = newMatrix(l,c,1);
	}		
	
	for(i = 0; i < AMOUNT; i++) {
		printf("%c :\n", 'A' + i);
		printMatrix(m[i]);
		putchar('\n');
		
		MT = cloneMatrix(m[i]);
		TM = cloneMatrix(MT);
		PROG=scaleAndReduce(MT);
		exportProg(&PROG,"P");
		printf("\n");
		exec(TM,&PROG);
		printf("Reduzida de %c:\n", 'A' + i);
		printMatrix(MT);
		putchar('\n');
		printf("Resultado da repetição do programa em %c:\n", 'A' + i);
		printMatrix(TM);
		putchar('\n'); 
	}
	
	/*printf("A: l1 -> l1*-2: \n");
	linePlace(MT, 0, lineMultiply(MT, 0, -2));
	printMatrix(MT);
	putchar('\n');
	
	printf("A: l2 -> l1+l2: \n");
	lineSum(MT, 1, 0, 1, 1);
	printMatrix(MT);
	putchar('\n');
	
	printf("A: l1 -> l1*1.5: \n");
	linePlace(MT, 0, lineMultiply(MT, 0, 1.5));
	printMatrix(MT);
	putchar('\n');
	
	printf("A: l3 -> l1+l3: \n");
	lineSum(MT, 2, 0, 1, 1);
	printMatrix(MT);
	putchar('\n');
	
	putchar('\n');*/
	
	for(i = 0; i < AMOUNT; i++) {
		freeMatrix(m[i]);
	}
	free(m);
	
	return 0;
}
