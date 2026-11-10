#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 101

// ATENÇÃO: O cálculo da complexidade deve incluir todo o ccodigo, inclusive a leitura do arquivo.


char nome_arquivo[50], aux[MAX];								// proibido alterar esta linha
int opcao, tamanho, i, j, n, m, digrafo, matriz_adj[MAX][MAX];  // proibido alterar esta linha
// Declare variáveis globais a partir daqui.



void executafuncao (){   										// É dentro desta função que o aluno deverá escrever seu código
int x = 0;
if (!x) {
printf ("deu certo\n");
}

    typedef struct node{
        int valor;
        struct node * prox;

    }node;

    node * tabela_hash[10]; // vai de 0 a 9
    node * vertice_atual;
    node * vertice_anterior;
    node * vertice_novo;
    int fila_busca_largura[MAX]; // necessária para uma busca horizontal
    int vertice_visitado[MAX];
    int ordem_busca_em_largura[MAX];
    int quantidade_vertices_busca_em_largura = 0;
    int frente, fim;
    int inicio, origem, v, w, k ,c; //para auxiliar nos loops de repetição
    int  valor,chave ,existe;

    if (tamanho == 0){
    printf("nenhum arquivo inicializado \n");
        return;
    }

    for (v = 1; v<= n ; v++) // O(n)
    {
        vertice_visitado[v] = 0;
    }
    
    for (k = 1; k<= n; k ++){ // O(n); a busca completa custa O(n²)
        origem = k;
        if(vertice_visitado[origem]){
            continue;
        }
    

        frente = 0;
        fim = 0;
        vertice_visitado[origem] = 1;
        fila_busca_largura[fim++] = origem;                // enfileira a origem

        while (frente < fim) // O(n) no total entre as buscas
        {
            v = fila_busca_largura[frente++];
            ordem_busca_em_largura[quantidade_vertices_busca_em_largura ++] = v;

            for (w = 1; w<= n; w ++) // O(n) por vértice; O(n²) no total
            {
                if(matriz_adj[v][w] !=0 && !vertice_visitado[w]){
                    vertice_visitado [w] = 1;
                    fila_busca_largura [fim++] = w;
                }
            }
            
        }
        
    }

    printf("realizando a busca em largura\n");
    for (k = 0; k< quantidade_vertices_busca_em_largura; k ++){ // O(n)
        printf("%d ", ordem_busca_em_largura[k]);
    }
    printf("\n");
    
    printf("Transformando a saida da busca em um valor na tabela hash\n");

    for( k = 0; k < 10; k ++){ // O(1)
        tabela_hash[k] = NULL;
    }
    
    for (k = 0; k < quantidade_vertices_busca_em_largura; k++) { // O(n); com o while, O(n²) no pior caso
        valor = ordem_busca_em_largura[k];
        chave = valor % 10;                  

        vertice_novo = (node *) malloc(sizeof(node));
        if (vertice_novo == NULL) {                 
            printf(" erro: memoria insuficiente\n");
            break;
        }
        vertice_novo->valor = valor;
        vertice_novo->prox = NULL;

        if (tabela_hash[chave] == NULL) {
            tabela_hash[chave] = vertice_novo;
        } else {                             
            vertice_atual = tabela_hash[chave];
            while (vertice_atual->prox != NULL) { // O(n) no pior caso por inserção
                vertice_atual = vertice_atual->prox;
            }
            vertice_atual->prox = vertice_novo;
        }
    }

    opcao = 3;
    do // Depende da quantidade de opções do usuário
    {
        switch (opcao){
            case 1:
            case 2:
                if (opcao == 1) {
                        printf(" valor a inserir: ");
                } else {
                        printf(" valor a retirar: ");
                }  
                while (scanf("%d", &valor) != 1) { // Depende da entrada
                    while ((c = getchar()) != '\n' && c != EOF) { } // Depende do tamanho da entrada inválida
                    printf(" valor invalido, digite um numero inteiro: ");
                }

                chave = ((valor % 10) + 10) % 10;
                vertice_anterior = NULL;
                vertice_atual = tabela_hash[chave];
                while (vertice_atual != NULL && vertice_atual->valor != valor) { // O(k)
                    vertice_anterior = vertice_atual;
                    vertice_atual = vertice_atual->prox;
                }

                existe = (vertice_atual != NULL);
                if (opcao == 1) {
                    if (existe) {            // valores repetidos nao sao aceitos
                        printf(" %d ja existe na tabela\n", valor);
                    } else {
                        vertice_novo = (node *)malloc(sizeof(node));
                        if (vertice_novo == NULL) {
                            printf(" erro: memoria insuficiente\n");
                        } else {
                            vertice_novo->valor = valor;
                            vertice_novo->prox = NULL;
                            if (vertice_anterior == NULL) {
                                tabela_hash[chave] = vertice_novo;
                            } else {
                                vertice_anterior->prox = vertice_novo;
                            }
                            printf(" %d inserido na chave %d\n", valor, chave);
                        }
                    }
                } else {
                    if (!existe) {
                        printf(" %d nao esta na tabela\n", valor);
                    } else {
                        if (vertice_anterior == NULL) {   
                            tabela_hash[chave] = vertice_atual->prox;
                        } else {                     
                            vertice_anterior->prox = vertice_atual->prox;
                        }
                        free(vertice_atual);
                        printf(" %d retirado da chave %d\n", valor, chave);
                    }
                }
                break;

            case 3:                          // ----- mostrar toda a estrutura: o(10 + k) = o(k) -----
                printf("\n |-------------------- tabela hash --------------------|\n");
                for (k = 0; k < 10; k++) { // O(1); com o while, O(k)
                    printf(" [%d] ", k);
                    vertice_atual = tabela_hash[k];
                    while (vertice_atual != NULL) { // O(k) no total entre as chaves
                        printf("%d -> ", vertice_atual->valor);
                        vertice_atual = vertice_atual->prox;
                    }
                    printf("null\n");
                }
                break;

            default:
                printf(" opcao invalida\n");
        }

        // le a proxima opcao do menu
        printf("\n 1 - inserir\n 2 - retirar\n 3 - mostrar toda a estrutura\n 0 - voltar\n opcao: ");
        while (scanf("%d", &opcao) != 1) { // Depende da entrada
            while ((c = getchar()) != '\n' && c != EOF) { } // Depende do tamanho da entrada inválida
            printf(" opcao invalida, digite um numero: ");
        }
    } while (opcao != 0); // Depende da quantidade de opções do usuário

    // libera todos os nos da tabela, para nao vazar memoria ao ler outro arquivo.
    // complexidade: o(10 + k) = o(k)
    for (k = 0; k < 10; k++) {               
        vertice_atual = tabela_hash[k];
        while (vertice_atual != NULL) {      // laco: libera cada no da lista
            vertice_novo = vertice_atual->prox; // guarda o proximo antes de liberar o atual
            free(vertice_atual);
            vertice_atual = vertice_novo;
        }
        tabela_hash[k] = NULL;
    }

    // o menu terminou com opcao = 0. devolve opcao = 1 para o usuario
    opcao = 1;

    // codigo do prof tem complexidade O(n^2)
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

