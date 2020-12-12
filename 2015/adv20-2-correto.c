#include <stdio.h>

#define MAX 1000000

int vet[MAX] = {};

int main(){
  int n;
  scanf("%d", &n);

  int elf = 1;
  while ( elf < MAX ) {
     int tmp = elf;
     for(int i=1; i<= 50; i++) {
         if ( (tmp >= MAX) ) break;
         vet[tmp] += elf*11;
         tmp += elf;
     }
     elf++;
  }

  for(int i = 1; i < MAX; i++) {
      if(vet[i] >= n){
        printf("%d\n", i);
        break;
      }
  }


  return 0;
}
