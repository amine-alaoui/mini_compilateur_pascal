#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
  PROGRAM_ERR,CONST_ERR,VAR_ERR,BEGIN_ERR,END_ERR,IF_ERR,
  THEN_ERR,WHILE_ERR,DO_ERR,READ_ERR,WRITE_ERR,PV_ERR,
  PT_ERR,PLUS_ERR,MOINS_ERR,MULT_ERR,DIV_ERR,VIR_ERR,AFF_ERR,
  PO_ERR,PF_ERR,ID_ERR,NUM_ERR,CONST_VAR_BEGIN_ERR,INST_ERR,COND_ERR,EG_ERR
}ERREURS;
int analyse_syntaxique();
void Sym_Suiv();
void Test_Symbole(CODES_LEX token,ERREURS erreur);
void PROGRAM();
void BLOCK();
void CONSTS() ;
void VARS();
void INSTS();
void INST();
void AFFEC();
void EXPR();
void TERM();
void FACT();
void SI();
void COND();
void TANTQUE();
void LIRE();
void ECRIRE();
CODES_LEX recov(char * symb);
int i;
int syntax;
int nbrIDFS;
