#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef struct {
  int armor, damage, hp;
} personagem;

typedef struct {
  int armor, damage, cost;
} item;

int roundsAteRIP( personagem p, int ataque_oponente ) {
	int dano_real = ataque_oponente - p.armor;
	return dano_real > 0 ? ceil( p.hp / (double) dano_real ) : p.hp;
}

int battle(personagem player, personagem enemy){
  int rounds_player = roundsAteRIP(enemy, player.damage);
  int rounds_enemy = roundsAteRIP(player, enemy.damage);
  return rounds_player <= rounds_enemy;
}

int main(void) {
  personagem enemy;
  personagem player = {0, 0, 100};

  printf("hp, damage, armor\n");
  scanf("%d %d %d", &(enemy.hp), &(enemy.damage), &(enemy.armor) );

  item weapons[5] = {{0,4,8}, {0,5,10}, {0,6,25}, {0,7,40}, {0,8,74}};
  item armours[6] = {{0,0,0}, {1,0,13}, {2,0,31}, {3,0,53}, {4,0,75}, {5,0,102}};
  item rings[7]   = {{0,0,0}, {0,1,25}, {0,2,50}, {0,3,100}, {1,0,20}, {2,0,40}, {3,0,80}};

  int maior = INT_MIN;
  int total_cost;

  for(int i = 0; i < 5; i++){ //weapon
    for(int j = 0; j < 6; j++){ //armor
      for(int k = 0; k < 7; k++){  //ring 1
        for(int l = 0; l < 7; l++){ //ring 2

          if(l==k && k!=0) continue;

          item w = weapons[i]; //weapon
          item a = armours[j]; //armor
          item r1 = rings[k];  //ring1
          item r2 = rings[l];  //ring2
          player.armor = a.armor + r1.armor + r2.armor;
          player.damage = w.damage + r1.damage + r2.damage;
          total_cost = w.cost + a.cost + r1.cost + r2.cost;
          if ( !battle ( player,enemy ) ) {
            if ( total_cost > maior ) maior = total_cost;
          }

        }
      }
    }
  }

  printf("%d\n", maior);
  return 0;
}
