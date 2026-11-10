# Erro diagnosticado: leitura de grafos com mais de 50 vértices

## Resumo

O slide do trabalho diz que o grafo "poderá ter entre 1 e 100 vértices", mas o código fornecido pelo professor só lê corretamente arquivos com **até 50 vértices**.

A partir de 51, cada linha do arquivo é contada duas vezes. O programa acha que o grafo tem o dobro de vértices e a matriz fica errada.

**Não podemos corrigir:** alterar o código fornecido dá nota zero para toda a equipe. O caminho é avisar o professor e deixar a decisão com ele.

## A causa

Trecho do código fornecido (`Tema_5.cpp`, linhas 42 a 48):

```c
while(fgets(aux, MAX, arquivo)) {     // MAX = 101: lê no máximo 100 caracteres por vez
    ...
    tamanho = tamanho + 1;            // conta uma "linha" a cada fgets
}
```

Uma linha com `n` vértices tem `2n` caracteres: `n` dígitos, `n - 1` espaços e o `\n`.

| Vértices | Caracteres na linha | O que o `fgets` faz | `tamanho` |
|---|---|---|---|
| 50 | 100 | lê a linha inteira de uma vez | 50 (certo) |
| 51 | 102 | lê em 2 pedaços (100 + 2) | 102 (errado) |
| 100 | 200 | lê em 2 pedaços (100 + 100) | 200 (errado) |

A regra é: funciona enquanto `2n <= 100`, ou seja, `n <= 50`.

O que acontece depois da contagem errada:

1. O `tamanho` vira o dobro do número real de vértices.
2. A leitura pega `tamanho` números por linha da matriz, então a linha 2 do grafo continua dentro da linha 1 da matriz.
3. O arquivo acaba antes da hora, e as demais posições não recebem dados.
4. Os laços vão além do índice 100, último válido de `matriz_adj[101][101]`.
5. Com `i` maior que 100, o programa lê memória fora da matriz. Por isso o `M` sai errado e pode mudar de uma compilação para outra.

## Resultados medidos

Testes com grafos em ciclo, em que o `M` correto é igual a `N`, usando o `Tema_5.cpp` sem nenhuma alteração. Compilador: GCC 8.1.0.

| Arquivo | Vértices reais | Esperado | Obtido | Situação |
|---|---|---|---|---|
| `teste.txt` (grafo completo) | 4 | N = 4, M = 6 | N = 4, M = 6 | correto |
| `grafo3.txt` | 50 | N = 50, M = 50 | N = 50, M = 50 | correto |
| `grafo51.txt` | 51 | N = 51, M = 51 | **N = 102, M = 104** | errado |
| grafo de 100 vértices | 100 | N = 100, M = 100 | **N = 200, M = 7867** | errado |

O valor de `N` é consequência direta da contagem. O valor de `M` depende do que está na memória depois da matriz, então pode ser diferente em outra máquina.

Os programas terminaram normalmente nesses testes, sem travar. Isso não garante que nunca vão travar, porque acessar fora da matriz tem comportamento indefinido em C.

### Efeito na busca em largura

No programa da equipe (`Tema_5.cpp`), a busca recebe do `main` o `n` errado:

- **Com 51 vértices reais (`grafo51.txt`):** `N = 102`, e a busca mostrou 102 vértices. Metade deles não existe no grafo (52, 54, 56, ...).
- **Com 100 vértices reais:** `N = 200`, mas a busca mostrou só 111 vértices, alguns inexistentes (101, 103, 112, ...). Com `N = 200`, deveria mostrar 200.

O caso de 100 vértices indica **gravação fora do limite** no código da equipe. Os vetores `vertice_visitado`, `fila_busca_largura` e `ordem_busca_em_largura` têm tamanho `MAX` (índices de 0 a 100), mas os laços usam índices até `n = 200`. Já o laço que zera `vertice_visitado` (`for (v = 1; v <= n; v++)`) grava nas posições 101 a 200, que não existem. Essas gravações provavelmente atingem outras variáveis da função, e por isso a busca perdeu vértices. Nos testes o programa não travou, mas isso não é garantido.

A culpa não é da busca: com o `n` certo (até 50 vértices), ela funciona corretamente.

## O que este erro não é

- **Não é estouro do vetor `aux`:** o `fgets` respeita o limite e nunca grava além dele. A causa é a contagem de pedaços como se fossem linhas.
- **Não é causado por começar em 1:** o `tamanho` já sai errado antes de qualquer índice ser usado. Começar em 1 é exigência do slide, e é o que permite usar os índices de 1 a 100 com `MAX 101`.
- **Não acontece por falta de memória do computador:** o limite vem do tamanho da linha lida.
- **As gravações inválidas do teste de 51 não saíram da matriz:** usaram `j` = 101 ou 102, que caem na linha seguinte da própria matriz. O que sai da matriz, nesse teste, são as leituras.

## Como apresentar

### Antes da apresentação

1. Avisar o professor com antecedência, pelo Classroom ou pessoalmente, com a mensagem abaixo. O slide diz que alterações podem ser informadas pelo Classroom.
2. Não mexer no código fornecido, mesmo que a correção pareça simples.
3. Levar os 3 arquivos de teste obrigatórios com no máximo 50 vértices, a menos que o professor oriente outra coisa.
4. Deixar `grafo3.txt` e `grafo51.txt` à mão, para mostrar o limite se ele pedir.
5. Garantir que todos da equipe saibam explicar o erro, porque as perguntas são individuais e os outros ficam fora da sala.

Mensagem sugerida:

> Professor, ao testar o código fornecido para o trabalho, percebemos que arquivos com mais de 50 vértices são lidos incorretamente. O `fgets` lê no máximo 100 caracteres, então cada linha com 51 vértices ou mais é contada duas vezes: um grafo com 51 vértices aparece como N = 102. Como o enunciado prevê até 100 vértices e não podemos alterar o código fornecido, como devemos proceder?

### Durante a apresentação

Fazer primeiro os testes normais, que valem a nota de execução. Mostrar o limite só depois, se o professor permitir ou se um grafo dele cair nesse caso.

Fala sugerida, de cerca de 1 minuto:

> O enunciado prevê até 100 vértices, mas o código fornecido só lê corretamente até 50. Cada vértice ocupa dois caracteres na linha, e o `fgets` lê no máximo 100 por vez. Com 51 vértices, a linha tem 102 caracteres e é lida em dois pedaços. Como o `tamanho` aumenta a cada `fgets`, ele conta 102 vértices em vez de 51, e a matriz fica desalinhada. Não corrigimos porque o código fornecido não pode ser alterado, mas podemos mostrar o comportamento agora.

Não alterem o código durante nem depois da apresentação: o slide também pune isso com nota zero.

### Perguntas prováveis

| Pergunta | Resposta |
|---|---|
| Por que 50 funciona e 51 não? | Uma linha com `n` vértices tem `2n` caracteres, e o `fgets` lê até 100. `2 x 50 = 100` cabe; `2 x 51 = 102` não. |
| O vetor `aux` estoura? | Não. O `fgets` respeita o limite; ele só devolve a linha em pedaços. |
| Onde o programa acessa fora da matriz? | Quando `i` ou `j` passa de 100, o que acontece porque `tamanho` chega a 102 ou mais. |
| Por que o `M` deu um número estranho? | O cálculo lê posições fora da matriz, e esses valores dependem do que está na memória. |
| Por que não corrigiram? | Alterar o código fornecido dá nota zero. Por isso avisamos o professor. |
| Como seria a correção? | Usar um buffer de leitura com espaço para a maior linha, ou contar uma linha só quando o `\n` for encontrado. |
| O problema tem relação com começar em 1? | Não. O `tamanho` já sai errado antes de qualquer índice ser usado. |
| A complexidade muda? | A ordem continua `O(n²)`, mas sobre um `n` errado: com 51 vértices, os laços trabalham com 102. |

## Como demonstrar

Fazer esta demonstração com o programa **sem alterações**, para mostrar que o erro é do código fornecido. Testem antes, no notebook que será usado: o slide proíbe usar a máquina do professor.

### Passo 1: mostrar o tamanho das linhas

Abrir os arquivos de `Tema_5/Entrada` no VS Code, clicar no fim da primeira linha e olhar a coluna na barra inferior:

- `grafo3.txt`: `Col 100`, ou seja, 99 caracteres mais o `\n`, totalizando 100.
- `grafo51.txt`: `Col 102`, ou seja, 101 caracteres mais o `\n`, totalizando 102.

### Passo 2: compilar e rodar

No cmd do VS Code, a partir da pasta do projeto:

```cmd
g++ -g -o build\tema5.exe "Tema_5\Projeto\Tema_5.cpp"
cd Tema_5\Entrada
..\..\build\tema5.exe
```

Se o `g++` não for reconhecido, feche e abra todas as janelas do VS Code. Para resolver só naquele terminal, rode antes:

```cmd
set "PATH=C:\Program Files (x86)\CodeBlocks\MinGW\bin;%PATH%"
```

### Passo 3: comparar 50 e 51

1. Digitar `grafo3` e mostrar `N = 50 e M = 50`.
2. Digitar um valor diferente de 0 para continuar.
3. Digitar `grafo51` e mostrar `N = 102`, acima da matriz que aparece desalinhada.

A matriz de 102 colunas é larga e quebra as linhas no terminal. Maximize a janela e aponte para a linha do `N`. O valor de `M` pode ser diferente do medido aqui.

Nenhuma linha de código precisa ser adicionada para esta demonstração: basta o `grafo51.txt`.
