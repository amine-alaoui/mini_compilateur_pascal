#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  enum{
    PROGRAM_TOKEN, ID_TOKEN, CONST_TOKEN, VAR_TOKEN,
    BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN,
    DO_TOKEN, READ_TOKEN, WRITE_TOKEN, PV_TOKEN, PT_TOKEN, PLUS_TOKEN,
    MOINS_TOKEN, MULT_TOKEN, DIV_TOKEN, VIR_TOKEN, AFF_TOKEN, INF_TOKEN,
    INFEG_TOKEN, SUP_TOKEN, SUPEG_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN,
    FIN_TOKEN, NUM_TOKEN, ERREUR_TOKEN, EG_TOKEN, EOF_TOKEN, COMMENT_TOKEN,
    GUIMO_TOKEN,GUIMF_TOKEN,SPCE_TOKEN,SAUT_TOKEN
} CODES_LEX;
typedef struct class
{
   CODES_LEX cls;
   char* nom;
   int val;
   struct class * next;
}class;

class* head;
class* temp;
char* mot;
char Car_Cour;
FILE* fichier;
//FILE* resultat= NULL;
int analyse_lexicale();
char Lire_Car();
CODES_LEX lire_mot();
CODES_LEX lire_nombre();
CODES_LEX lire_Symbole();
CODES_LEX analyse();
void openfile(char * filename);
void resultfile(char * filename,char * chaine);
void ajouter();
void afficherListe();
char * conversion(CODES_LEX cls);
