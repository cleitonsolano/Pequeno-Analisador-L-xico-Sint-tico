/****************************************************************************** 
*	Alunos: Cleiton Solano Soares Caetano & Frank Douglas Barros			  *	
*	Materia: Estrutura de Dados												  *
*	Professora: N·dia Felix													  *
*	Goi‚nia, 13 de julho de 2017											  * 
*	EX01)										  							  *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Pilha.h"

int main(int argc, char *argv[]) {

	Pilha *pi, *pi_resultado = NULL;
	Pilha_prioridades *pp;

	int k=0,r=0,flag;
	char valor, op;

    pi = cria_pilha();
    pp = guardar_prioridades();
	/*

	//INSERINDO ELEMENTOS NA PILHA POR ARQUIVOS
	FILE *fptr;
	char nome[31], ch;

	printf("Digite o nome do arquivo:\n");
	scanf(" %[^\n]s",nome);

	if ((fptr = fopen(nome, "w+")) == NULL)
	{
		puts("O arquivo n√É¬£o pode ser aberto");
		exit(1);
	}

	puts("Digite alguma coisa para salvar em um arquivo (tecle ENTER para finalizar):");

	// Le um caracter por vez do teclado ate que seja teclado ENTER
	while ((ch = getchar()) != '\n')
		fputc(ch, fptr); // grava o caracter lido no arquivo
	fputc('\n', fptr); // acrescenta uma quebra de linha no final do arquivo

	// Le um caracter por vez do arquivo ate atingir o seu fim (End Of File - EOF)
	while ((ch = fgetc(fptr)) != EOF)
		putchar(ch);
	// depois criar uma fun√ß√£o dentro da pilha.h com nome insere_final e usando a mesma logica desse while para inserir a express√£o que esta no arquivo na pilha!
	fclose(fptr); // fecha o arquivo

	*/

	//resolvi deixar o insere elementos dessa fora por ser mais didatico!
	//INSERINDO ELEMENTOS NA PILHA 1 POR VEZ
    /*do{
    	printf("Digite o elemento %i  da pilha 1:\n",k);
    	scanf(" %c",&valor);

	 		r = insere_final(pi,valor);
    		if(r == 0){//caso a pilha esteja j√° com todas as posi√ß√µes ocupadas
    			printf("Pilha esta cheia (100 posicoes ocupadas)!\n");
				break;
    		}

	 	printf("Digite S para continuar N para sair:\n");
 		scanf(" %c",&op);
 		k++;
    }while(op == 'S' || op == 's');
    k=1;*/
	
	//ESSE … O JEITO MAIS SIMPLES DE LER !!! MAS, DESPONIBILIZEI MAIS OUTROS DOIS TIPOS DE LEITURA ;)
	printf("Digite a expressao:\n");
    scanf(" %s",pi->dados);
    pi->qtd = strlen(pi->dados);
    imprime_pilha(pi);

    pi_resultado = avaliador_lexico_e_sintatico(pi, pp,&flag);

    if(pi_resultado == NULL){
        printf("N√ÉO PROCESSOU ND!!\n");
    } else if(flag == 1){//printar apenas o erro que deu
    
	}else{//IMPRIMINDO A EQUA«√O P”S-FIXA OU INVERSA
		imprime_pilha(pi_resultado);
	}

	//DESALOCANDO A PILHA PRINCIPAL
	libera_pilha1(pi);
	//DESALOCANDO A PILHA DE PRIORIDADES
	libera_pilha2(pp);
	//DESALOCANDO A PILHA DO RESULTADO FINAL
	libera_pilha1(pi_resultado);

	return 0;
}

