#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define UP 		0
#define DOWN 	1
#define LEFT 	2
#define RIGHT 	3
#define lAlvo 	3
#define cAlvo 	2
float sigma = 0.7;
float alfa = 0.5;
float epsilon = 0.05;
float Inf = 10000000000000.0000;

int a[9][6] = { 
	{0,0,0,0,0,1},//1
	{0,1,0,1,0,0},//2
	{1,1,1,1,0,1},//3
	{0,0,9,1,0,1},//4
	{0,0,0,1,0,0},//5
	{0,1,1,1,0,0},//6
	{0,1,0,0,0,0},//7
	{0,1,1,1,1,0},//8
	{0,0,0,0,0,0},//9

};

int t[9][6] = { 
	{ 0, 0, 0, 0, 0,-1},//1
	{ 0,-1, 0,-1, 0, 0},//2
	{-1,-1,-1,-1, 0,-1},//3
	{ 0, 0,-9,-1, 0,-1},//4
	{ 0, 0, 0,-1, 0, 0},//5
	{ 0,-1,-1,-1, 0, 0},//6
	{ 0,-1, 0, 0, 0, 0},//7
	{ 0,-1,-1,-1,-1, 0},//8
	{ 0, 0, 0, 0, 0, 0},//9

};


typedef struct 
{
	int linha;
	int coluna;
	int r;

}agente;
agente robo;

int recompensa(int linhaAgente, int colunaAgente, int linhaAmbiente, int colunaAmbiente);
void imprimeAgente(int ambiente[9][6], agente r);
void imprimeAgente2(int ambiente[9][6]);
void zera(int ambiente[9][6]);
void inicializaQ(float q[][6][4]);
void imprimeQ(float q[][6][4]);
//int calculaQ(float q[][6][4],agente *r,int ambiente[][6]);
float melhorAcao(float q[][6][4], int i, int j,int *pos, int ambiente [][6]);
void anda(int ambiente[][6],float q[][6][4],agente *r);
int AcaoAle( int i, int j, int ambiente [][6]);

float q[9][6][4];
void aleAgente(agente *r, int ambiente[][6]){
	int x = rand()%9;
	int y = rand()%6;
	while(ambiente[x][y]==1){
		x = rand()%9;
		y = rand()%6;
	}
	r->linha = x;
	r->coluna = y;
}

int inte = 120;
int main(int argc, char const *argv[])
{
	robo.linha = 0;
	robo.coluna = 0;
	inicializaQ(q);
	printf("\n");
	int cont=0;
	int v[inte];
	int ate= 0;
	//printf("roo %f\n",RO );
	imprimeAgente2(t);

	while(ate < inte){
		 robo.linha = 0;
		 robo.coluna = 0;
		//aleAgente(&robo,a);
		while((robo.linha!=lAlvo) || (robo.coluna !=cAlvo) ){
			imprimeAgente(a,robo);
			//getchar();
			t[robo.linha][robo.coluna] = t[robo.linha][robo.coluna] + 1;
			anda(a,q,&robo);
			system("clear");
			//imprimeQ(q);
			//printf("\n");
			printf("%d\n",ate);
			//if (ate == 2){
			//imprimeQ(q);
			//imprimeAgente(a,robo);
			//printf("\n%f\n",alfa);
			//getchar();
			//			}
			//printf("linha: %d coluna:%d\n",robo.linha,robo.coluna );
			cont++;
		}
		imprimeAgente2(t);
		printf("\n");
		imprimeAgente(a,robo);
		//getchar();
		zera(t);
	//alfa = 1/((float)ate+1.0);
	epsilon = epsilon/2.0;
	//getchar();
	v[ate]=cont;
	cont = 0;
	ate ++;
	int i;
	system("clear");
	for(i = 0; i< ate; i ++){
		printf("i%d:%d\n",i,v[i]);
	}
	}
	//printf("%f\n",RO );
	
	return 0;
}



void imprimeAgente2(int ambiente[9][6]){
	int i,j;
	//system("clear");
	for(i = 0; i < 9 ; i ++){
		printf("\n");
		for (j = 0; j< 6; j++){
			if(ambiente[i][j] == -1){
				printf(" * ");
			}
			// else if (i== r.linha && j == r.coluna){
			// 	printf(" A ");
			// }
			else if (ambiente[i][j] == -9){
				printf(" $ ");
			}
			else {
				printf(" %d ",ambiente[i][j]);
			}

		}
	}
	printf("\n");
	
}

void zera(int ambiente[9][6]){
	int i,j;
	//system("clear");
	for(i = 0; i < 9 ; i ++){
		
		for (j = 0; j< 6; j++){
			if(ambiente[i][j] != -1 && ambiente[i][j] != -9 ){
				ambiente[i][j] = 0;
			}
		}
	}	
}





void imprimeAgente(int ambiente[9][6], agente r){
	int i,j;
	//system("clear");
	for(i = 0; i < 9 ; i ++){
		printf("\n");
		for (j = 0; j< 6; j++){
			if(ambiente[i][j] == 1){
				printf(" * ");
			}
			else if (i== r.linha && j == r.coluna){
				printf(" A ");
			}
			else if (ambiente[i][j] == 9){
				
				printf(" $ ");
			}
			else {
				printf(" - ");
			}

		}
	}
	printf("\n");
	
}

void inicializaQ(float q[][6][4]){
		int i,j,k;
		for ( i = 0; i < 9; i++)
		{
			for ( j = 0; j < 6; j++)
			{
				for ( k = 0; k < 4; k++)
				{
					q[i][j][k] = 0.0;
				}
				
			}
		}

}
 
void imprimeQ(float q[][6][4]){
	int i,j,k;

	for(i = 0; i < 9 ; i ++){
		printf("(%d)\n",i+1);
		printf("    [U]  [D]   [L]   [R] \n");		
		for (j = 0; j< 6; j++){
			
			for ( k = 0; k< 4; k++){
	
				if(q[i][j][k] == Inf){
					printf(" INF ");
				}
				else{
					printf(" %4.2f ",q[i][j][k]);
				}
			
			}
			printf("[%d]\n",j+1 );				
		}

	}
	printf("\n");
}

int recompensa(int linhaAgente, int colunaAgente, int linhaAlvo, int colunaAlvo){

	// int x,x1,y,y1,
	int v=0;

	// x1 = pow((linhaAgente-linhaAlvo),2);
	// x = sqrt(x1);
	// y1 = pow((colunaAgente-colunaAlvo),2);
	// y = sqrt(y1);
	// v = x+y;
	if (linhaAgente == linhaAlvo && colunaAgente == colunaAlvo){
		v = Inf;
	}
	else{
		v = -1.00;
	}
	
	return v;
}
 

// int calculaQ(float q[][6][4],agente *r,int ambiente[][6]){


// }

float melhorAcao(float q[][6][4], int i, int j,int *pos, int ambiente [][6]){
	float maior;
	int indice[4];// vai estar o valor das acoes disponiveis
	int cont = 0,k;

	if(i-1 >= 0 && ambiente[i-1][j]!=1){	// verifica se a acao UP esta disponivel
		indice[cont]=UP;
		cont++;
	}
	if(i+1 < 9 && ambiente[i+1][j]!=1){ 	// verifica se a acao DOWN esta disponivel
		indice[cont]=DOWN;
		cont++;
	}
	if(j-1 >= 0 && ambiente[i][j-1]!=1){	// verifica se a acao LEFT esta disponivel
		indice[cont]=LEFT;
		cont++;
	}
	if(j+1 < 6 && ambiente[i][j+1]!=1){		// verifica se a acao RIGHT esta disponivel
		indice[cont]=RIGHT;

		cont++;
	}
	printf("UP:%d,DOWN:%d,LEFT:%d:RIGHT:%d\n",i-1,i+1,j-1,j+1);
// esolaha da ação
	maior = q[i][j][indice[0]];
	*pos = indice[0];
	for (k = 0; k < cont; k++){	//procura a acao de maior valor.
		//printf("%d,%f",indice[k],q[i][j][indice[k]]);
		//getchar();
		if(maior < q[i][j][indice[k]]){
			maior = q[i][j][indice[k]];
			*pos = indice[k];
		}
	}
//

return maior;
	
}




int AcaoAle( int i, int j, int ambiente [][6]){
	int pos;
	int indice[4];// vai estar o valor das acoes disponiveis
	int cont = 0,k;

	if(i-1 >= 0 && ambiente[i-1][j]!=1){	// verifica se a acao UP esta disponivel
		indice[cont]=UP;
		cont++;
	}
	if(i+1 < 9 && ambiente[i+1][j]!=1){ 	// verifica se a acao DOWN esta disponivel
		indice[cont]=DOWN;
		cont++;
	}
	if(j-1 >= 0 && ambiente[i][j-1]!=1){	// verifica se a acao LEFT esta disponivel
		indice[cont]=LEFT;
		cont++;
	}
	if(j+1 < 6 && ambiente[i][j+1]!=1){		// verifica se a acao RIGHT esta disponivel
		indice[cont]=RIGHT;

		cont++;
	}
	printf("UP:%d,DOWN:%d,LEFT:%d:RIGHT:%d\n",i-1,i+1,j-1,j+1);
// esolaha da ação
	k = rand()%cont;
	pos = indice[k];


return pos;
	
}





void anda (int ambiente[][6],float q[][6][4],agente *r){
	int pos;
	int reco = recompensa(r->linha,r->coluna,lAlvo,cAlvo);
	float ran = rand()/(RAND_MAX+1.0);
	
	float acao2;
	// if(ran < 1-epsilon){
		float acao = melhorAcao(q,r->linha,r->coluna,&pos,ambiente);
	// }
	// else{
	// 	pos = AcaoAle(r->linha,r->coluna,ambiente);
	// }
	
	
	switch(pos){
		case UP:{
			printf(" UP \n");
			acao2 =  melhorAcao(q,r->linha-1,r->coluna,&pos,ambiente);
			q[r->linha][r->coluna][UP] =q[r->linha][r->coluna][UP]+alfa*(reco+sigma*acao2-q[r->linha][r->coluna][UP]);
			r->linha = r->linha - 1;
			break;
		}
		case DOWN:{
			printf(" DOWN \n");
			acao2 = melhorAcao(q,r->linha + 1,r->coluna,&pos,ambiente);
			q[r->linha][r->coluna][DOWN] =q[r->linha][r->coluna][DOWN]+alfa*(reco+sigma*acao2-q[r->linha][r->coluna][DOWN]);
			r->linha = r->linha + 1;
			break;
		}
		case LEFT:{
			printf(" LEFT \n");
			acao2 =  melhorAcao(q,r->linha,r->coluna-1,&pos,ambiente);
			q[r->linha][r->coluna][LEFT] =q[r->linha][r->coluna][LEFT]+alfa*(reco+sigma*acao2-q[r->linha][r->coluna][LEFT]);
			r->coluna = r->coluna - 1;
			break;
		}
		case RIGHT:{
			printf(" RIGHT \n");
			acao2 =  melhorAcao(q,r->linha,r->coluna+1,&pos,ambiente);
			q[r->linha][r->coluna][RIGHT] =q[r->linha][r->coluna][RIGHT]+alfa*(reco+sigma*acao2-q[r->linha][r->coluna][RIGHT]);
			r->coluna = r->coluna + 1;
			break;
		}
	}

	//printf("\ni:%dj:%d\n",r->linha,r->coluna);
	//getchar();

}