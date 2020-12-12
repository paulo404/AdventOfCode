#include <stdio.h>

#define MAX 200
#define MAX_CARS 20

//tem que ser quadrado

typedef struct {
   	int lin, col;
    char direction;
    int memory; // 1° -> esquerda || 2° -> reto || 3° direita || repetir
    int movi;
} relampago_mcqueen;

int main(void) {
	char m[MAX][MAX]= {};

	int lin = 0;
	while ( fgets( & m[lin][0], MAX, stdin ) != NULL )
		lin++;

	relampago_mcqueen carros[MAX_CARS];

  int cars = 0;
  for ( int i = 0; i < lin; i++ )
    for ( int j = 0; j < lin; j++)
	  	switch( m[i][j] ){
            case '<' :
            case '>' :
            case '^' :
            case 'v' :
            carros[cars].lin = i;
            carros[cars].col = j;
            carros[cars].memory = 0;
            carros[cars].movi = 0;
            carros[cars].direction = m[i][j];
            cars++;
        }
	printf( "%d cars\n", cars);

  int katchau = 1;
	while ( katchau ) {
		//simulate
    for ( int l = 0; l < lin; l++) {
      for ( int c = 0; c < lin; c++) {
          switch( m[j][c] ){
            case '<' :
            case '>' :
            case '^' :
            case 'v' :
            //qual carro a gente leu?
            for (int carro = 0; carro < cars; carro++) {
              if ( carros[carro].lin == l && carros[carro].col == c && !carros[carro].movi ){
                        switch( carros[carro].direction ){
                            case '<' :

                            case '>' :

                            case '^' :

                            case 'v' :
                        }
                  carros[carro].movi = 1;
                  break;
              }


            }

          }
      }

    }

    }



	}
	//print pos collisao ( X )

  return 0;
}
