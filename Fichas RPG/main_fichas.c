#include "fichas.h"

int main(){
	int x, aux, cont=0, flag, cont2, fhash=0, qtd, cont3, criou=0;
	Lista *li, *buffer;
	struct entrada al[MAX];
	do{
		printf("\n\tMENU\n");
		printf("1.Criar lista.\n");
		printf("2.Verificar se a lista eh vazia.\n");
		printf("3.Liberar a lista.\n");
		printf("4.Inserir dados de jogador.\n");
		printf("5.Remover a ultima ficha inserida.\n");
		printf("6.Verificar a quantidade de jogadores.\n");
		printf("7.Imprimir fichas.\n");
		printf("8.Finalizar o programa.\n");
		printf("Digite sua escolha: ");
		scanf("%d",&aux);
		system(CLEAR);
		switch(aux){
			case 1:
				if(criou ==1){
					printf("A lista ja foi criada!!");
				}else{
					li = cria_lista();
					buffer = cria_lista();
					criou = 1;
				}
			break;
			case 2:
				if(criou == 1){
					x = lista_vazia(li);
					if(x==0){
						printf("A lista nao esta vazia!\n\n");
					}else{
						printf("A lista esta vazia!\n\n");
					}
				}else{
					printf("A lista nao foi criada");
				}
			break;
			case 3:
				if(criou == 1){
					libera_lista(li);
					libera_lista(buffer);
					printf("Lista liberada!");
					criou = 0;
				}else
					printf("A lista nao foi criada");
			break;
			case 4:
				if(criou ==1){
					printf("Digite quantas fichas deseja inserir: ");
					scanf("%d",&qtd);
					system(CLEAR);
					for(cont3=0;cont3<qtd;cont3++){
						flag = recebe(&al[cont],cont,flag);
						x = insere_final(buffer, al[cont]);
						cont++;
						system(CLEAR);
						if(cont==10){
							for(cont2=0;cont2<MAX;cont2++){
								al[cont2].prevHash = fhash;
							}
							for(cont2=0;cont2<MAX;cont2++){
								fhash = al[cont2].hash + fhash;
							}
							for(cont2=0;cont2<MAX;cont2++){
								al[cont2].hash = fhash;
								x = insere_final(li, al[cont2]);
							}
							libera_lista(buffer);
							buffer = cria_lista();
							printf("Elementos transferidos para o bloco.\n\n");
							cont=0;
						}	
					}
					if(x==0){
						printf("Erro!\n\n");
					}else{
						printf("Ficha inserida com sucesso!\n\n");
					}
				}else
					printf("A lista nao foi criada");
			break;
			case 5:
				if(criou == 1){
					x = remove_final(buffer);
					if(x==0){
						printf("Erro!\n\n");
					}else{
						printf("Ficha removida com sucesso!\n\n");
					}
				}else
					printf("A lista nao foi criada");
			break;
			case 6:
				if(criou == 1){
					printf("1.Verificar tamanho do buffer.\n");
					printf("2.Verificar tamanho dos blocos.\n");
					printf("Decisao: ");
					scanf("%d",&aux);
					system(CLEAR);
					if(aux==1){
						x = tamanho_lista(buffer);
						if(x==-1){
							printf("Erro!\n\n");
						}else{
							printf("A quantidade de jogadores no buffer eh:%d\n\n",x);
						}
					}else{
						x = tamanho_lista(li);
						if(x==-1){
							printf("Erro!\n\n");
						}else{
							printf("A quantidade de jogadores nos blocos eh:%d\n\n",x);
						}
					}
				}else
					printf("A lista nao foi criada");
			break;
			case 7:
				if(criou == 1){
					printf("1.Imprimir o buffer.\n");
					printf("2.Imprimir blocos.\n");
					printf("Decisao: ");
					scanf("%d",&aux);
					system(CLEAR);
					if(aux==1){
						imprime(buffer, aux);
					}else{
						imprime(li, aux);
					}
				}else
					printf("A lista nao foi criada");
			break;
		}
	}while(aux!=8);

	return 0;
}
