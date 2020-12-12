#include <stdio.h>
#include <math.h>

int somaDosDivisores( int n ) {
  if (n == 1) return 1;
  int acc = 0;
  for (int i = 1; i <= (n/2); ++i) {
    if (n % i == 0) {
      // printf("%d %d %d\n", n, acc, i);
      acc += i;
    }
  }
  acc += n;
  return acc;
}

int main(){
  int n; // fiz minha parte :)
  scanf("%d", &n);
  int casa = 1;
  while ( 1 ) {
    int presentes = somaDosDivisores(casa)*10;
    if(casa<11) printf("%d: %d\n", casa, presentes);
    if ( presentes >= n ) {
      printf("%d\n", casa);
      break;
    }
    casa++;
  }
  return 0;

}
