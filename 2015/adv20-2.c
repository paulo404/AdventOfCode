#include <stdio.h>

#define MAX 1000000

int vet[MAX] = {};

int main(){
  int n;
  scanf("%d", &n);

  int elf = 1;
  while ( 1 ) {
     int tmp = elf;
     int pls_break = 0;
     for(int i=1; i<= 50; i++) {
         if ( (tmp >= MAX) ) break;
         vet[tmp] += elf*11;
         if(vet[tmp] >= n){
            printf("%d\n", tmp);
            pls_break = 1;
            break;
         }
         tmp += elf;
     }
     if(pls_break) break;
     elf++;
  }
  return 0;
}
