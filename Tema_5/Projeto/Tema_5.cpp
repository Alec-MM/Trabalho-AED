#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 101

// ATENÇÃO: O cálculo da complexidade deve incluir todo o ccodigo, inclusive a leitura do arquivo.


char nome_arquivo[50], aux[MAX];								// proibido alterar esta linha
int opcao, tamanho, i, j, n, m, digrafo, matriz_adj[MAX][MAX];  // proibido alterar esta linha
// Declare variáveis globais a partir daqui.
typedef struct no_fila{
    int valor;
    struct no_fila *prox;
} no_fila;

typedef struct no_hash {
    int valor;
    struct no_hash *prox;
} no_hash;

typedef struct fila{
    struct no_fila *inicio;
    struct no_fila *fim;
} fila;

typedef struct tabela_hash{
    no_hash *vetor[10];
} tabela_hash;

fila* inicializar_fila(){
	fila *fi = (fila *) malloc(sizeof(fila));
	if(fi != NULL){
		fi->inicio = NULL;
		fi->fim = NULL;
	}
	return fi;
}

void enqueue(fila *fi, int valor){
    no_fila *novo = (no_fila *) malloc(sizeof(no_fila));
    
    if (novo == NULL){
        printf("\nerro de alocacao\n");
        return;
    }
    
    novo->prox = NULL;
    novo->valor = valor;
    
    if (fi->inicio == NULL){
        fi->inicio = novo;
        fi->fim = novo;
        return;
    } 
    
    fi->fim->prox = novo;
    fi->fim = novo;
    return;
}

int dequeue(fila *fi){
    if (fi == NULL){
        printf("\nerro: fila não encontrada\n");
        return 0;
    }
    
    if(fi->inicio == NULL){
        printf("\nfila vazia\n");
        return 0;
    }
    
    int valor = fi->inicio->valor;
    
    no_fila *aux = fi->inicio->prox;
    
    free(fi->inicio);
    
    fi->inicio = aux;
    
    if(fi->inicio == NULL){
        fi->fim = NULL;
    }
    
    return valor;
    
}

tabela_hash* inicializar_hash(){
	tabela_hash *tabela = (tabela_hash *) malloc(sizeof(tabela_hash));
	
	if(tabela == NULL){
		return tabela;
	} 
	
	int i = 0;
	while(i < 10){
		tabela->vetor[i] = NULL;
		i++;
	} 
	return tabela;
}

void inserir_hash(tabela_hash *tabela, int v){
	int indice = v % 10;

	no_hash *novo = (no_hash *) malloc(sizeof(no_hash));
	
	if(novo == NULL){
		printf("\n erro: novo nó não alocado");
		return;
	}

	novo->valor = v;

	novo->prox = tabela->vetor[indice];
	tabela->vetor[indice] = novo;
	
}

int buscar_hash(tabela_hash *tabela, int v){
	int indice = v % 10;

	no_hash *aux = tabela->vetor[indice];

	while(aux != NULL && aux->valor != v){
		aux = aux->prox;
	}

	if(aux == NULL){
		return 0;
	}

	return 1;
}

void executafuncao (){   										// É dentro desta função que o aluno deverá escrever seu código
	fila *fi = inicializar_fila();
    tabela_hash *th = inicializar_hash();

    if (fi == NULL || th == NULL) {
        printf("\nErro de alocacao nas estruturas de dados\n");
        return;
    }

    inserir_hash(th, 1);
    enqueue(fi, 1);

    printf("\nordem de visitacao:\n ");

    while (fi->inicio != NULL) {
        int u = dequeue(fi);
        printf("%d ", u);

        for (int v = 1; v <= n; v++) {
            if (matriz_adj[u][v] != 0 && !buscar_hash(th, v)) {
                inserir_hash(th, v);
                enqueue(fi, v);
            }
        }
    }
    printf("\n\n");

    free(fi);
    free(th);
}

	
}



}


int main() {
	opcao = 1;

    while(opcao != 0){
        inicio:
        tamanho = 0;
        m = 0;
        digrafo = 0;
        system("cls"); 
        fflush(stdin); 
        printf("Digite o nome do arquivo (sem o .txt): ");
        gets(nome_arquivo);
        FILE *arquivo; 
        strcat(nome_arquivo,".txt"); 
            
        if((arquivo = fopen(nome_arquivo,"r")) != NULL){
        	while(fgets(aux, MAX, arquivo)) { 
                   char *elemento; 
                   elemento = strtok(aux, " ");
                    while (elemento != NULL){
                        elemento = strtok(NULL, " "); 
                    }
                    tamanho = tamanho + 1; 
                }
                fclose(arquivo);
                
                printf ("\n --------------------------- MATRIZ DE ADJACÊNCIA ---------------------------\n");
                
                if((arquivo = fopen(nome_arquivo,"r")) != NULL){
                    printf("\n");
                    for(int i = 1; i <= tamanho; i++){
                        for(int j = 1; j <= tamanho; j++){
                            fscanf(arquivo, "%d", &matriz_adj[i][j]);
							printf("%3d ", matriz_adj[i][j]); 
                        }
                        printf("\n");
                    }
                }
                fclose(arquivo);
				n = tamanho;
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (matriz_adj[i][j] != matriz_adj[j][i]) {
							digrafo = 1;   // É dígrafo
						}
					}
				}
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (digrafo == 1 && matriz_adj[i][j] != 0) {
							m = m + 1;
						} 
						if (digrafo == 0 && matriz_adj[i][j] != 0 && i <= j) {
							m = m + 1;
						}
					}
				}
				
	          printf ("\nN = %d e M = %d \n \n",n,m);     
            } else {
                printf("\nErro ao abrir o arquivo/Erro ao localizar o arquivo\n\n");
                
            }
        	  
		executafuncao ();       
        printf("\nDigite 0 para sair ou qualquer outra coisa para continuar: ");
		scanf("%d", &opcao);
        
    }
    return 0;
}

