/*----------------------------------------------------------------------
 * Estrutura de nós da árvore, armazena informações sobre o conteúdo do|
 * nó e dos seus respectivos galhos a esquerda e a direita             | 
 ---------------------------------------------------------------------*/
typedef struct arv Arv;

/*----------------------------------------------------------------------
 * Retorna NULL para ser usado em um nó folha ou que ainda nõa tem seus|
 * galhos definidos                                                    | 
 --------------------------------------------------------------------*/
Arv * arv_criaVazia();

/*---------------------------------------------------------------------
 * Cria um nó que ainda terá seus valores definido no decorrer da     |
 * leitura                                                            |
 --------------------------------------------------------------------*/
Arv * arv_criaSemConteudo();

/*---------------------------------------------------------------------
 * LIbera a memória alocada para essa árvore e seus galhos            |
 --------------------------------------------------------------------*/
Arv * arv_libera (Arv * arv);

/*---------------------------------------------------------------------
 * Verifia de a árvore está vazia retornando 1 (true) se estiver ou 0 |
 * (false) se não estiver                                             |
 --------------------------------------------------------------------*/
int arv_vazia (Arv * arv);

/*---------------------------------------------------------------------
 * Calcula o valor da operação do nó, usando os dois nós folhas       |
 * apontados por esse nó pai, atribuindo, ao final, o resultado ao    |
 * conteúdo do prório nó, possibilitando fazer as outras operações, se|
 * houver, de maneira recursiva                                       |
 --------------------------------------------------------------------*/
void arv_calcula(Arv *arv);

/*---------------------------------------------------------------------
 * Calcula o valor final da arvore raiz obtida pela leituda da entrada|
 * e atribui esse valor a uma arvore folha, que já foi o nó raiz da   |
 * expressão usando recursividade                                     |
 --------------------------------------------------------------------*/
void arv_calcula_raiz(Arv * arv);

/*---------------------------------------------------------------------
 * Printa o valor do número inteiro contido no nó, caso seja um nó de |
 * operação, irá imprimir o número -1 (fora do escopo do trabalho)    |
 --------------------------------------------------------------------*/
void printaIntArvore(Arv * arv);

/*---------------------------------------------------------------------
 * Printa o caractere referente a operação contido no nó, caso seja um|
 *  nó folha, irá imprimir o caractere 'a', que não corresponde a     |
 * operação aritmética                                                |
 --------------------------------------------------------------------*/
void printaCharArvore(Arv * arv);

/*---------------------------------------------------------------------
 * Verifica se o nó é uma folha (nó da esquerda e direita nulos), caso|
 * seja, retorna 1 (true), caso não, retorna 0 (false)                |
 --------------------------------------------------------------------*/
int ehFolha(Arv * arv);

/*---------------------------------------------------------------------
 * Verifica se caractere é um número, caso sim, retorna 1 (true), caso|
 * caso não, retorna 0 (false)                                        |
 --------------------------------------------------------------------*/
int EhNumero(char c);

/*---------------------------------------------------------------------
 * Verifica se há uma árvore à esquerda do nó analizado, se tiver,    |
 * retorna 1 (true), se não tiver, retorna 0 (false)                  |
 --------------------------------------------------------------------*/
int temEsquera(Arv * arv);

/*---------------------------------------------------------------------
 * Le o arquivo entrada.txt e retorna a árvore raiz, que contem todos |
 * os nós com operações e as folhas com os números usando             |
 * recursividade                                                      |
 --------------------------------------------------------------------*/
Arv * LeArvRaiz(FILE * file, Arv * raiz);

/*---------------------------------------------------------------------
 * Printa o resultado das expressões da árvore no arquivo saida.txt   |
 --------------------------------------------------------------------*/
void printaResultadoNaSaida(Arv * arv, FILE * saida);

/*---------------------------------------------------------------------
 * Escreve no arquivo graphviz.txt, usando resursividade              |
 --------------------------------------------------------------------*/
void geraArquivoGraphviz (Arv * raiz, FILE * graphviz);

/*---------------------------------------------------------------------
 * Utiliza as funções acima para ler o arquivo de entrada e printar os|
 * resultados nos respectivos arquivos de saída referentes a esses    |
 * resultados, seja ele o resultado do nó raiz ou a representação     |
 * textual da representação gráfica das expressões no                 |
 * https://dreampuf.github.io/                                        |
 --------------------------------------------------------------------*/
void leEntradaEPrintaSaida();