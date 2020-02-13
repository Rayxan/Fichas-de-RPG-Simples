#include "fichas.h"

Lista* cria_lista(){
	Lista* li = (Lista*)malloc(sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

void libera_lista(Lista* li){
		Elem* no;
		while((*li) != NULL){
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(*li);
}

int tamanho_lista(Lista* li){
	if(li==NULL){
		return -1;
	}
	int cont = 0;
	Elem* no = *li;
	while(no != NULL){
		cont++;
		no = no->prox;
	}
	return cont;
}

int lista_vazia(Lista* li){
	if(li == NULL){
		return 1;
	}else if(*li == NULL){
		return 1;
	}else
	return 0;
}

void imprime(Lista* li, int auxi){
	if(li==NULL||(*li)==NULL){
		printf("A estrutura escolhida nao possui elementos.\n");
	}else{
		Elem *aux = *li;
		int cont = 0, bloco=1;
		while(aux != NULL){
			if(auxi==2){
				if(cont==0||cont % 10==0){
					printf("\t\t\tBloco %d\n",bloco);
					printf("Hash Anterior: %x\n",(aux->dados).prevHash);
					printf("Hash: %x\n\n",(aux->dados).hash);
					bloco++;
				}
			}
			cont++;
			printf("Jogador %d\n",cont);
			printf("Id do Jogador: %d\n",(aux->dados).id);
			printf("Nome do Jogador: %s\n",(aux->dados).nome);
			printf("Nome do Personagem: %s\n",(aux->dados).player);
			printf("Raca: %s\n",(aux->dados).raca);
			printf("Forca: %d\n",(aux->dados).fo);
			printf("Constituicao: %d\n",(aux->dados).cons);
			printf("Destreza: %d\n",(aux->dados).des);
			printf("Inteligencia: %d\n",(aux->dados).inte);
			printf("Sabedoria: %d\n",(aux->dados).sab);
			printf("Carisma: %d\n\n",(aux->dados).car);
			aux = aux->prox;
		}
	}
}

int insere_final(Lista* li, struct entrada al){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*)malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = al;
	no->prox = NULL;
	if((*li)==NULL){
		*li = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
	}
	return 1;
}

int remove_final(Lista* li){
	if(li==NULL||(*li)==NULL){
		return 0;
	}
	Elem *ant, *no = *li;
	while(no->prox != NULL){
		ant = no;
		no = no->prox;
	}
	if(no==(*li)){
		*li=no->prox;
	}else{
		ant->prox = no->prox;
	}
	free(no);
	return 1;
}

int hash(char data[]){
	int hash = 0;
	int cont;
	for(cont=0;cont<strlen(data);cont++){
		hash = hash ^ data[cont];
		hash = hash*0x123456789;
	}
	return hash;
}

int mine_block(char data[]){
	int nonce = 0;
	int hash1;

	char dataToHash[256];

	while(1){
		sprintf(dataToHash,"%s%d",data,nonce);
		hash1 = hash(dataToHash);

		if((hash1 & 0xff) == 0xAA){
			return nonce;
		}
		nonce++;
	}
	return nonce;
}

int recebe(struct entrada *al, int cont, int flag){
	struct entrada al2;
	char converte[250];

	printf("Digite seu ID: ");
	scanf("%d",&al2.id);
	getchar();
    printf("Digite seu nome: ");
	scanf("%[^\n]",al2.nome);
	getchar();
    printf("Digite o nome do seu personagem: ");
    scanf("%[^\n]",al2.player);
    getchar();
    printf("Digite sua raca: ");
    scanf("%[^\n]",al2.raca);
    printf("Forca: ");
    scanf("%d",&al2.fo);
    printf("Constituicao: ");
    scanf("%d",&al2.cons);
    printf("Destreza: ");
    scanf("%d",&al2.des);
    printf("Inteligencia: ");
    scanf("%d",&al2.inte);
    printf("Sabedoria: ");
    scanf("%d",&al2.sab);
    printf("Carisma: ");
    scanf("%d",&al2.car);
    if(cont>0){
    	al2.prevHash = flag;
		sprintf(converte,"%s%d",al2.nome,al2.prevHash);
    	al2.nonce = mine_block(converte);
    	sprintf(converte,"%s%d",converte,al2.nonce);
    	al2.hash = hash(converte);
    	flag = al2.hash;
    }else{
	   	al2.prevHash = 0;
    	sprintf(converte,"%s%d",al2.nome,al2.prevHash);
    	al2.nonce = mine_block(converte);
    	sprintf(converte,"%s%d",converte,al2.nonce);
    	al2.hash = hash(converte);
		flag = al2.hash;
	}
    *al = al2;
    return flag;
}
