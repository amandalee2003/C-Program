#include <math.h>
#include "dreidel.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "mtrand.h"
#include <stdlib.h>
#define OPTIONS "p:c:s:v"
int v=0;
int main(int argc, char **argv){
    int opt=0;
    int n_rounds = 0;
    int coins_per_player=3;
    int n_players=4;
    //int coins_per_player=3;
    int p;
    int c;
    char *name_arr[] ={"Aharon", "Batsheva", "Chanah", "David", "Ephraim", "Faige", "Gamaliel", "Hannah"};
    uint64_t s=613;
    mtrand_seed(s);
   // int n_seed=613;
   //int n_message="";
    while((opt=getopt(argc,argv,OPTIONS)) != -1){
	switch(opt){
	    case 'p':
		p = atoi(optarg);
		if (p>=2&&p<=8){
		    n_players=p;
		}else{
		    return 1;
		}break;
            case 'c': 
		c = atoi(optarg);
	        if (c>=1&&c<=20){
		    coins_per_player = c;
		}else{
		    return 1;
	        }break;	
	    case 's':
		s = strtoul(optarg, NULL, 10);
		if(s>0 && s<=9999999999){
		    mtrand_seed(s);
		}else{
		    return 1;
		}break;
	    case 'v':
		v =1;
		break;
		}}
    int index = play_game(n_players, coins_per_player, &n_rounds);
    printf("%s %d %d %d %lu\n", name_arr[index],n_players,coins_per_player,n_rounds, s);
    return 0;    
}
