#include <stdio.h>
#define MAX 6

char recipes[50000000] = {3, 7};

int found( char *n, int pos ){
    int len = MAX-1;
    int pos2 = pos;
    while( len + 1 ) {
        if ( n[len] - '0' != recipes[pos2] ) return 0;
        len--;
        pos2--;
    }
    return 1;
}

int main() {
    char n[MAX] = "077201";
//	scanf("%s", n);

	int num_r = 2;
	int pos1 = 0, pos2 = 1;
	while(1) {
		int proxima_recipe = recipes[pos1] + recipes[pos2];

		if(proxima_recipe >= 10)
			recipes[num_r++] = 1;
		recipes[num_r++] = proxima_recipe % 10;

		pos1 = (pos1 + recipes[pos1] + 1) % num_r;
		pos2 = (pos2 + recipes[pos2] + 1) % num_r;

		if(found(n, num_r-1)) break;
		if(found(n, num_r-2)){
            num_r--;
            break;
        }
	}

	printf("%d\n\a", num_r - MAX );
	return 0;
}
