#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define MAX_CARS 20

typedef enum { NORTE = '^', SUL = 'v', LESTE = '>', OESTE = '<'} Direcao;

Direcao clockwise(Direcao d) {
  if ( d == NORTE) return LESTE;
  if ( d == LESTE) return SUL;
  if ( d == SUL)   return OESTE;
  if ( d == OESTE) return NORTE;
  printf("Mamae, eu nao devia estar aqui!\n");
}

Direcao counterclockwise(Direcao d) {
  if ( d == NORTE) return OESTE;
  if ( d == LESTE) return NORTE;
  if ( d == SUL)   return LESTE;
  if ( d == OESTE) return SUL;
  printf("Mamae, eu nao devia estar aqui!\n");
}

typedef struct {
   	int lin, col;
    char direction;
    int memory; // 1° -> esquerda || 2° -> reto || 3° direita || repetir
    int crash;
} relampago_mcqueen;

int compCarro (const void *m , const void *t) {

  relampago_mcqueen *marquinhos = ( relampago_mcqueen * ) m;
  relampago_mcqueen *tomate = ( relampago_mcqueen * ) t;
  if (marquinhos->lin < tomate->lin) return -1;
  if (marquinhos->lin > tomate->lin) return +1;
  if (marquinhos->col < tomate->col) return -1;
  if (marquinhos->col > tomate->col) return +1;
  return 0;
}

int crashou ( int lin, int col, relampago_mcqueen carros[], int n_carros) {
  for (int i = 0; i < lin; i++)
    for(int j = 0; j < col; j++) {
      int qtd_carros = 0;
      int index = 0;
      for( int k = 0; k < n_carros; k++){
        if ( carros[k].crash ) continue;
        if (carros[k].lin == i && carros[k].col == j) {
          index = k;
          qtd_carros++;
        }
      }
      if ( qtd_carros >= 2) {
        //marcar crashou como true
        for( int l = 0; l < n_carros; l++)
          if (carros[l].lin == i && carros[l].col == j) {
            carros[l].crash = 1;
          }

        //printf("lin=%d, col=%d\n", j, i );
        return 1;
      }
    }
  return 0;
}

void printation( char m[MAX][MAX], int lin, int col, relampago_mcqueen carros[], int n_carros) {
  printf("\033[H");
  for (int i = 0; i < lin; i++)
    for(int j = 0; j < col; j++) {
      int qtd_carros = 0;
      int index = 0;
      for( int k = 0; k < n_carros; k++)
        if (carros[k].lin == i && carros[k].col == j) {
          if(carros[k].crash == 1) continue;
          index = k;
          qtd_carros++;
        }
      if ( qtd_carros >= 2) { printf("X"); }
      else if ( qtd_carros == 1) printf("%c", carros[index].direction);
      else if ( qtd_carros == 0) printf("%c",m[i][j] );
    }
  puts("\n");
}

int main(void) {

	char m[MAX][MAX]= {};
	int lin = 0;
  int col = 0;
	while ( fgets( & m[lin][0], MAX, stdin ) != NULL ) {
    int size = strlen(m[lin]);
    col = (size > col) ? size : col;
		lin++;
  }

	relampago_mcqueen carros[MAX_CARS];

  int cars = 0;
  for ( int i = 0; i < lin; i++ )
    for ( int j = 0; j < col; j++)
	  	switch( m[i][j] ){
            case NORTE :
            case SUL :
            case LESTE :
            case OESTE :
            carros[cars].direction = m[i][j];
            if( m[i][j] == NORTE || m[i][j] == SUL ) m[i][j] = '|';
            else m[i][j] = '-';
            carros[cars].lin = i;
            carros[cars].col = j;
            carros[cars].memory = 0;
            carros[cars].crash = 0;
            cars++;
        }
  int crashes = 0;

	printf( "%d\a cars\n", cars);
  printf("\033[2J\033[?25l");

  int katchau = 1;
	while ( katchau ) {
		//simulate
    qsort( carros, cars, sizeof(relampago_mcqueen), &compCarro);

    // printation(m,lin,col,carros,cars);
    for( int i = 0; i < cars; i++) {
      //printf("[lin=%d, col=%d]\n", carros[i].lin, carros[i].col);
      relampago_mcqueen *atual = carros + i;

      if ( atual->crash ) continue;

      //mover o carro
      switch(atual->direction) {
        case NORTE: (atual->lin)--; break;
        case SUL: (atual->lin)++; break;
        case OESTE: (atual->col)--; break;
        case LESTE: (atual->col)++; break;
      }

      //faz a curva
      switch(m[atual->lin][atual->col]) {
        case '/':
          if(atual->direction == NORTE || atual->direction == SUL) atual->direction = clockwise(atual->direction);
          else atual->direction = counterclockwise(atual->direction);
          break;
        case '\\':
          if(atual->direction == NORTE || atual->direction == SUL)  atual->direction = counterclockwise(atual->direction);
          else atual->direction = clockwise(atual->direction);
          break;
        //curvas intersection
        case '+':   // 1° -> esquerda || 2° -> reto || 3° direita || repetir
          if( (atual->memory) == 0 ) atual->direction = counterclockwise(atual->direction);
          if( (atual->memory) == 2 ) atual->direction = clockwise(atual->direction);
          if( (atual->memory) == 2 ) atual->memory = 0;
          else atual->memory++;
          break;
      }

      //ver se crashou
      if (crashou(lin,col,carros,cars)) crashes++;
      if(crashes == (int)cars/2) {
        katchau= 0;
      }

    }
	}

  printation(m,lin,col,carros,cars);
  for( int bab = 0; bab < cars; bab++)
    if( carros[bab].crash == 0 ) printf("lin %d, col %d\n", carros[bab].lin, carros[bab].col);

  return 0;
}
