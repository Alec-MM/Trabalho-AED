#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 101

// ATENÇÃO: O cálculo da complexidade deve incluir todo o codigo, inclusive a leitura do arquivo.

char nome_arquivo[50], aux[MAX];								// proibido alterar esta linha
int opcao, tamanho, i, j, n, m, digrafo, matriz_adj[MAX][MAX];  // proibido alterar esta linha
// Declare variáveis globais a partir daqui.

// estrutura simples para os nos da tabela hash
struct no {
    int valor;
    struct no *prox;
};

// vetor de ponteiros pra nossa tabela hash (tamanho 10)
struct no *tabela[10];

// inicializa a tabela hash com ponteiros nulos
// complexidade: o(1). esse for roda cravado 10 vezes sempre, nao depende do tamanho do grafo.
void inicializa_hash() {
    for(int k = 0; k < 10; k++) {
        tabela[k] = NULL;
    }
}

// insere na hash usando a regra do resto da divisao por 10
// complexidade: o(1). aloca o no e joga no comeco da lista, sem laco de repeticao.
void insere_hash(int val) {
    int chave = val % 10;
    struct no *novo = (struct no*) malloc(sizeof(struct no));
    novo->valor = val;
    novo->prox = tabela[chave];
    tabela[chave] = novo;
}

// remove um valor especifico da tabela hash
// complexidade: o(v) no pior caso. tem um while que percorre a lista encadeada.
// se todos os vertices cairem na mesma chave, ele roda 'v' vezes.
void remove_hash(int val) {
    int chave = val % 10;
    struct no *atual = tabela[chave];
    struct no *ant = NULL;

    // procura o valor na lista dessa chave especifica
    while(atual != NULL && atual->valor != val) {
        ant = atual;
        atual = atual->prox;
    }

    // se chegou no final e nao achou
    if(atual == NULL) {
        printf("o valor %d nao ta na hash.\n", val);
        return;
    }

    // se o elemento for o primeiro da lista ou estiver no meio/fim
    if(ant == NULL) {
        tabela[chave] = atual->prox;
    } else {
        ant->prox = atual->prox;
    }
    free(atual);
    printf("valor %d removido com sucesso.\n", val);
}

// mostra como a estrutura da tabela hash ta organizada no momento
// complexidade: o(v). o for roda 10 vezes, e o while interno vai
// rodar no maximo 'v' vezes no total (somando todos os elementos inseridos).
void mostra_hash() {
    printf("\n--- estrutura da hash ---\n");
    for(int k = 0; k < 10; k++) {
        printf("[%d]: ", k);
        struct no *atual = tabela[k];
        while(atual != NULL) {
            printf("%d -> ", atual->valor);
            atual = atual->prox;
        }
        printf("null\n");
    }
}

// faz a busca em largura e joga os resultados direto na hash
// complexidade da busca: o(v^2).
// o laco while roda 'v' vezes (pra cada vertice na fila)
// o laco for interno tbm roda 'v' vezes pra checar as conexoes na matriz.
void bfs(int inicio) {
    int visitados[MAX];
    int fila[MAX];
    int ini_fila = 0, fim_fila = -1;

    // zera o vetor de visitados, roda 'v' (tamanho) vezes -> o(v)
    for(int k = 1; k <= tamanho; k++) {
        visitados[k] = 0;
    }

    fila[++fim_fila] = inicio;
    visitados[inicio] = 1;

    printf("\nresultado da busca em largura (bfs): ");

    // laco principal da bfs
    while(ini_fila <= fim_fila) {
        int atual = fila[ini_fila++];
        printf("%d ", atual);

        // insere o vertice visitado na nossa tabela hash
        insere_hash(atual);

        // procura os vizinhos na matriz de adjacencia
        for(int k = 1; k <= tamanho; k++) {
            if(matriz_adj[atual][k] != 0 && visitados[k] == 0) {
                fila[++fim_fila] = k;
                visitados[k] = 1;
            }
        }
    }
    printf("\n");
}


void executafuncao (){   										// É dentro desta função que o aluno deverá escrever seu código
    
    inicializa_hash();
    
    // pelo requisito do prof, o grafo comeca no vertice 1
    bfs(1);
    
    int op_menu = -1;
    int val;
    
    // menu pro usuario interagir com a hash
    // complexidade: o(1) de processamento a cada ciclo, so depende do usuario digitar.
    while(op_menu != 0) {
        printf("\n--- menu ---\n");
        printf("1 - inserir na hash\n");
        printf("2 - retirar da hash\n");
        printf("3 - mostrar estrutura\n");
        printf("0 - sair\n");
        printf("opcao: ");
        scanf("%d", &op_menu);
        
        if(op_menu == 1) {
            printf("qual valor quer inserir? ");
            scanf("%d", &val);
            insere_hash(val);
        } else if(op_menu == 2) {
            printf("qual valor quer remover? ");
            scanf("%d", &val);
            remove_hash(val);
        } else if(op_menu == 3) {
            mostra_hash();
        } else if(op_menu != 0) {
            printf("opcao invalida.\n");
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
        printf("digite o nome do arquivo (sem o .txt): ");
        gets(nome_arquivo);
        FILE *arquivo; 
        strcat(nome_arquivo,".txt"); 
            
        // complexidade da contagem de tamanho: o(l) onde l e o numero de linhas do arquivo. o laco while usa strtok.
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
                
                printf ("\n --------------------------- matriz de adjacencia ---------------------------\n");
                
                // complexidade da leitura da matriz: o(v^2). lacos for aninhados rodando 'tamanho' vezes cada.
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
				
                // complexidade para checar se e digrafo: o(v^2). lacos aninhados rodando 'tamanho' vezes.
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (matriz_adj[i][j] != matriz_adj[j][i]) {
							digrafo = 1;   // e digrafo
						}
					}
				}
				
                // complexidade da contagem de arestas: o(v^2) por causa dos dois lacos de repeticao.
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
				
	          printf ("\nn = %d e m = %d \n \n",n,m);     
            } else {
                printf("\nerro ao abrir o arquivo/erro ao localizar o arquivo\n\n");
                
            }
        	  
		executafuncao ();       
        printf("\ndigite 0 para sair ou qualquer outra coisa para continuar: ");
		scanf("%d", &opcao);
        
    }
    return 0;
}