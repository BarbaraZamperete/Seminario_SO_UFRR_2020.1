/*Algoritmo baseado no código de gustavomrs */

#include <stdio.h>

#define X 5
#define Y 4

#define false 0
#define true 1

//variáveis globais
// alterando os valores dos recursos disponíveis, obtemos resultados diferentes ex: {9,6,2}
int recursos_disponiveis[Y] = {1,0,2,0}; // recursos disponíveis
int recursos_atribuidos[X][Y] = {{3,0,1,1},{0,1,0,0},{1,1,1,0},{1,1,0,1},{0,0,0,0}};	 
int recursos_necessarios[X][Y] = {{1,1,0,0,},{0,1,1,2},{3,1,0,0},{0,0,1,0},{2,1,1,0}}; 


int i, j, k, podeSerAtendido;
int verifica_atendimento[X]; //vetor que armazena se o processo foi atendido ou nao
int deadlock = false;
int ordem_atendimento[X]; //vetor que armazena a ordem que os processos foram atendidos
int numero_atendimento = 0;


void processos_n_atendidos(int num_processo);

int main()
{
	for(i = 0 ; i < X; i++)
		verifica_atendimento[i] = true;

	for(i = 0; i < X; i++) {
		podeSerAtendido = 0;
		for(j = 0; j < Y; j++) {
			if(recursos_necessarios[i][j] <= recursos_disponiveis[j]) { //verifica se o pedido é igual ou menor que os recursos disponiveis
				podeSerAtendido++;
			}
		}
		//se a condicao for verdadeira, significa que o processo pode ser atendido com os recursos que ele deseja
		if(podeSerAtendido == Y) {
			//se o processo pode ser atendido, atualiza  o array A 
			for(k = 0; k < Y; k++) {
				recursos_disponiveis[k] = recursos_disponiveis[k] + recursos_atribuidos[i][k];
				recursos_atribuidos[i][k] = 0;
			}
			verifica_atendimento[i] = true;
			ordem_atendimento[numero_atendimento] = i;
			numero_atendimento++;
			//varrer a lista de nao atendidos, para ver se um novo processo pode ser atendido agora
			for(k = 0; k < X; k++) {
				if(verifica_atendimento[k] == false)
					processos_n_atendidos(k);				
			}
		}
		else {
			verifica_atendimento[i] = false;
		}	
	}
	for(i = 0; i < X; i++)
		if(!verifica_atendimento[i])
			deadlock = true;

	if(deadlock) { 
		printf("Houve deadlock com os seguintes processos:");
		for(i = 0; i < X; i++)
			if(verifica_atendimento[i] == false)
				printf("p%d, ", i);
	}
	else {
		printf("Nao houve deadlock. Os processos podem ser atendidos na seguinte ordem:");
		for(i = 0; i < X; i++)
			printf("p%d, ", ordem_atendimento[i]);
	}
	printf("\n");	
	return 0;
}

void processos_n_atendidos(int num_processo) {
	podeSerAtendido = 0;
	for(j = 0; j < Y; j++) {
		if(recursos_necessarios[num_processo][j] <= recursos_disponiveis[j]) {
			podeSerAtendido++;
		}
	}

	if(podeSerAtendido == Y) { // se todos os elementos da linha podem ser atendidos
		//o processo pode ser atendido então atualiza  o vetor A
		int z;
		for(z = 0; z < Y; z++) {
			recursos_disponiveis[z] = recursos_disponiveis[z] + recursos_atribuidos[num_processo][z];
			recursos_atribuidos[num_processo][z] = 0;
		}
		verifica_atendimento[num_processo] = true;
		ordem_atendimento[numero_atendimento] = num_processo;
		numero_atendimento++;
	}
}