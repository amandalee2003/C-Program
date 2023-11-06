#include <math.h>
#include "mathlib.h"
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "ascSCTl"
double my_ab(double x){
    double absolute_value=x;
    if(x<0){
        absolute_value=-1*x;
    }else{
        absolute_value=1*x;
    }return absolute_value;
    }
int main(int argc, char **argv) {
    int opt=0;
    int a_flag=0;
    int s_flag=0;
    int c_flag=0;
    int S_flag=0;
    int C_flag=0;
    int T_flag=0;
    int l_flag=0;
    while((opt=getopt(argc,argv,OPTIONS)) !=-1){
        switch(opt){
	    case 'a':
		a_flag += 1;
		if (a_flag>1){
		    break;
		}
            case 's':
		if(s_flag==0){
         	    printf("  x          sin          Library          Difference\n");
        	    printf("  -          ------       -------          ----------\n");
        	    for(double x=0.05*M_PI; x<=1.95*M_PI; x+=0.05*M_PI){
	                double difference = my_ab(my_sin(x)-sin(x));
                        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_sin(x), sin(x), difference);
               }}
		s_flag +=1;
		if(a_flag == 0){
	            break;
		}
            case 'c':
		if(c_flag==0){
        	    printf("  x            cos            Library            Difference\n");
                    printf("  -            ------         -------            ----------\n");
                    for(double x=0.05*M_PI; x<=1.95*M_PI; x+=0.05*M_PI){
                        double difference = my_ab(my_cos(x)-cos(x));
                        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_cos(x), cos(x), difference);
		}}
		c_flag += 1;
		if(a_flag == 0){
                    break;
                }
            case 'S':
		if (S_flag ==0){
                    printf("  x          arcsin          Library          Difference\n");
                    printf("  -          ------          -------          ----------\n");
                    for(double x=-1.0; x<=0.95; x+=0.05){
                        double difference = my_ab(my_arcsin(x)-asin(x));
                        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_arcsin(x), asin(x), difference);
		}}
		S_flag+=1;
	        if(a_flag == 0){
                    break;
                }
            case 'C':
		if(C_flag==0){
                    printf("  x          arccos          Library          Difference\n");
                    printf("  -          ------          -------          ----------\n");
                    for(double x=-1.0; x<=0.95; x+=0.05){
                        double difference = my_ab(my_arccos(x)-acos(x));
                        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_arccos(x), acos(x), difference);
		}}
		C_flag+=1;
		if(a_flag == 0){
                    break;
		}
            case 'T':
		if(T_flag==0){
                    printf("  x          arctan          Library          Difference\n");
                    printf("  -          ------          -------          ----------\n");
                    for(double x=1.0; x<=10.0; x+=0.05){
                        double difference = my_ab(my_arctan(x)-atan(x));
                        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_arctan(x), atan(x), difference);
		}}
		T_flag +=1;
		if(a_flag == 0){
                    break;
                }
            case 'l':
		if(l_flag==0){
                    printf("  x          log          Library          Difference\n");
                    printf("  -          ------       -------          ----------\n");
                    for(double x=1.0; x<=10.0; x+=0.05){
                        double difference = my_ab(my_log(x)-log(x));
                        printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", x, my_log(x), log(x), difference);
		}}
		l_flag+=1;
		 if(a_flag == 0){
                    break;
                }
	}}
     return 0;
    }    
