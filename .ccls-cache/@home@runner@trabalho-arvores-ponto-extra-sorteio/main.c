
/***********
+------------------------------------------+
| INSTITUTO FEDERAL DO MARANHÃO            |
| SISTEMAS DE INFORMAÇÃO                   |
| ALG. E ESTRUTUTURAS DE DADOS I           |
| Professor Gentil Cutrim                  |
| Acadêmico: Valter Oliveira & Pedro Lemos |
+------------------------------------------+
organizando os dados de acordo com a quantidade de comparecimentos

DADOS A CONSIDERAR -------------------------
* jair bolsonaro - 22
* lula           - 13
* branco         - 95
* nulo           - 96
*/

/*INCLUSÃO DAD BIBLIOTECAS  */
#include "template.h"
//#include "operacoesArvore.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*ESTRUTURA DA BASE DE ENTRADA DE DADOS  */
typedef struct {
  int NR_ZONA;
  int NR_SECAO;
  int QT_APTOS;
  int QT_COMPARECIMENTO;
  int QT_ABSTENCOES;
  int NR_VOTAVEL;
  char NM_VOTAVEL[20];
  int QT_VOTOS;
  
} Dados;

typedef struct{
int NumTotZona;
int NumTotSecao;
int QuantCom;
int QuantAbs;
int QuanVot;
}Dadoss;

typedef Dados elemento;
typedef Dadoss contagem;
const elemento VL_NULO = {0,  0,  0,  0,  0,  0,"" ,  0};
const contagem NULO = {0, 0, 0, 0, 0};

#include "tad_arvore.h"

//#### PROTÓTIPOS DAS FUNÇÕES #########
void imprimir(elemento e);
int abrir_dados(tree *arvore);
void montaTela();
void teste();
void imprimeArvore(tree a, int nivel);
int comparaelementos(elemento item1, elemento item2);
void navegar_arvore_em_ordem(tree e, void(executar)(elemento a));
void imprimir_z_eleitoral(tree e, elemento a);
void imprimir_zona_eleitoral(elemento e);
void DadosGerais(contagem cont);
contagem Total(contagem cont);

// elementos internos
//######### MAIN ######################
tree arv;

int main() {

  // incluirNaArvore(&arv, &elem);
  define(&arv);
  int op;
  elemento elem;

  do {

    montaTela();
    scanf("%d", &op);

    switch (op) {

    case 1:
      limpatela();
      abrir_dados(&arv);
      break;

    case 2:
      navegar_arvore_em_ordem(arv, imprimir_zona_eleitoral);
     
      pausa();
      pausa();
      limpatela();
      break;

    case 3:
      imprimeArvore(arv,0);
      pausa();
      pausa();
      limpatela();
      break;

    case 4:
      exit(1);
      break;
    }

  } while (1);

  return 0;
}

//#########  FUNÇÕES  ############
// carregar dados;
int abrir_dados(tree *arvore) {
  char S[20];
  elemento e, aux,  item1, item2;
  contagem cont;
  char *ptr;
  FILE *arq;
  int i = 0, num;
  int fgetc(FILE * arq);
  arq = fopen("arquivosCand.txt", "r");
  e = VL_NULO;
  cont = NULO;
  aux = VL_NULO;
  while (EOF != fscanf(arq, "%[^\n]\n", S)) {

    ptr = strtok(S, "\t");
    num = converterInteiro(ptr);
    e.NR_ZONA = num;
    ptr = strtok(NULL, "\t");
    num = converterInteiro(ptr);
    e.NR_SECAO = num;
    ptr = strtok(NULL, "\t");
    num = converterInteiro(ptr);
    e.QT_APTOS = num;
    ptr = strtok(NULL, "\t");
    num = converterInteiro(ptr);
    e.QT_COMPARECIMENTO = num;
    ptr = strtok(NULL, "\t");
    num = converterInteiro(ptr);
    e.QT_ABSTENCOES = num;
    ptr = strtok(NULL, "\t");
    num = converterInteiro(ptr);
    e.NR_VOTAVEL = num;
    ptr = strtok(NULL, "\t");
    strcpy(e.NM_VOTAVEL, ptr);
    ptr = strtok(NULL, "\t");
    num = converterInteiro(ptr);
    e.QT_VOTOS = num;

if ( e.NR_ZONA != aux.NR_ZONA)
   cont.NumTotZona = cont.NumTotZona + 1;

if (aux.NR_SECAO != e.NR_SECAO)
   cont.NumTotSecao = cont.NumTotSecao + 1;
    
cont.QuantAbs = cont.QuantAbs + e.QT_ABSTENCOES;
cont.QuantCom = cont.QuantCom + e.QT_COMPARECIMENTO;
cont.QuanVot = cont.QuanVot + e.QT_VOTOS;

//verificador
  // imprimir(e);
  //  printf(".");
//DadosGerais(cont);    
  aux = e;
    
  adicionar_elemento_arvore(arvore, e, comparaelementos);
  //  pausa();
  }
  //fim da leitura do arquivo de Texto
  printf("\n\n +++++ DADOS CARREGADOS +++++ \n\n");
  DadosGerais(cont);
  
}
// imprimir zona eleitoral
void imprimir_zona_eleitoral(elemento e) { 
  printf("ZONA: %d - SECAO: %d - COMPARECIMENTOS: %d - VOTO: %s : %d \n", e.NR_ZONA, e.NR_SECAO, e.QT_COMPARECIMENTO, e.NM_VOTAVEL, e.QT_VOTOS);
}
// montar a tela
void montaTela() {
  printf("\n- Análise de dados Candidatos -\n");
  printf("1\t Carregar dados;\n");
  printf("2\t Listar zona eleitoral por quant. comparecimento;\n");
  printf("3\t Imprimir TODA a árvore;\n");
  printf("4\t sair;\n");
  printf("\nopção escolhida ->  ");
}
//comparar elementos


int comparaelementos(elemento item1, elemento item2) {
  if (item1.NR_ZONA == item2.NR_ZONA)
    return 1; // inserir a direita
  if (item1.NR_ZONA > item2.NR_ZONA || item1.NR_ZONA < item2.NR_ZONA)
    return -1; // inserir a esquerda
  // if(item1.NR_ZONA == item2.NR_ZONA)
  //   return 0;
  // return item1.NR_ZONA - item2.NR_ZONA;
}

//navegacao em ordem
void navegar_arvore_em_ordem(tree e, void ( executar )(elemento a)) {
  if(vazia(e))
    return;
  navegar_arvore_em_ordem(e->esq, executar);
  executar(e->info);
  navegar_arvore_em_ordem(e->dir, executar);
}
//imprimir a arvoore
void imprimeArvore(tree e, int nivel) {
  if (e != NULL) {
    for (int i = 1; i <= nivel; i++, printf(".."))
      ;
    printf("Zona: %d, Seção: %d, NumCand.: %d, NomeCand.: %s Votos %d\n",
           e->info.NR_ZONA, e->info.NR_SECAO, e->info.NR_VOTAVEL,
           e->info.NM_VOTAVEL, e->info.QT_VOTOS);
    imprimeArvore(e->esq, nivel + 1);
    imprimeArvore(e->dir, nivel + 1);
  }
}

void DadosGerais(contagem cont){
printf("\nDADOS TOTAIS--------------\n");
printf("Total Zonas: %d\n",cont.NumTotZona);
printf("Total Seções: %d\n",cont.NumTotSecao);
printf("Comparecimentos: %d\n",cont.QuantCom);
printf("Abstenções: %d\n",cont.QuantAbs);
printf("Numero total de votos: %d\n",cont.QuanVot);
printf("---------------------------\n");
}












//NAO UTILIZADO.........

void imprimir(elemento e) {
  printf("\n----- Exibindo dados --------\n");
  printf("NR_ZONA: %d\n", e.NR_ZONA);
  printf("NR_SECAO: %d\n", e.NR_SECAO);                   // deve ser inteiro
  printf("QT_APTOS: %d\n", e.QT_APTOS);                   // deve ser inteiro
  printf("QT_COMPARECIMENTO: %d\n", e.QT_COMPARECIMENTO); // deve ser inteiro
  printf("QT_ABSTENCOES: %d\n", e.QT_ABSTENCOES);         // deve ser inteiro
  printf("NR_VOTAVEL: %d\n", e.NR_VOTAVEL);
  printf("NM_VOTAVEL: %s\n", e.NM_VOTAVEL);
  printf("QT_VOTOS: %d\n", e.QT_VOTOS); // deve ser inteiro
  printf("\n-----------------------------\n");
}




