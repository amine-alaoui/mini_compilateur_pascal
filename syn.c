  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "lex.h"
  #include "syntax.h"
  //#include"semantique.h"

/* passage d'un symbole à l'autre */
  void Sym_Suiv(){
      temp = temp->next;
  }
/* conversion d'enum en chaine de caractere pour affichage */

  void Erreur(ERREURS COD_ERR,int i){
    syntax+=1;
    switch(COD_ERR){
  case 0: printf("%d- ERREUR-->PROGRAM\n",i);break;
  case 1: printf("%d- ERREUR-->CONST_ERREUR\n",i);break;
  case 2: printf("%d- ERREUR-->VAR_ERREUR\n",i);break;
  case 3: printf("%d- ERREUR-->BEGIN_ERREUR\n",i);break;
  case 4: printf("%d- ERREUR-->END_ERREUR\n",i);break;
  case 5: printf("%d- ERREUR-->IF_ERREUR\n",i);break;
  case 6: printf("%d- ERREUR-->THEN_ERREUR\n",i);break;
  case 7: printf("%d- ERREUR-->WHILE_ERREUR\n",i);break;
  case 8: printf("%d- ERREUR-->DO_ERREUR\n",i);break;
  case 9: printf("%d- ERREUR-->READ_ERREUR\n",i);break;
  case 10: printf("%d- ERREUR-->WRITE_ERREUR\n",i);break;
  case 11: printf("%d- ERREUR-->PV_ERREUR\n",i);break;
  case 12: printf("%d- ERREUR-->PT_ERREUR\n",i);break;
  case 13: printf("%d- ERREUR-->PLUS_ERREUR\n",i);break;
  case 14: printf("%d- ERREUR-->MOINS_ERREUR\n",i);break;
  case 15: printf("%d- ERREUR-->MULT_ERREUR\n",i);break;
  case 16: printf("%d- ERREUR-->DIV_ERREUR\n",i);break;
  case 17: printf("%d- ERREUR-->VIR_ERREUR\n",i);break;
  case 18: printf("%d- ERREUR-->AFF_ERREUR\n",i);break;
  case 19: printf("%d- ERREUR-->PO_ERREUR\n",i);break;
  case 20: printf("%d- ERREUR-->PF_ERREUR\n",i);break;
  case 21: printf("%d- ERREUR-->ID_ERREUR\n",i);break;
  case 22: printf("%d- ERREUR-->NUM_ERREUR\n",i);break;
  case 23: printf("%d- ERREUR-->CONST_VAR_BEGIN_ERR\n",i);break;
  case 24: printf("%d- ERREUR-->INST_ERR\n",i);break;
  case 25: printf("%d- ERREUR-->COND_ERR\n",i);break;
  case 26: printf("%d- ERREUR-->EG_ERREUR\n",i);break;

  }
  }
/* test de symobole passer ne paramètre avec les elts de la liste chainée*/

  void Test_Symbole (CODES_LEX cl, ERREURS COD_ERR){

      if (temp->cls == cl)
        {
          printf("%d- %s ok \n",i,conversion(temp->cls));
          Sym_Suiv();
        }
   else{
       Erreur(COD_ERR,i);
        }
  i=i+1;
  }
/* analyse de la liste des tokens */

  void PROGRAM()
  {
      Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
      Test_Symbole(ID_TOKEN, ID_ERR);
      Test_Symbole(PV_TOKEN, PV_ERR);
      nbrIDFS+=1;
      BLOCK();
      Test_Symbole(PT_TOKEN, PT_ERR);
  }
/* analyse du corps du programme */
  void BLOCK()
  {
      CONSTS();
      VARS();
      INSTS();
  }
/* verification des CONST_TOKEN */
  void CONSTS() {

      switch (temp->cls) {
          case CONST_TOKEN :  Sym_Suiv();

                              Test_Symbole(ID_TOKEN, ID_ERR);
                              Test_Symbole(EG_TOKEN, EG_ERR);
                              Test_Symbole(NUM_TOKEN, NUM_ERR);
                              Test_Symbole(PV_TOKEN, PV_ERR);
                              nbrIDFS+=1;
                              while (temp->cls==ID_TOKEN){
                                                            Test_Symbole(ID_TOKEN,ID_ERR);
                                                            Test_Symbole(EG_TOKEN, EG_ERR);
                                                            Test_Symbole(NUM_TOKEN, NUM_ERR);
                                                            Test_Symbole(PV_TOKEN, PV_ERR);
                                                            nbrIDFS+=1;
                                                          }
                              if(temp->cls==CONST_TOKEN)
                              CONSTS();break;
          case VAR_TOKEN: break;
          case BEGIN_TOKEN:  break;
          default: Erreur(CONST_VAR_BEGIN_ERR,i);break;
      }

  }
/* verification des VAR_TOKEN */
  void VARS() {

    switch (temp->cls) {
      case VAR_TOKEN : Test_Symbole(VAR_TOKEN,VAR_ERR);
                       Test_Symbole(ID_TOKEN,ID_ERR);
                       nbrIDFS+=1;
                       while(temp->cls== VIR_TOKEN) {
                                                      Sym_Suiv();
                                                      Test_Symbole(ID_TOKEN,ID_ERR);
                                                      nbrIDFS+=1;
                                                    }
                       Test_Symbole(PV_TOKEN,PV_ERR);
                      if(temp->cls==VAR_TOKEN)
                        VARS();
                      else if(temp->cls==CONST_TOKEN)
                        CONSTS();
                         break;
      case BEGIN_TOKEN : break;
      default          : Erreur(CONST_VAR_BEGIN_ERR,i);break;
    }
  }
/* verification des instruction */
  void INSTS() {

    Test_Symbole(BEGIN_TOKEN,BEGIN_ERR);
    INST();
    Test_Symbole(PV_TOKEN,PV_ERR);
    while (temp->cls!=EOF_TOKEN) {
                                    if(temp->cls!=PV_TOKEN)
                                                           {
                                                             INST();
                                                            if (temp->cls==PT_TOKEN)
                                                                                 { if (temp->next->cls!=EOF_TOKEN)
                                                                                          {Erreur(PT_ERR,i);
                                                                                            Sym_Suiv();continue;}
                                                                                   else break;
                                                                                 }
                                                          }
                                     Test_Symbole(PV_TOKEN,PV_ERR);
                                }
}
/* verification des BEGIN, WHILE, WRITE, READ .....*/
  void INST() {

    switch (temp->cls) {
      case BEGIN_TOKEN : INSTS(); break;
      case ID_TOKEN    : AFFEC(); break;
      case IF_TOKEN    : SI(); break;
      case WHILE_TOKEN : TANTQUE();break;
      case WRITE_TOKEN : ECRIRE(); break;
      case READ_TOKEN  : LIRE(); break;
      case END_TOKEN   : Test_Symbole(END_TOKEN,END_ERR);break;
      default          : Erreur(INST_ERR,i);Sym_Suiv();break ;
  }
  }
/* verification des AFFEC_TOKEN (affectation) */
  void AFFEC() {

    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(AFF_TOKEN,AFF_ERR);
    EXPR();
  }
/* verification des expresions + ou - */
  void EXPR() {

    TERM();
    while(temp->cls== PLUS_TOKEN || temp->cls== MOINS_TOKEN) {
      Sym_Suiv();
      TERM();
    }
  }
/* verification des termes */
  void TERM() {

    FACT();
      /* verification des expresions multiplication ou division */
    while(temp->cls== MULT_TOKEN || temp->cls == DIV_TOKEN) {
      Sym_Suiv();
      FACT();
    }
  }
/* verification des facteurs */
  void FACT() {

      switch(temp->cls) {
      case ID_TOKEN : Test_Symbole(ID_TOKEN,ID_ERR); break ;
      case PO_TOKEN : Sym_Suiv();EXPR(); Test_Symbole(PF_TOKEN,PF_ERR); break ;
       default      : ; break ;
    }
  }
/* verification de IF_TOKEN */
  void SI() {

    Test_Symbole(IF_TOKEN,IF_ERR);
    COND();
    Test_Symbole(THEN_TOKEN,THEN_ERR);
    INST();
  }
/* verification de la condition apres IF */
  void COND() {

    EXPR();
    switch(temp->cls) {
      case EG_TOKEN:Sym_Suiv();EXPR();break;
      case DIFF_TOKEN:Sym_Suiv();EXPR();break;
      case INF_TOKEN:Sym_Suiv();EXPR();break;
      case SUP_TOKEN:Sym_Suiv(); EXPR();break;
      case INFEG_TOKEN:Sym_Suiv();EXPR();break;
      case SUPEG_TOKEN:Sym_Suiv();EXPR();break;
      default: Erreur(COND_ERR,i);break ;
    }
    EXPR();
  }
/* verification de ce qui est après le  WHILE */
  void TANTQUE() {

    Test_Symbole(WHILE_TOKEN,WHILE_ERR);
    COND();
    Test_Symbole(DO_TOKEN,DO_ERR);
    if (temp->cls==BEGIN_TOKEN){
                                 Test_Symbole(BEGIN_TOKEN,BEGIN_ERR);
                                 while (temp->cls!=END_TOKEN && temp->next->cls!=PT_TOKEN) {
                                                                                            INST();
                                                                                            Test_Symbole(PV_TOKEN,PV_ERR);
                                                                                          }
                                 if(temp->next->cls==PT_TOKEN)
                                 Erreur(END_ERR,i);
                                 Test_Symbole(END_TOKEN,END_ERR);
                              }
  else INST();
}
/* verification de ce qui est après le  WRITE */
   void ECRIRE() {

    Test_Symbole(WRITE_TOKEN,WRITE_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    EXPR();

    while(temp->cls== VIR_TOKEN) {
      Sym_Suiv();
      EXPR();
    }
    Test_Symbole(PF_TOKEN,PF_ERR);
  }
/* verification de ce qui est après le  READ */
  void LIRE() {

    Test_Symbole(READ_TOKEN,READ_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    while(temp->cls== VIR_TOKEN) {
      Sym_Suiv();
      Test_Symbole(ID_TOKEN,ID_ERR);
    }
    Test_Symbole(PF_TOKEN,PF_ERR);
  }
  int analyse_syntaxique(){
    /* initialisation*/
    i=0;
    /* initialisation du pointeur temp sur la tete de la liste */
    temp=head;
    syntax=0;
     printf("***************************TEST DES TOKENS****************************\n");
     printf("   ================================================================\n");
    /* analyse du programme proposé */
    PROGRAM();
    /* affichage du resultat d'analyse */
     printf("     ==========================================================\n");
     printf("         ===============FIN ANALYSE SYNTAXIQUE===========\n");

   if (syntax==0)
    {printf("                ********   SYNTAXE CORRECTE   ******\n");
     printf("                ====================================\n");
      return 0;}
   else{
     printf("      ********  !!!!SYNTAXE INCORRECTE!! %d ERREUR(S)  ******\n",syntax);

     printf("               =====================================\n");
      return 1;}

  }
