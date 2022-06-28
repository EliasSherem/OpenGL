#include <stdio.h>
#include <math.h>
double seno(double x){
	return sin(x);
}

double coseno(double x){
	return cos(x);
}
void evalua (double(*funcion)(double)){
	double i;
	for( i=-3.14;i<3.14;i+=.7){
		printf("%5.2f %6.3f \n",i, (*funcion)(i));
	}
}

int main(){
	printf("\n Funcion seno(x) \n",224);
	evalua(seno);
	printf("\n Funcion coseno(x) \n",224);
	evalua(coseno);
	
}
