#include <math.h>
#define EPSILON 1e-10
double Exp(double x){
    double t=1.0;
    double y=1.0;
    for(double k=1.0; t>EPSILON; k+=1.0){
	t*=x/k;
	y+=t;
    }
    return y;
}
double my_abs(double x){
    double absolute_value=x;
    if(x<0){
        absolute_value=-1*x;
    }else{
	absolute_value=1*x;
    }return absolute_value;
    }
double my_power(double first,double second){
    double power=1,x;
    for(x=1;x<=second;++x){
	power=power*first;
    }return power;
    }
double my_squareroot(double x) {
    double value=1.0;
    for(double guess=0.0; my_abs(value-guess)>EPSILON; value=(value+x/value)/2.0){
        guess=value;
    }
    return value;
    }
double my_sin(double x){
    int n=0;
    double previous_sin=x;
    double sin_value=x;
    double sum_value=x;
    for(n=1;n<=1000;n++){
	sin_value=(x/(2*n))*(x/(2*n+1))*(my_abs(previous_sin));
        if (n%2==0){
	    sum_value += sin_value;
	}else{
	    sum_value -= sin_value;
	}previous_sin = sin_value;
    }return sum_value;
}
double my_cos(double x){
    int n=0;
    double previous_cos=1;
    double cos_value=1;
    double value_sum=1;
    for(n=1;n<=1000;n++){
        cos_value=(x/(2*n))*(x/(2*n-1))*(my_abs(previous_cos));
        if (n%2==0){
	    value_sum+=cos_value;
	}else{
	    value_sum-=cos_value;
	}previous_cos = cos_value;
    }return value_sum;
}
double my_arcsin(double x){
    double previous_value_arc = x;
    double  current_value;
    if (x >= 0){
	current_value = previous_value_arc-(((my_sin(previous_value_arc))-x)/(my_cos(previous_value_arc)));
    }else{
	current_value = previous_value_arc-(((-my_sin(-previous_value_arc))-x)/(my_cos(previous_value_arc)));
    }while((my_abs(current_value-previous_value_arc))>EPSILON){
        if (x >= 0){
            current_value = previous_value_arc-(((my_sin(previous_value_arc))-x)/(my_cos(previous_value_arc)));
        }else{
            current_value = previous_value_arc-(((-my_sin(-previous_value_arc))-x)/(my_cos(previous_value_arc)));
        }
	previous_value_arc = current_value;
        if (x >= 0){
            current_value = previous_value_arc-(((my_sin(previous_value_arc))-x)/(my_cos(previous_value_arc)));
        }else{
            current_value = previous_value_arc-(((-my_sin(-previous_value_arc))-x)/(my_cos(previous_value_arc)));
        }
    }return current_value;
    }
double my_arccos(double x){
    double arccos_value=0;
    arccos_value=M_PI/2;
    arccos_value=arccos_value-my_arcsin(x);
    return arccos_value;    
}
double my_arctan(double x){
    double arctan_value=(x*x)+1;
    arctan_value=my_squareroot(arctan_value);
    arctan_value=x/arctan_value;
    arctan_value=my_arcsin(arctan_value);
    return arctan_value;    
}
double my_log(double x){
    double previous_value = 1.0;
    double result_value = 0.0;
    while(my_abs(previous_value-result_value)>EPSILON){    
        previous_value = result_value;
        result_value = previous_value + (x-(Exp(previous_value))) / Exp(previous_value); 
    }return result_value;
}
