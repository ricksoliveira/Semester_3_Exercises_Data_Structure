#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int **p;
	int i, j, n = 3;
	
	p = (int**) malloc(n*sizeof(int*));
	
	for(i=0; i<n; i++){
		p[i] = (int*) malloc(n*sizeof(int));
	}
	
	printf("\n\n");
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d\t", i+j);
		}
		printf("\n\n");
	}
	
	for(i=0; i<n; i++){
		free(p[i]);
	}
	free(p);
		
}
