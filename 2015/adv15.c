#include <stdio.h>


typedef struct {
    int cap, dura, flav, text, calo;
} ingrediente;
                            // compila e executa ./main < input
ingrediente lista[4] = {};

int max( int a, int b ) {
    return ( a > b ? a : b );
}

int main(){
    char s[20];
    int i = 0;
    while ( scanf( "%s %s %d, %s %d, %s %d, %s %d, %s %d",
            s, s, &(lista[i].cap),
               s, &(lista[i].dura),
               s, &(lista[i].flav),
               s, &(lista[i].text),
               s, &(lista[i].calo)) == 11 ) i++;

    int Lidos = i;
    printf("Eu li %d\n", Lidos);

    /*
    i = 0;
    while ( i < Lidos ) {
      printf( "Ingred %d: %d, %d, %d, %d, %d\n", i,
        lista[i].cap, lista[i].dura, lista[i].flav, lista[i].text, lista[i].calo);
      i++;
    } */

    int best = -1;
    int c1, c2, c3, c4;
    for( c1 = 0; c1 <= 100; c1++ )
        for( c2 = 0; c2 <= 100-c1; c2++ )
            for( c3 = 0; c3 <= 100-c1-c2; c3++ ) {
                c4 = 100 - c1 - c2 - c3;
                int atualcap  = c1 * lista[0].cap  + c2 * lista[1].cap  + c3 * lista[2].cap  + c4 * lista[3].cap;
                int atualdura = c1 * lista[0].dura + c2 * lista[1].dura + c3 * lista[2].dura + c4 * lista[3].dura;
                int atualflav = c1 * lista[0].flav + c2 * lista[1].flav + c3 * lista[2].flav + c4 * lista[3].flav;
                int atualtext = c1 * lista[0].text + c2 * lista[1].text + c3 * lista[2].text + c4 * lista[3].text;
                int atualcalo = c1 * lista[0].calo + c2 * lista[1].calo + c3 * lista[2].calo + c4 * lista[3].calo;
                if( atualcalo != 500 ) continue;

                atualcap = max(0, atualcap);
                atualdura = max(0, atualdura);
                atualflav = max(0, atualflav);
                atualtext = max(0, atualtext);

  //              printf("JB gosta de cookies");

                long int atual = atualcap * atualdura * atualflav * atualtext;

                if ( atual > best  ) {
                   best = atual;
                }
            }

    printf( "%d\n", best );
    return 0;
}
