#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define MAX 10

struct entrada{
	char nome[100], player[100], raca[100];
	int fo, sab, inte, car, des, cons, id;
	int hash, prevHash, nonce;
};
typedef struct elemento* Lista;

struct elemento{
	struct entrada dados;
	struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista();

void libera_lista(Lista* li);

int tamanho_lista(Lista* li);

int lista_vazia(Lista* li);

int remove_final(Lista* li);

void imprime(Lista* li, int auxi);

int hash(char data[]);

int mine_block(char data[]);

int recebe(struct entrada *al,int cont, int flag);

int insere_final(Lista* li, struct entrada al);
