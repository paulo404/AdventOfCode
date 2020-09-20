#include <stdio.h>

char recipes[2000000] = {3, 7};

int main() {
	scanf("%d", &n);
	int num_r = 2;
	int pos1 = 0, pos2 = 1;

	for( int i = 0; i < n + 10; i++ ) {
		int proxima_recipe = recipes[pos1] + recipes[pos2];

		if(proxima_recipe >= 10)
			recipes[num_r++] = 1;
		recipes[num_r++] = proxima_recipe % 10;

		pos1 = (pos1 + recipes[pos1] + 1) % num_r;
		pos2 = (pos2 + recipes[pos2] + 1) % num_r;
	}

	for( int i = n; i < n + 10; i++ ){
		printf("%d", recipes[i]);
	}
	printf("\n");


	return 0;
}
//880751
