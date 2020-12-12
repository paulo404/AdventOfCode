#include <stdio.h>
#include <string.h>

typedef enum { MORTO = '.', VIVO = '#', ESCADA_BAIXO = '?', ESCADA_CIMA = 'C' } Bug;

Bug get(Bug m[5][5][500], int y, int x, int k) {
  if ( y < 0 || y >= 5 || x < 0 || x >= 5) return ESCADA_CIMA;
  return m[y][x][k];
}

int sumLine( Bug m[5][5][500], int i, int k ) {
  int sum = 0;
  for ( int j = 0; j < 5; j++ )
    sum += ( m[i][j][k] == VIVO )? 1 : 0;
  return sum;
}

int sumColumn( Bug m[5][5][500], int j, int k ) {
  int sum = 0;
  for ( int i = 0; i < 5; i++ )
    sum += ( m[i][j][k] == VIVO )? 1 : 0;
  return sum;
}
/* JB
int get_neigh(Bug m[5][5][500], int i, int j, int k, int disp_i, int disp_j) {
  int novo_i = i + disp_i;
  int novo_j = j + disp_j;

  // Vamos na ESCADA_BAIXO
  int aqui = 0, i1 = 0, i2 = 4, j1 = 0, j2 = 4;
  if ( i == 3 && j == 2 && disp_i == -1 ) { i1 = 4; aqui = 1; } // return get( m, 4, 0...4, k-1 ) // Caso R
  if ( i == 1 && j == 2 && disp_i ==  1 ) { i2 = 0; aqui = 1; } // return get( m, 0, 0...4, k-1 ) // Caso H
  if ( i == 2 && j == 1 && disp_j ==  1 ) { j2 = 0; aqui = 1; } // return get( m, 0...4, 0, k-1 ) // Caso L
  if ( i == 2 && j == 3 && disp_j == -1 ) { j1 = 4; aqui = 1; } // return get( m, 0...4, 4, k-1 ) // Caso N

  if ( aqui == 1 ) {
    int res = 0;
    for( i = i1; i <= i2; i++ )
      for( j = j1; j <= j2; j++ )
        res += ( get( m, i, j, k-1) == VIVO ? 1 : 0 );
    return res;
  }

  // Vamos na ESCADA_CIMA
  if ( novo_i < 0 ) return get( m, 1, 2, k+1 ) == VIVO ? 1 : 0;
  if ( novo_i > 4 ) return get( m, 3, 2, k+1 ) == VIVO ? 1 : 0;
  if ( novo_j < 0 ) return get( m, 2, 1, k+1 ) == VIVO ? 1 : 0;
  if ( novo_j > 4 ) return get( m, 2, 3, k+1 ) == VIVO ? 1 : 0;

  return get( m, novo_i, novo_j, k) == VIVO ? 1 : 0;
}
*/

int get_neigh(Bug m[5][5][500], int i, int j, int k, int disp_i, int disp_j) {
  int neigh = 0;

  int new_i = i + disp_i;
  int new_j = j + disp_j;

  //fell into the middle, must check prev k
  if ( get(m, new_i, new_j, k) == ESCADA_BAIXO ) {
    //sum outter line or column
    if ( disp_i )
      neigh += sumLine( m, i - disp_i, k - 1 );
    else
      neigh += sumColumn( m, j - disp_j, k - 1 );
  }
  //outer grid
  else if ( get(m, new_i, new_j, k) == ESCADA_CIMA ) {
    //get upper neighbor (must be located in the middle of line or column)
    if ( disp_i )
      neigh = ( get(m, i - disp_i, 2, k + 1 ) == VIVO )? 1 : 0;
    else
      neigh = ( get(m, 2, j - disp_j, k + 1 ) == VIVO )? 1 : 0;
  }
  //normal square
  else {
    neigh = ( get(m, new_i, new_j, k ) == VIVO )? 1 : 0;
  }

  return neigh;
}

void imprimemat(Bug mat[5][5][500], int k ){
	for(int i = 0; i < 5; i++){
		for( int j = 0; j < 5; j++)
			printf("%c", mat[i][j][k]);
		printf("\n");
	}
	printf("\n");
}

int main(void) {

  Bug mat[5][5][500] = {};

  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++)
      for(int k = 0; k < 500; k++) {
        //middle is escada
        if ( i == 2 && j == 2 )
          mat[i][j][k] = ESCADA_BAIXO;
        else
          mat[i][j][k] = MORTO;
      }

  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; )  {
      char ch;
      scanf("%c", &ch );

      //middle is escada
      if ( i == 2 && j == 2 ) ch = ESCADA_BAIXO;

      switch ( ch ) {
      case ESCADA_BAIXO:
      case VIVO:
      case MORTO: mat[i][j++][250] = ch; break;
      }
    }


  //imprimemat(mat);
	for ( int epochs = 0; epochs < 200; epochs++ ){
    Bug new_mat[5][5][500] = {};

    //imprimemat(mat);



		//simulate
		for(int i = 0; i < 5; i++) //line
			for(int j = 0; j < 5; j++) //column
				for(int k = 0; k < 500; k++) { //depth

					int neigh = 0;
					neigh += get_neigh(mat,i,j,k, -1, 0);
					neigh += get_neigh(mat,i,j,k, +1, 0);
					neigh += get_neigh(mat,i,j,k, 0, -1);
					neigh += get_neigh(mat,i,j,k, 0, +1);

					if ( mat[i][j][k] == VIVO && neigh != 1) new_mat[i][j][k] = MORTO;
					else if ( mat[i][j][k] == MORTO && (neigh == 1 || neigh == 2) ) new_mat[i][j][k] = VIVO;
					else new_mat[i][j][k] = mat[i][j][k];
				}

		memcpy(mat, new_mat, 500 * 5 * 5 * sizeof(Bug));

    printf("epoch %d\n", epochs);
    for (int a = +5; a >= -5; a--)
      imprimemat(mat,250+a);
    printf("-----------------------------\n");
	}

  //count bugs
  int c = 0;
  for(int i = 0; i < 5; i++) //line
    for(int j = 0; j < 5; j++) //column
      for(int k = 0; k < 500; k++)  //depth
        c += ( get(mat, i, j, k) == VIVO )? 1 : 0;
  printf( "%d\n", c );

  return 0;
}
