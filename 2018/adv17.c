#include<stdio.h>
#include<unistd.h>
#include<limits.h>

#define MAX 20000
#define LINES_INPUT 1347
//#define LINES_INPUT 8

#define flowing 0
#define fill 1


int y_max = INT_MIN;
int y_min = INT_MAX;
int x_max = INT_MIN;
int x_min = INT_MAX;

int max( int a, int b ) {return ( a > b ? a : b );}
int min( int a, int b ) {return ( a < b ? a : b );}

char mat[MAX][MAX] = {};

void imprimemat(){
  printf("\033[H");
  for( int i = y_min; i <= y_max; i++ ){
    for( int j = x_min - 1; j <= x_max + 1; j++ ){
      if( mat[i][j] == '|'  ) printf( "\033[1;34;44m \033[0m" );
      else if( mat[i][j] == '~' ) printf( "\033[1;07;47m \033[0m" );
      else if( mat[i][j] == '#' ) printf( "\033[1;37;47m \033[0m" );
      else printf(" ");
      			//if( mat[i][j] != 0 ) printf("%c", mat[i][j]);
      			//else printf(".");
    }
    printf("\n");
    usleep(500);
  }
  printf("\n");
}					// x = col y = lin

void fillOut( int y, int x ) {
  if ( mat[y][x] != '|' ) return;
  mat[y][x] = '~';
  fillOut(y, x-1);
  fillOut(y, x+1);
}

//velocity to only call recursion to the flowing side, or both if v == 0
int aguinha( int y, int x , int v /*  velocity */ ) {
  if ( y > y_max ) return flowing;
  if( mat[y][x] == '|' ) return flowing;
  if( mat[y][x] != 0 ) return fill;
  mat[y][x] = '|';

  //imprimemat();

  // chama pra baixo
  int baixo = aguinha(y + 1, x, 0);

  int esquerda = fill;
  int direita = fill;

  // chama pros lados
  if ( baixo != flowing ) {
    if ( v < 1 ) esquerda = aguinha(y, x - 1, -1);
    if ( v > -1 ) direita = aguinha(y, x + 1, 1);

    if ( (esquerda & direita) == fill ) {
      if ( v == 0 ) fillOut(y,x);
      return fill;
    }
    else return flowing;
  }

  return baixo;
}


int main() {
  mat[0][500] = '+';

  //read input while getting max of y and x
  for( int i = 0; i < LINES_INPUT ; i++ ){
    char c, h;
    int x, y, aux;
    scanf( "%c=", &c );
    if( c == 'x' ) { //y variando
      scanf( "%d, %c=%d..%d\n", &x, &h, &y, &aux );

      x_max = max(x, x_max);
      x_min = min(x, x_min);

      y_max = max(y, y_max);
      y_max = max(aux, y_max);

      y_min = min(y, y_min);
      y_min = min(aux, y_min);

      for( ; y <= aux; y++ )
        mat[y][x] = '#';
    }
    else {  //x variando
      scanf( "%d, %c=%d..%d\n", &y, &h, &x, &aux );

      x_max = max(x, x_max);
      x_max = max(aux, x_max);

      x_min = min(x, x_min);
      x_min = min(aux, x_min);

      y_max = max(y, y_max);
      y_min = min(y, y_min);

      for( ; x <= aux; x++ )
        mat[y][x] = '#';
    }
  }
  printf("\033[2J");

  y_max=75;
  //simulate
  aguinha( 1, 500, 0 );

  imprimemat();

  //printf("ymin=%d\n", y_min);
  //printf("ymax=%d\n", y_max);
  //printf("xmin=%d\n", x_min);
  //printf("xmax=%d\n", x_max);

  //count water
  int agua = 0;
  for( int i = y_min; i <= y_max; i++ )
    for( int j = x_min - 1; j <= x_max + 1; j++) //can flow 1 more than the extremities
      //if( mat[i][j] == '|' || mat[i][j] == '~') agua++; //part1
      if( mat[i][j] == '~') agua++; //part2

  printf("agua = %d\n", agua );

  return 0;
}
