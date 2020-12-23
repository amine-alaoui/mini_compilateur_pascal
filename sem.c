#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lex.h"
#include"syntax.h"
#include"semantique.h"

/* remplissage du tableau des identificateurs */
void remplir_tab(TSYM SYM){
  TAB_IDFS[i].NOM=temp->nom;
  TAB_IDFS[i].TIDF=SYM;
  i++;
  Sym_Suiv();
}
/* parcours de la liste chainée pour remplir le tableau des identificateurs */
void TABLEAU_IDF(){

                    temp=head;
                    i=0;
                    while(temp!=NULL){
                    switch (temp->cls) {
                                        case PROGRAM_TOKEN:Sym_Suiv();if(temp->cls==ID_TOKEN){
                                                                                        remplir_tab(TPROG);
                                                                                      };break;

                                        case CONST_TOKEN:Sym_Suiv();if(temp->cls==ID_TOKEN){remplir_tab(TCONST);}
                                                        Sym_Suiv();Sym_Suiv();Sym_Suiv();
                                                        while(temp->cls==ID_TOKEN){remplir_tab(TCONST);
                                                                                   Sym_Suiv();Sym_Suiv();Sym_Suiv();
                                                                                  };break;
                                        case VAR_TOKEN:Sym_Suiv();if(temp->cls==ID_TOKEN){remplir_tab(TVAR);}
                                                      while (temp->cls==VIR_TOKEN){ Sym_Suiv();
                                                                                    remplir_tab(TVAR);
                                                                                  };break;
                                      default: Sym_Suiv();break;
                                      }
                                    }
}
void analyse_semantique(){
  printf("*******************  ANALYSE SEMANTIQUE  **************************\n");
  printf("   ===========================================================\n");
  TABLEAU_IDF();
  sem=0;
  for(i=0;i<nbrIDFS-1;i++)
     {
      switch(TAB_IDFS[i].TIDF){
                                case TPROG:Regle5();Regle3();break;
                                case TCONST:Regle2();Regle4();break;
                                case TVAR:Regle2();break;
                                default:;break;
                              }
    }
      printf("  ====== VOUS AVEZ %d ERREUR SEMANTIQUE SUR VOTRE PROGRAMME =====\n",sem);
      printf("    ==========================================================\n");
      printf("         ===============FIN ANALYSE SEMANTIQUE===========\n");
      printf("         ================================================\n");
      printf("            ========================================\n");
      printf("                =================================\n");
      printf("                    ========================\n");
      printf("                       ================\n");
      printf("                          ==========\n");
      printf("                            ======\n");
      printf("                              ==\n");

    if(sem==0){
      printf("               BRAVO: le programme est correcte !!!!  \n");
    }
    else
      printf("             PAS BRAVO: le programme est incorrecte !!!  \n");
      printf("     ==========================================================\n");
 }
void Regle5(){
  temp=head;
  int count=0;
  while(temp!=NULL){
  if (strcmp(TAB_IDFS[i].NOM,temp->nom)==0)
    count++;
   Sym_Suiv();
 }
  if(count>1){printf("ERREUR: << %s >> EST LE NOM DU PROGRAMME ==> NON AUTORISÉ \n",TAB_IDFS[i].NOM);
  sem++;}
}
void Regle2(){
  int j=i+1;
    while(j<nbrIDFS && strcmp(TAB_IDFS[i].NOM,TAB_IDFS[j].NOM)!=0){
    j++;}

  if(j<nbrIDFS){printf("ERREUR: DOUBLE DECLARATION DE << %s >> \n",TAB_IDFS[i].NOM);
  sem++;}
}
void Regle3(){
  temp=head;
  while (temp!=NULL && strcmp(temp->nom,"begin")!=0){Sym_Suiv();}
  while(temp->next!=NULL ){Sym_Suiv();
                           if(temp->cls==ID_TOKEN){int r=0;
                                                    for(int k=0;k<nbrIDFS;k++){
                                                                          if (strcmp(TAB_IDFS[k].NOM,temp->nom)==0)
                                                                          r=1;
                                                                          }
                                                    if (r==0){
                                                    printf("ERREUR: IDENTIFICATEUR << %s >> NON DECLARÉ\n",temp->nom );
                                                    sem++;}
                                                  }
                        }


}
void Regle4(){
  temp=head;
  while(temp->next!=NULL){
    if(strcmp(temp->nom,TAB_IDFS[i].NOM)==0){
      Sym_Suiv();
      if(temp->cls==AFF_TOKEN){
        printf("ERREUR: << %s >> CONSTANTE NE CHANGE PAS DE VALEUR\n",temp->nom );
        sem++;}
    }
    else if(temp->cls==READ_TOKEN) {
      Sym_Suiv();Sym_Suiv();
      if (strcmp(temp->nom,TAB_IDFS[i].NOM)==0){
        printf("ERREUR: << %s >> CONSTANTE NE CHANGE PAS DE VALEUR\n",temp->nom );
        sem++;}
    }
    else Sym_Suiv();
  }
}
// void Regle1(){
//   temp=head;
//   int l=0;
//   //while (temp!=NULL && strcmp(temp->nom,"begin")!=0){Sym_Suiv();}
//   while(temp->next!=NULL ){
//     if (/*temp->cls==CONST_TOKEN ||*/ temp->cls==VAR_TOKEN)
//     l++;
//     if (l>1) break;
//     Sym_Suiv();
//  }
//  if (l!=0)
//  {printf("ERREUR: << %s %s >> DECLARATION NON AUTORISEE \n",temp->nom,temp->next->nom );
//  sem++;}
// }
