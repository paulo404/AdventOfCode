#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

typedef enum { MORTO = '.', VIVO = '#' } Bug;

Bug get(Bug m[5][5], int y, int x) {
  if ( y < 0 || y >= 5 || x < 0 || x >= 5) return MORTO;
  return m[y][x];
}

void imprimemat(Bug mat[5][5] ){
	for(int i = 0; i < 5; i++){
		for( int j = 0; j < 5; j++)
			printf("%c", mat[i][j]);
		printf("\n");
	}
	printf("\n");
}

int calc_rating(Bug mat[5][5]){
  int soma = 0;
  int pot2 = 1;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++) {
      if(mat[i][j] == VIVO)
        soma += pot2;
      pot2 *= 2;
    }
  }
  return soma;
}

int have_seen(int val, int bio_ratings[MAX_SIZE], int size){
  for(int i = 0; i< size; i++)
    if(val == bio_ratings[i]) return 1;
  return 0;
}

int main(void) {

  Bug mat[5][5] = {};
  int bio_ratings[MAX_SIZE];
  int bio_size = 0;

  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; )  {
      char ch;
      scanf("%c", &ch );
      switch ( ch ) {
        case VIVO:
        case MORTO: mat[i][j++] = ch;
      }
    }

  imprimemat(mat);
	int seen = 0;
	while(!seen) {
    Bug new_mat[5][5] = {};

    imprimemat(mat);

		//simulate
		for(int i = 0; i < 5; i++)
			for(int j = 0; j < 5; j++) {
				int neigh = 0;
				neigh += (get(mat,i-1,j) == VIVO)? 1 : 0;
				neigh += (get(mat,i+1,j) == VIVO)? 1 : 0;
				neigh += (get(mat,i,j-1) == VIVO)? 1 : 0;
				neigh += (get(mat,i,j+1) == VIVO)? 1 : 0;

				if ( mat[i][j] == VIVO && neigh != 1) new_mat[i][j] = MORTO;
				else if ( mat[i][j] == MORTO && (neigh == 1 || neigh == 2) ) new_mat[i][j] = VIVO;
				else new_mat[i][j] = mat[i][j];
			}

		memcpy(mat, new_mat, 5 * 5 * sizeof(Bug));

    int rating = calc_rating(new_mat);
    if(have_seen(rating, bio_ratings, bio_size)){
        printf( "rating = %d\n", rating );
        imprimemat(mat);
        break;
    }
    bio_ratings[bio_size] = rating;
    bio_size ++;

	}

  return 0;
}
