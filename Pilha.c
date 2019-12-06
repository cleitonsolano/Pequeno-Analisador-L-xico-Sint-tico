#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Pilha.h"


//PILHA :insiro no final e removo no final!!!!
//CRIANDO UMA PILHA SEQUÊNCIAL DE TAMANHO MAXÍMO 100 !!!!

//MINHA ESTRUTURA QUE IRA GUARDAR OS VALORES DA EXPRESSÃO
struct pilha{
	int qtd;//quantidade de elementos presentes na pilha
	char dados[MAX];//o dado de cada elemento da pilha
};

//MINHA ESTRUTURA DE PRIORIDADES QUE É UMA PILHA
struct prioridades{
	char valor;// dados
	int p;//vai guardar a prioridade
};

//typedef struct pilha Pilha;
//typedef struct prioridades Pilha_prioridades;

//CRIANDO A PILHA
Pilha *cria_pilha(){
	Pilha *pi;

	pi = (Pilha*)malloc(sizeof(Pilha));//alocando memoria para a pilha
	if(!pi) return NULL;//verifico se a Pilha existe

	pi->qtd = 0;//=0 pois atualmente não tem nenhum elemento preenchido na lista

	return pi;
}

//INSERINDO ELEMENTOS NA PILHA ( OPERAÇÃO PUSH)
int insere_final(Pilha *pi, char elem){

	if(pi == NULL || pi->qtd == MAX) return 0;//verifico se a Pilha existe e se ela tem espaço

	pi->dados[pi->qtd] = elem;//inserindo no final
	pi->qtd++;

	return 1;
}

//DESALOCAR MEMORIA DA PILHA PRIORIDADES
int libera_pilha1(Pilha *pi){
	if(!pi) return 0;//verifico se a Pilha existe
	free(pi);//desaloco a pilha como um todo

	return 1;
}

//DESALOCAR MEMORIA DA PILHA EXPRESSÃO OU PILHA RESULTADO
int libera_pilha2(Pilha_prioridades *pi){
	if(!(pi)) return 0;//verifico se a Pilha existe
	free((pi));//desaloco a pilha como um todo

	return 1;
}

//REMOÇÃO DA PILHA NO FINAL (OPERAÇÃO POP)
int remove_final(Pilha *pi){
	if(pi == NULL || pi->qtd == 0) return 0;//verifico se a Pilha existe e se a pilha esta vazia

	pi->qtd--;

	return 1;

}

//IMPRIMINDO CADA ELEMENTO DA PILHA
int imprime_pilha(Pilha *pi){
	if(pi == NULL || pi->qtd == 0) return 0;

	int i;

	printf("\n\n");
	for(i=0;i<pi->qtd;i++){
		printf("%c ",pi->dados[i]);
	}printf("\n\n");

	return 1;
}

//PILHA VAI GUARDAR TODOS OPERADORES POSSIVEIS E SUAS RESPECTIVAS PRIORIDADES
Pilha_prioridades *guardar_prioridades(){
	Pilha_prioridades  *pi;
	pi = (Pilha_prioridades*)malloc(T * sizeof(Pilha_prioridades));
	if(!(pi)) return NULL;//verifico se a Pilha existe
	(pi)[0].p = 6;
	pi[0].valor = '^';
	pi[1].p = 5;
	pi[1].valor = ',';
	pi[2].p = 5;
	pi[2].valor = '/';
	pi[3].p = 5;
	pi[3].valor = '*';
	pi[4].p = 4;
	pi[4].valor = '+';
	pi[5].p = 4;
	pi[5].valor = '-';
	pi[6].p = 3;
	pi[6].valor = '<';
	pi[7].p = 3;
	pi[7].valor = '>';
	pi[8].p = 3;
	pi[8].valor = '=';
	pi[9].p = 3;
	pi[9].valor = '#';
	pi[10].p = 2;
	pi[10].valor = '.';
	pi[11].p = 1;
	pi[11].valor = '|';
    pi[12].p = -1;
	pi[12].valor = '(';
    pi[13].p = -1;
	pi[13].valor = ')';


	return (pi);
}

//PESQUISAR QUAL A PRIORIDADE DE DETERMINADO OPERADOR
int  pesquisa_prioridade(Pilha_prioridades *pi, char val){
	if(!(pi)) return 0;// caso a pilha de prioridades exista

	int i=0;

	while(i < T && pi[i].valor != val){
		i++;
	}
	if(i == T){
		return -1;//operador nao encontrado,não pode ser zero pois ele é uma prioridade
	}else{
		return (pi[i].p);//operador encontrado, retorno a sua prioridade
	}
}

//ARMAZENANDO TODOS OS OPERADORES NESSA PILHA
Pilha *avaliador_lexico_e_sintatico(Pilha *pi, Pilha_prioridades *p, int *flag_error){// vou reotrnar a pilha dos operandos que vai ter a notação polonesa inversa
	if(!pi) return NULL;//caso minha pilha expressao exista

	Pilha *p_operadores;//pilha  que vai  armazenar os OPERADORES!!
	Pilha *p_operandos;// pilha que vai armazenar os OPERANDOS!!

	p_operadores = cria_pilha();//criando pilha dos operadores
	p_operandos = cria_pilha();//criando pilha dos operandos

	if(!p_operadores || !p_operandos) return NULL;// verificar caso as duas foram criadas com sucesso

	*flag_error=0; // se ficar igual a zero ate o final do programa quer dizer que não teve nenhum erro!
	int i=0,flag_operandos = 0,j,flag_operadores = 0, flag_abre = 0, flag_fecha = 0;

	while(i < pi->qtd){//criteiro de parada caso chegue no ultimo elemento da pilha da expressão
        if(pi->dados[i] >= 48 && pi->dados[i] <= 57 || pi->dados[i] >= 65 && pi->dados[i] <= 90 || pi->dados[i] >= 97 && pi->dados[i] <= 122){///se for verdade ele é um OPERANDO !!!
            p_operandos->dados[p_operandos->qtd] = pi->dados[i];
			p_operandos->qtd++;
			flag_operandos++;
			flag_operadores=0;
		// '(' ou ')' são tratados como caso a parte(Não são operadores nem operandos) mas indiretamente eles tem que ter uma prioridade, no caso a menor!
        }else if(pi->dados[i] == 40){ /// caso seja  '('
            p_operadores->dados[p_operadores->qtd] = pi->dados[i];
            p_operadores->qtd++;
            if(i-1 >= 0 && flag_operandos == 1){
                printf("Syntax Error!\n");//caso tenha um operando sem a presença do operador ao lado do ( tipo a+b(c-d)... erro OOKK
                *flag_error=1;
                break;
            }
            flag_abre++;

        }else if(pi->dados[i] == 41){ ///caso seja  ')'
        	if(p_operadores->qtd == 0){
                printf("Syntax Error!\n");//verificando caso comece com parenteses ) na pilha dos operadores OOOKK
                *flag_error=1;
				break;
            }else{
                p_operadores->qtd--;
            }
            while(p_operadores->qtd > 0 && p_operadores->dados[p_operadores->qtd] != 40){
                insere_final( p_operandos, p_operadores->dados[p_operadores->qtd]);/// p_operandos->dados[p_operandos->qtd] =  p_operadores->dados[p_operadores->qtd];e depois p_operandos->qtd++;
                remove_final(p_operadores);// ou posso fazer assim: p_operadores->qtd--;
            }
            if(p_operadores->dados[p_operadores->qtd] != 40) { // nao achou o '('
                printf("Syntax Error!\n");
                *flag_error = 1;
                break;
            }
            flag_fecha++;
            if(flag_fecha > flag_abre) {
                printf("Syntax Error!\n");
                *flag_error = 1;
                break;
            }
            if(i+1 == pi->qtd) {
                p_operadores->qtd--;// para retirar o ( da p_operadores

            }

        }else if(pi->dados[i] >= 42 && pi->dados[i] <= 47 || pi->dados[i] >= 60 && pi->dados[i] <= 62 || pi->dados[i] == 35 || pi->dados[i] == 94){///se for verdade ele é um OPERADOR !!!
            if(p_operadores->qtd == 0){//caso ela esteja vazia (EMPILHO PO)
				p_operadores->dados[p_operadores->qtd] = pi->dados[i];
				p_operadores->qtd++;
            }else if(pesquisa_prioridade(p,p_operadores->dados[p_operadores->qtd-1]) < pesquisa_prioridade(p,pi->dados[i])){//caso a prioridade do ultimo elemento da pi_operadores seja menor que pi->dados[i] apenas insiro em pi_operadores
                p_operadores->dados[p_operadores->qtd] = pi->dados[i];
				p_operadores->qtd++;
			}
			else{//caso a prioridade do ultimo elemento seja MAIOR ou IGUAL(DESEMPILHO PO) pesquisa_prioridade(pi,p_operadores[p_operadores-1]->dadods) <= pesquisa_prioridade(pi,pi[i]->dadods)
				p_operandos->dados[p_operandos->qtd]  = p_operadores->dados[p_operadores->qtd-1];/// retirei da pilha de operadores o ultimo e acrescentei nA pilha dos operandos
				p_operandos->qtd++;
				p_operadores->dados[p_operadores->qtd-1] = pi->dados[i];/// recebeu o utimo da pilha de dados, na posição que ocupava o ultimo elemento da pi_operadores

			}
			flag_operandos = 0;
			flag_operadores++;

        }else{// caso não seja um operando, não seja um operador e não seja um '(' ou ')'
            printf("Lexical Error!\n");
            *flag_error=1;
            break;
        }
        if(flag_operandos >= 2){// caso tenha dois ou mais operandos juntos !!! OOOKK
            printf("Syntax Error!\n");
            *flag_error=1;
            break;
        }
	i++;

    }

    if(flag_operadores > 0 && *flag_error == 0) {
        printf("Syntax Error! \n");///caso nao tenha dois operandos para cada operador !!!! OOOKK
        *flag_error=1;
    }

    if(flag_abre == flag_fecha) {
        while(p_operadores->qtd >= 0){
            if(p_operadores->dados[p_operadores->qtd] =='(' && *flag_error == 0){
                printf("Syntax Error!\n");// caso tenha um sobrando ( quer dizer que não fecharam todos os parenteses
                *flag_error=1;
                break;
            }
            // e ao mesmo tempo que verifico os parenteses, vou desempilhando os operadores restantes na p_operadores
            insere_final( p_operandos, p_operadores->dados[p_operadores->qtd]); //p_operandos->dados[p_operandos->qtd] = p_operadores->dados[p_operadores->qtd-1];
            p_operadores->qtd--;

        }
    }else {
    	if(*flag_error == 0){
    		printf("Syntax Error!\n");
        	*flag_error = 1;	
    	}
        
    }
    /*
    if(p_operadores->qtd==0 ){
        while(p_operadores->qtd>= 0){
            printf("\n\nentrei no while final!!!\n\n");
            if(p_operadores->dados[p_operadores->qtd] =='(' && *flag_error == 0 && flag_aux == 0){
                printf("ERROR SINTAXE5!\n");// caso tenha um sobrando  ( quer dizer que não fecharam todos os parenteses
                *flag_error=1;
                break;
            }
                // e ao mesmo tempo que verifico os parenteses, vou desempilhando os operadores restantes na p_operadores
            insere_final( p_operandos, p_operadores->dados[p_operadores->qtd]); //p_operandos->dados[p_operandos->qtd] = p_operadores->dados[p_operadores->qtd-1];
            p_operadores->qtd--;
        }
    }else{
        while(p_operadores->qtd > 0){
            printf("\n\n%i\n\n%i\n\n%c\n\n",p_operadores->qtd,p_operandos->qtd,p_operadores->dados[p_operadores->qtd]);
            printf("\n\nentrei no while final!!!\n\n");
            if(p_operadores->dados[p_operadores->qtd] =='(' && *flag_error == 0){
                printf("ERROR SINTAXE5!\n");// caso tenha um sobrando ( quer dizer que não fecharam todos os parenteses
                *flag_error=1;
                break;
            }
            // e ao mesmo tempo que verifico os parenteses, vou desempilhando os operadores restantes na p_operadores
            insere_final( p_operandos, p_operadores->dados[p_operadores->qtd]); //p_operandos->dados[p_operandos->qtd] = p_operadores->dados[p_operadores->qtd-1];
            p_operadores->qtd--;

        }
    }
     */

    return p_operandos;
}

