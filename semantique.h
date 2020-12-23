#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include"syntax.h"
typedef enum{TPROG, TCONST,TVAR}TSYM;
typedef struct{
  char* NOM;
  TSYM TIDF;
}T_TAB_IDF;
int i;
int sem;
T_TAB_IDF TAB_IDFS[40];
void remplir_tab();
void TABLEAU_IDF();
//void Regle1();
void Regle2();
void Regle3();
void Regle4();
void Regle5();
void analyse_semantique();
