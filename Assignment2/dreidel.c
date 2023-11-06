#include <math.h>
#include "dreidel.h"
#include "mtrand.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int game = 1;
int coin_arr[] ={0, 0, 0, 0, 0, 0, 0, 0};
//int *coin_array = coin_arr;
char options_arr[] ={'G','H','N','S'};
//char *options_array = options_arr;
char *dreidel_name[] ={"Aharon", "Batsheva", "Chanah", "David", "Ephraim", "Faige", "Gamaliel", "Hannah"};

char spin_dreidel(void){
    uint64_t random_num = mtrand_rand64();
    int mod = random_num % 4;
    return (options_arr[mod]);
}

int play_game(int n_players, int coins_per_player, int * n_rounds){
    int index;
    int num_players = n_players;
    int central_pot = 0;
    int lost[n_players];
    for (int i= 0; i<n_players; i++){
	(coin_arr[i])=coins_per_player;
	lost[i] = 0;
    }while (game == 1){
	    *n_rounds += 1;
        for (int i = 0;i<n_players;i++){
            //char spin = spin_dreidel();
            if (coin_arr[i] >= 0){
		char spin = spin_dreidel();
                if (spin == 71){
                    (coin_arr[i]) += central_pot;
                    central_pot = 0;
                }if (spin == 72){
                    (coin_arr[i]) += (central_pot/2);
                    central_pot -= (central_pot/2);
                }if (spin == 83){
                    if (coin_arr[i]==0){
			coin_arr[i] -= 1;
                        num_players -= 1;
			lost[i] = 1;
                        if(v ==1){
                            printf("%s: eliminated in round %d of a %d player game.\n", dreidel_name[i], *n_rounds, n_players);
		    }}else{
                        (coin_arr[i]) -= 1;
                        central_pot += 1;
            }}if (num_players == 1){
                //index = i;
		for(int l=0; l<n_players; l++){
			if(lost[l]==0){
				index = l;
			}
		}
		game = 0;
		break;
        }}
	    if (num_players == 1){
                //index = i;
		for(int l=0; l<n_players; l++){
                        if(lost[l]==0){
                                index = l;
                        }
                }
		game = 0;
                break;
	}
	}}return index;
	}

