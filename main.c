#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "syntax.h"
#include "semantique.h"
int main(int argc, const char * argv[]) {
  int a;
  /* ouverture de fichier à tester */
  openfile("test.txt");
  /* analyse lexicale */
  a=analyse_lexicale();

  if (a==0){
            /* analyse_syntaxique */
            a = analyse_syntaxique();
            if(a==0){ /* analyse_semantique */
                       analyse_semantique();
                       // for(int l=0;l<nbrIDFS;l++)
                       // printf("%s==========%d\n",TAB_IDFS[l].NOM,TAB_IDFS[l].TIDF);
                  }
            else printf("       !!!!!!!!!!!!!!!!!VERIFIER VOTRE SYNTAXE!!!!!!!!!!!!!!!!!\n");
          }
  else printf("         !!!!!!!!!!!!!!!!!VERIFIER VOTRE LEXIQUE!!!!!!!!!!!!!!!!!\n");
   return 0;
}
