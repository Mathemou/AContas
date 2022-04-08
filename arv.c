#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv.h"
#include "math.h"

/*----------------------------------------------------------------------
 * Essa variavél global foi declarada com a justificativa de poder     |
 * acessa-la fora do escopo da função e zerar seu conteúdo, evitando   |
 * que a recursividade possa impactar no valor que os nós devem ter    |
 ---------------------------------------------------------------------*/
static int pos = 0;

/*----------------------------------------------------------------------
 * Estrutura de nós da árvore, armazena informações sobre o conteúdo do|
 * nó e dos seus respectivos galhos a esquerda e a direita             | 
 ---------------------------------------------------------------------*/
struct arv {
    char op; //Guarda a operação que o nó representa;
    float num; // Guarda o número que o nó representa;
    Arv * esq; // Aponta para a árvore á esqueda do nó;
    Arv * dir; // Aponta para o árvore á direita do nó;
    int pos; //Inidca a posição dele na leitura dos arquivos;
};

/*----------------------------------------------------------------------
 * Retorna NULL para ser usado em um nó folha ou que ainda nõa tem seus|
 * galhos definidos                                                    | 
 --------------------------------------------------------------------*/
Arv * arv_criaVazia(){
    return NULL; 
}

/*---------------------------------------------------------------------
 * Cria um nó que ainda terá seus valores definido no decorrer da     |
 * leitura                                                            |
 --------------------------------------------------------------------*/
Arv * arv_criaSemConteudo(){
  Arv* p=(Arv*)malloc(sizeof(Arv));
  p->num = -1;
  p->op = 'a';
  p->esq = arv_criaVazia();
  p->dir = arv_criaVazia();
  return p;
}

/*---------------------------------------------------------------------
 * LIbera a memória alocada para essa árvore e seus galhos            |
 --------------------------------------------------------------------*/
Arv * arv_libera (Arv * arv){
    if (!arv_vazia(arv)){
        arv_libera(arv->esq);
        arv_libera(arv->dir);
        free(arv);
    }
    return NULL;
}

/*---------------------------------------------------------------------
 * Verifia de a árvore está vazia retornando 1 (true) se estiver ou 0 |
 * (false) se não estiver                                             |
 --------------------------------------------------------------------*/
int arv_vazia (Arv * arv){
    return arv==NULL;
}

/*---------------------------------------------------------------------
 * Calcula o valor da operação do nó, usando os dois nós folhas       |
 * apontados por esse nó pai, atribuindo, ao final, o resultado ao    |
 * conteúdo do prório nó, possibilitando fazer as outras operações, se|
 * houver, de maneira recursiva                                       |
 --------------------------------------------------------------------*/
void arv_calcula(Arv *arv){
  
  if(ehFolha(arv)){
    return; //Caso o nó seja uma folha, nenhuma operação pode ser realizada;
  }

  //Verifica o tipo de operação daquele nó;
  switch (arv->op){
    case '-':
      arv->num = arv->esq->num - arv->dir->num;
      break;
    case '+':
      arv->num = arv->esq->num + arv->dir->num;
      break;
    case '/':
      arv->num = arv->esq->num / arv->dir->num;
      break;
    case '*':
      arv->num = arv->esq->num * arv->dir->num;
      break;
  }

  //Libera a memória alocada para as folhas e faz os endereços para elas apontarem para NULL;
  arv_libera(arv->esq);
  arv_libera(arv->dir);
  arv->esq = arv_criaVazia();
  arv->dir = arv_criaVazia();
}

/*---------------------------------------------------------------------
 * Calcula o valor final da arvore raiz obtida pela leituda da entrada|
 * e atribui esse valor a uma arvore folha, que já foi o nó raiz da   |
 * expressão usando recursividade                                     |
 --------------------------------------------------------------------*/
void arv_calcula_raiz(Arv * arv){
  if(!ehFolha(arv)){ //Apenas prossegue com o cálculo se o nó não for folha;
  if (ehFolha(arv->esq)&&ehFolha(arv->dir)){ //Se ambos os nós forem folhas, realiza o cálculo
    arv_calcula(arv);
  } else { //Se não, tenta calcular o nó da esquerda e da direita;
    arv_calcula_raiz(arv->esq);
    arv_calcula_raiz(arv->dir);
    arv_calcula(arv); //Caso consiga calcular os dois nós, tenta calcular novamente o valor desse nó;
  }
  }
}

/*---------------------------------------------------------------------
 * Printa o valor do número inteiro contido no nó, caso seja um nó de |
 * operação, irá imprimir o número -1 (fora do escopo do trabalho)    |
 --------------------------------------------------------------------*/
void printaIntArvore(Arv * arv){
  printf("%.2f\n", arv->num);
}

/*---------------------------------------------------------------------
 * Printa o caractere referente a operação contido no nó, caso seja um|
 *  nó folha, irá imprimir o caractere 'a', que não corresponde a     |
 * operação aritmética                                                |
 --------------------------------------------------------------------*/
void printaCharArvore(Arv * arv){
  printf("%c\n", arv->op);
}

/*---------------------------------------------------------------------
 * Verifica se o nó é uma folha (nó da esquerda e direita nulos), caso|
 * seja, retorna 1 (true), caso não, retorna 0 (false)                |
 --------------------------------------------------------------------*/
int ehFolha(Arv * arv){
  if (arv->esq==NULL&&arv->dir==NULL){
    return 1;
  } else {
    return 0;
  }
}

/*---------------------------------------------------------------------
 * Verifica se caractere é um número, caso sim, retorna 1 (true), caso|
 * caso não, retorna 0 (false)                                        |
 --------------------------------------------------------------------*/
int EhNumero(char c){
  if (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'){
    return 1;
  }
  return 0;
}

/*---------------------------------------------------------------------
 * Verifica se há uma árvore à esquerda do nó analizado, se tiver,    |
 * retorna 1 (true), se não tiver, retorna 0 (false)                  |
 --------------------------------------------------------------------*/
int temEsquerda(Arv * arv){
  if (arv->esq != NULL){
    return 1;
  } else {
    return 0;
  }
}

/*---------------------------------------------------------------------
 * Le o arquivo entrada.txt e retorna a árvore raiz, que contem todos |
 * os nós com operações e as folhas com os números usando             |
 * recursividade                                                      |
 --------------------------------------------------------------------*/
Arv * LeArvRaiz(FILE * file, Arv * raiz){
  
  pos++;
  raiz->pos = pos;
  
  char c;
  while(1){
    if(fscanf(file, "%c", &c)){}else{exit(0);}
    if (c==')') {
      return raiz;
    }
    if (c=='('&&!temEsquerda(raiz)){
      raiz->esq = LeArvRaiz(file, arv_criaSemConteudo());
    } else if (EhNumero(c)){
      raiz->num = atoi(&c);
      while(1){
        if(fscanf(file, "%c", &c)){}else{exit(0);}
        if(EhNumero(c)){
          raiz->num*=10;
          raiz->num+=atoi(&c);
        } else if(c==')'){
          return raiz;
        }
      }
      
    } else if (c!=')'&&c!='('){
      raiz->op = c;  
    } else if (c=='('&&temEsquerda(raiz)){
      raiz->dir = LeArvRaiz(file, arv_criaSemConteudo());
    } 
  }
}

/*---------------------------------------------------------------------
 * Printa o resultado das expressões da árvore no arquivo saida.txt,  |
 * caso seja um número com casas decimais, printa ele no formato x.xx |
 * caso não, simplesmente printa o número no formato x                |
 --------------------------------------------------------------------*/
void printaResultadoNaSaida(Arv * arv, FILE * saida){
  if(arv->num-floor(arv->num)!=0){
    fprintf(saida, "%.2f\n", arv->num);
  } else {
    fprintf(saida, "%.0f\n", arv->num);
  }
}

/*---------------------------------------------------------------------
 * Escreve no arquivo graphviz.txt, usando resursividade              |
 --------------------------------------------------------------------*/
void geraArquivoGraphviz (Arv * raiz, FILE * graphviz){
  if(ehFolha(raiz)){
    if (raiz->num-floor(raiz->num)!=0){ //Verifica se o número tem casas decimais, por convenção do trabalho, não ocorrerá nenhum caso assim;
      fprintf(graphviz, "no%d[label=\"%.2f\"]\n", raiz->pos, raiz->num);
    } else {
      fprintf(graphviz, "no%d[label=\"%.0f\"]\n", raiz->pos, raiz->num);
    }
  } else {
    fprintf(graphviz, "no%d[label=\"%c\"]\n", raiz->pos, raiz->op);
    fprintf(graphviz, "no%d--no%d\n", raiz->pos, raiz->esq->pos);
    geraArquivoGraphviz(raiz->esq, graphviz);
    fprintf(graphviz, "no%d--no%d\n", raiz->pos, raiz->dir->pos);
    geraArquivoGraphviz(raiz->dir, graphviz);
  }
}

/*---------------------------------------------------------------------
 * Utiliza as funções acima para ler o arquivo de entrada e printar os|
 * resultados nos respectivos arquivos de saída referentes a esses    |
 * resultados, seja ele o resultado do nó raiz ou a representação     |
 * textual da representação gráfica das expressões no                 |
 * https://dreampuf.github.io/                                        |
 --------------------------------------------------------------------*/
void leEntradaEPrintaSaida(){
  FILE * entrada = fopen("entrada.txt", "r");
  
  if (entrada==NULL){
    printf("Não foi possível encontrar o arquivo entrada.txt");
    return;
  }

  FILE * saida = fopen("saida.txt", "w");
  
  if (saida==NULL){
    printf("Não foi possível criar o arquivo saida.txt");
    return;
  }

  FILE * graphviz = fopen("graphviz.txt", "w");
  
  if (graphviz==NULL){
    printf("Não foi possível criar o arquivo graphviz.txt");
    return;
  }

  //Primeira expressão
  char extra;
  if(fscanf(entrada, "%c", &extra)){}else{exit(0);}
  Arv * raiz = LeArvRaiz(entrada, arv_criaSemConteudo());
  pos = 0;
  fprintf(graphviz, "strict graph {\n");
  geraArquivoGraphviz(raiz, graphviz);
  fprintf(graphviz, "}\n");
  arv_calcula_raiz(raiz);
  printaResultadoNaSaida(raiz, saida);
  arv_libera(raiz);
  //Le as demais expressões
  while(1){
    if(fscanf(entrada, "%c", &extra)){}else{exit(0);}
    if(extra!='\n'){
      break;
    }
    if(fscanf(entrada, "%c", &extra)){}else{exit(0);}
    
    Arv * raiz = LeArvRaiz(entrada, arv_criaSemConteudo());
    pos = 0;
    fprintf(graphviz, "strict graph {\n");
    geraArquivoGraphviz(raiz, graphviz);
    fprintf(graphviz, "}\n");
    arv_calcula_raiz(raiz);
    printaResultadoNaSaida(raiz, saida);
    arv_libera(raiz);
  }
  
  fclose(entrada);
  fclose(saida);
  fclose(graphviz);
}