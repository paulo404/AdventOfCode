#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10       //mudar dps

typedef enum {slashing=0, cold=1, fire=2, radiation=3, bludgeoning=4}att_type;

typedef struct {
  int n, hp, att, init;
  att_type attack_type;
  int weak[5];
  int immune[5];
  int faccao, id_enemy, targeted, id;     // 1 immune 0 infecc
 } grupos;

int compTarget (const void *aa , const void *bb) {
  grupos *a = ( grupos * ) aa; //NOTE might be b - a
  grupos *b = ( grupos * ) bb;
  int comp =    b->n * b->att - a->n * a->att;
  if ( !comp ) comp = b->init - a->init;
  return comp;
}


int compFight (const void *aa , const void *bb) {
  grupos *a = ( grupos * ) aa; //NOTE might be b - a
  grupos *b = ( grupos * ) bb;
  return b->init - a->init;
}

//slashing=0, cold=1, fire=2, radiation=3, bludgeoning=4;
int main(){
  int n_infec = TAM; //NOTE change according to input
  int n_imunes = TAM; //NOTE change according to input
  int n_combined = n_infec + n_imunes;
  grupos combined[n_combined];

   //combined[0] = (grupos) {.n = 17, .hp = 5390, .att=4507, .init = 2, .attack_type = fire, .weak = {0,0,0,1,1}, .immune={},.faccao=1,.id_enemy = -1};
   //combined[1] = (grupos){.n=989, .hp=1274, .att=25, .init=3, .attack_type=slashing, .weak={1,0,0,0,1}, .immune={0,0,1,0,0},.faccao=1,.id_enemy = -1};
   //combined[2] = (grupos) {.n=801, .hp=4706, .att=116, .init=1, .attack_type=bludgeoning, .weak={0,0,0,1,0}, .immune={0,0,0,0,0},.faccao=0,.id_enemy = -1};
   //combined[3] = (grupos) {.n=4485, .hp=2961, .att=12, .init=4, .attack_type=slashing, .weak={0,1,1,0,0}, .immune={0,0,0,1,0},.faccao=0,.id_enemy = -1};

  // "input"
  combined[0]  = (grupos) {.n = 1117, .hp = 5042,  .att=44,   .init = 15, .attack_type = fire,        .weak = {1,0,0,0,0}, .immune={0,0,1,1,1}, .faccao=1, .id_enemy = -1};
  combined[1]  = (grupos) {.n = 292,  .hp = 2584,  .att=81,   .init = 18, .attack_type = bludgeoning, .weak = {0,0,0,0,0}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[2]  = (grupos) {.n = 2299, .hp = 8194,  .att=35,   .init = 7,  .attack_type = radiation,   .weak = {0,0,0,0,0}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[3]  = (grupos) {.n = 1646, .hp = 6315,  .att=37,   .init = 14, .attack_type = slashing,    .weak = {1,0,0,0,0}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[4]  = (grupos) {.n = 2313, .hp = 6792,  .att=29,   .init = 9,  .attack_type = bludgeoning, .weak = {0,0,1,1,0}, .immune={0,1,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[5]  = (grupos) {.n = 2045, .hp = 8634,  .att=36,   .init = 13, .attack_type = fire,        .weak = {0,0,0,1,0}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[6]  = (grupos) {.n = 34,   .hp = 1019,  .att=295,  .init = 6,  .attack_type = cold,        .weak = {0,0,0,0,1}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[7]  = (grupos) {.n = 157,  .hp = 6487,  .att=362,  .init = 3,  .attack_type = radiation,   .weak = {1,1,0,0,0}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[8]  = (grupos) {.n = 1106, .hp = 4504,  .att=39,   .init = 12, .attack_type = slashing,    .weak = {0,1,0,0,0}, .immune={0,0,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[9]  = (grupos) {.n = 5092, .hp = 8859,  .att=12,   .init = 16, .attack_type = radiation,   .weak = {0,0,0,0,0}, .immune={1,1,0,0,0}, .faccao=1, .id_enemy = -1};
  combined[10] = (grupos) {.n = 3490, .hp = 20941, .att=9,    .init = 5,  .attack_type = bludgeoning, .weak = {0,0,0,0,0}, .immune={0,0,1,0,0}, .faccao=0, .id_enemy = -1};
  combined[11] = (grupos) {.n = 566,  .hp = 11571, .att=40,   .init = 10, .attack_type = bludgeoning, .weak = {0,1,0,0,1}, .immune={0,0,0,0,0}, .faccao=0, .id_enemy = -1};
  combined[12] = (grupos) {.n = 356,  .hp = 30745, .att=147,  .init = 8,  .attack_type = slashing,    .weak = {0,0,0,1,0}, .immune={0,0,0,0,0}, .faccao=0, .id_enemy = -1};
  combined[13] = (grupos) {.n = 899,  .hp = 49131, .att=93,   .init = 19, .attack_type = cold,        .weak = {1,0,0,0,0}, .immune={0,0,1,1,1}, .faccao=0, .id_enemy = -1};
  combined[14] = (grupos) {.n = 1203, .hp = 27730, .att=43,   .init = 4,  .attack_type = slashing,    .weak = {0,1,0,0,0}, .immune={0,0,0,0,0}, .faccao=0, .id_enemy = -1};
  combined[15] = (grupos) {.n = 22,   .hp = 45002, .att=3748, .init = 17, .attack_type = bludgeoning, .weak = {0,0,0,0,1}, .immune={0,0,0,0,0}, .faccao=0, .id_enemy = -1};
  combined[16] = (grupos) {.n = 3028, .hp = 35744, .att=18,   .init = 11, .attack_type = fire,        .weak = {0,0,0,0,1}, .immune={0,0,0,0,0}, .faccao=0, .id_enemy = -1};
  combined[17] = (grupos) {.n = 778,  .hp = 17656, .att=35,   .init = 2,  .attack_type = bludgeoning, .weak = {0,0,1,0,0}, .immune={0,0,0,0,0}, .faccao=0, .id_enemy = -1};
  combined[18] = (grupos) {.n = 47,   .hp = 16006, .att=645,  .init = 20, .attack_type = cold,        .weak = {0,1,0,1,0}, .immune={0,0,0,0,1}, .faccao=0, .id_enemy = -1};
  combined[19] = (grupos) {.n = 4431, .hp = 13632, .att=6,    .init = 1,  .attack_type = bludgeoning, .weak = {0,0,1,0,0}, .immune={0,0,0,0,1}, .faccao=0, .id_enemy = -1};

  //atribuir ids
  int id;
  for( id = 0; id < 2*TAM; id++) combined[id].id = id;


  //FIGHT!
  while(1){
    int i;

    //stop when one of the sides is defeated
    int sum_imune = 0;
    int sum_infec = 0;
    for(i = 0; i < TAM*2; i ++){
      if ( combined[i].faccao )  //imune
        sum_imune += combined[i].n;
      else //infec
        sum_infec += combined[i].n;
    }
    if(sum_imune <= 0 || sum_infec <= 0) break;


    //É HORA DO DUELO
    printf("HORA DO DUELO\n");

    // Selecao dos targueti
    qsort(combined , n_combined, sizeof(grupos), &compTarget);

    for(i = 0; i < TAM*2; i++){
      grupos *atacante = &combined[i];
      grupos *to_attack = NULL;
      int max_damage = 0;

      if ( atacante->n <= 0) continue;

      for(int j = 0; j < 2*TAM; j++){
        grupos *candidato = &combined[j];
        if(candidato->targeted || candidato->faccao == atacante->faccao || candidato->n <= 0 )
          continue;

        int curr_damage = atacante->att * atacante->n;
        if(candidato->immune[atacante->attack_type]) curr_damage = 0;
        else if( candidato->weak[atacante->attack_type]) curr_damage *= 2;

        if(curr_damage > max_damage){
          max_damage = curr_damage;
          to_attack = candidato;
        }
      }

      if (to_attack != NULL) {
        atacante->id_enemy = to_attack->id;
        to_attack->targeted = 1;
      }
      printf("Atacante id %d setou id enemy %d como alvo\n", atacante->id, atacante->id_enemy);
    }

    //fase de ataque
    qsort(combined , n_combined, sizeof(grupos), &compFight);

    for( int i = 0; i < n_combined; i++ ) {
      grupos *atacante = &combined[i];
      grupos *atacado = NULL;

      //nao tenho alvo passo a vez
      if ( atacante->id_enemy == -1 ) continue;

      //pesquisa pelo meu inimigo
      for(int j =0; j < n_combined; j++){
        if(atacante->id_enemy == combined[j].id){
          atacado = &combined[j];
          break;
        }
      }

      if (atacado != NULL) {
        int damage = atacante->n * atacante->att;
        if(atacado->weak[atacante->attack_type]) damage *=2;
        else if(atacado->immune[atacante->attack_type]) damage =0;

        int new_n = atacado->n - (int) damage/atacado->hp;
        atacado->n = (new_n < 0)? 0 : new_n;

        char imune[] = "imune";
        char infec[] = "infec";
        char fac_att[10];
        if ( atacante->faccao) memcpy(fac_att, imune,6);
        else memcpy(fac_att, infec,6);
        char fac_hit[10];
        if ( atacante->faccao) memcpy(fac_hit,infec,6);
        else memcpy(fac_hit, imune,6);

        printf( "%s %d atacando %s %d com %d de dano, matei %d!\n", fac_att, atacante->id, fac_hit, atacado->id, damage, (int) damage/atacado->hp);
      }
    }
    printf("\n\nNova rodada:\n");
    for(int i = 0; i < 2*TAM; i++){
      grupos v = combined[i];
      if (v.faccao) printf("Imune %d : %d units\n", v.id, v.n);
      else printf("Infect %d : %d units\n", v.id, v.n);

    }
    printf("-----------------------\n");

    //reseta flags          ---- quais mais? ----
    for( i = 0; i < 2*TAM; i++ ){
      combined[i].targeted = 0;
      combined[i].id_enemy = -1;
    }
  }
  return 0;

}
