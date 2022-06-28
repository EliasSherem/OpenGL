#include <stdio.h>

int main(){
	char tablero [8][8];
	int x,y,i,j;
	fflush(stdin);
	printf("Ingresa las coordenadas del caballo: (x,y)\n");
	printf("Ingresa x: ");
	scanf("%d",&x);
	printf("Ingresa y: ");
	scanf("%d", &y);
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			tablero[i][j]='-';
		}
	}
	tablero[x][y]='c';
	if(x+2 < 8){
		if(y+1 < 8){
			tablero[x+2][y+1]='*';
		}
		if(y-1 > 0){
			tablero[x+2][y-1]='*';
		}
	}
	if(x-2 > 0){
		if(y+1 < 8){
			tablero[x-2][y+1]='*';
		}
		if(y-1>0){
			tablero[x-2][y-1]='*';
		}
	}
	if(y+2 < 8){
		if(x+1 <8){
			tablero[x+1][y+2]='*';
		}
		if(x-1>0){
			tablero[x-1][y+2]='*';
		}
	}
	if(y-2 > 0){
		if(x+1 < 8){
			tablero[x+1][y-2]='*';
		}
		if(x-1>0){
			tablero[x-1][y-2]='*';
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			printf("%c ",tablero[i][j]);
		}
		printf("\n");
	}
	return 0;
}
