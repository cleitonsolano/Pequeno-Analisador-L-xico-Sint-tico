//ARQUIVO PILHA.H
//Aqui vão estar: Os prototipos das funções, os tipos dos ponteiros e os dados globalmente acessíveis

#define MAX 100
#define T 14 //tamanho da pilha de prioridades

typedef struct pilha Pilha;
typedef struct prioridades Pilha_prioridades;

Pilha *cria_pilha();
int insere_final(Pilha *pi, char elem);
int libera_pilha1(Pilha *pi);
int libera_pilha2(Pilha_prioridades *pi);
int remove_final(Pilha *pi);
int imprime_pilha(Pilha *pi);
Pilha_prioridades *guardar_prioridades();
int  pesquisa_prioridade(Pilha_prioridades *pi, char val);
Pilha *avaliador_lexico_e_sintatico(Pilha *pi, Pilha_prioridades *p,int *flag_error);
