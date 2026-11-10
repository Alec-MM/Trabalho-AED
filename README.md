# Trabalho-AED

## Problemas encontrados no código fornecido pelo professor

O arquivo `Tema_5/Projeto/Tema_5.cpp` **não pode ser alterado** (fora da função `executafuncao`), sob pena de nota zero. Os pontos abaixo foram verificados em testes e servem para a equipe saber o que evitar.

### Problemas que deixam o resultado errado

#### 1. Grafos com mais de 50 vértices são lidos errado

O slide permite grafos de **1 a 100 vértices**, mas a leitura usa `fgets(aux, MAX, arquivo)` com `aux[MAX]` e `MAX = 101`. Uma linha da matriz com `n` vértices tem cerca de `2n` caracteres. Quando a linha passa de 100 caracteres, o `fgets` a lê em dois pedaços, e cada pedaço é contado como uma linha (`tamanho` fica errado).

| Vértices no arquivo | Resultado do programa |
|---|---|
| 50  | `N = 50` (correto) |
| 51  | `N = 102` (errado, matriz embaralhada) |
| 100 | `N = 200` (errado, e escreve fora dos limites de `matriz_adj[101][101]`) |

No caso de 100 vértices há escrita fora da matriz (comportamento indefinido): o programa pode travar ou corromper outras variáveis globais.

#### 2. Linha em branco no fim do arquivo quebra a leitura

Uma quebra de linha extra no final do `.txt` é contada como mais uma linha. Exemplo testado: matriz 2x2 com uma linha vazia no fim foi lida como `N = 3`, com a matriz errada.

Espaço sobrando no fim das linhas **não** causa problema.

### Cuidados para o código da equipe

3. **Arquivo não encontrado:** o `main` mostra o erro e chama `executafuncao()` mesmo assim. Nesse caso `tamanho` vale 0, mas `n` e `matriz_adj` continuam com o grafo do arquivo anterior. A função deve começar verificando `if (tamanho == 0) return;`.
4. **Não usar a variável global `opcao` no menu da função:** ela controla o laço do `main`. Usar uma variável própria (ex.: `opcao_menu`).
5. **`fflush(stdin)`** só funciona no Windows (comportamento indefinido no padrão C). Apresentar em Windows.
6. **`nome_arquivo[50]` com `gets`:** nomes com mais de ~45 caracteres estouram o vetor. Usar nomes curtos e deixar o `.txt` na mesma pasta do executável.
7. **`gets` e a extensão `.cpp`:** `gets` foi removida do C11 e do C++14. Com o MinGW (GCC 8.1 do CodeBlocks) o código compila normalmente, tanto como C quanto como C++. Se aparecer erro, provavelmente é o IntelliSense do VS Code ou um compilador diferente. **Não trocar por `fgets`**: o `fgets` guarda o `\n` e o nome do arquivo ficaria `"nome\n.txt"`.

### Regras para os arquivos de teste

- No máximo **50 vértices**.
- **Nenhuma linha em branco** no final do arquivo.
- Vértices começam em 1 (não existe vértice 0).

## Como executar os testes de 50 e 51 vértices

Estes passos rodam o `Tema_5.cpp` para mostrar o problema 1. O erro está na leitura feita pelo `main` do professor, então aparece mesmo depois que a equipe escrever a `executafuncao()`. Abra um **cmd** (no terminal do VS Code, escolha Command Prompt) na pasta do projeto.

**1. Deixar o compilador disponível** (só é necessário se `g++ --version` não funcionar; ajuste o caminho se o seu MinGW estiver em outra pasta):

```cmd
set "PATH=C:\Program Files (x86)\CodeBlocks\MinGW\bin;%PATH%"
```

**2. Compilar:**

```cmd
if not exist build mkdir build
g++ -g -o build\tema5.exe "Tema_5\Projeto\Tema_5.cpp"
```

**3. Executar a partir da pasta dos testes:**

```cmd
cd Tema_5\Entrada
..\..\build\tema5.exe
```

**4. Digitar no programa, nesta ordem:**

| Quando aparecer | Digite | O que deve mostrar |
|---|---|---|
| `Digite o nome do arquivo` | `grafo3` | Matriz 50 x 50 e `N = 50 e M = 50` |
| `Digite 0 para sair...` | `1` | A tela limpa e pede outro arquivo |
| `Digite o nome do arquivo` | `grafo51` | Matriz 102 x 102 e `N = 102 e M = 104` |
| `Digite 0 para sair...` | `0` | O programa encerra |

Digite o nome **sem** o `.txt`, porque o programa já acrescenta a extensão.

Depois do `N = ...`, o programa executa a `executafuncao()`. Enquanto ela for a do professor, só aparece `deu certo`. Quando tiver o código da equipe, siga o que ela pedir (por exemplo, sair do menu da tabela hash) até voltar ao `Digite 0 para sair...`.

**Dicas:**

- **Matriz quebrando na tela:** ela é mais larga que o terminal. Maximize o painel e procure a linha do `N`, logo abaixo da matriz.
- **`M` diferente de 104:** pode acontecer, porque esse valor depende da memória fora da matriz. O `N = 102` é o que prova o erro.
- **"Erro ao abrir o arquivo":** você não está em `Tema_5\Entrada`, ou o nome foi digitado errado.
- **Terminal PowerShell:** o `set` não funciona lá. Use `$env:Path = "C:\Program Files (x86)\CodeBlocks\MinGW\bin;$env:Path"`.
- **Se o segundo arquivo não for pedido corretamente:** digite `0` para sair e rode o passo 3 de novo para cada teste.
