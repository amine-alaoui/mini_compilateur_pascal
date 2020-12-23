    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "lex.h"
    #include "syntax.h"

     int analyse_lexicale(){
       /* allocation mémoire de temp de type la structure class */
       temp=(class *)malloc(sizeof(class));
       /* lecture du premier caractère */
       Lire_Car();
       /* vérification de mot par mot jusqu'à la fin du fichier */
       while(Car_Cour!=EOF){
           analyse();
           Lire_Car();
       }
       printf("EOF_TOKEN \n");
       temp->cls=EOF_TOKEN;
       temp->nom="EOF";
       /* ajouter le EOF_TOKEN pour marquer la fin de vérification */
       ajouter();
       /* afficher la liste chainée et ecriture des résultats des tokens sur un fichier txt */
       afficherListe();
       /* initialisation du pointeur temp sur la tete de la lise chainée */
      temp=head;
      int i=0;
       printf("=====================================================================\n");
       printf("     ===================FIN ANALYSE LEXICALE===================\n");
       /* chercher l'EREEUR sur a liste en parcourant la liste chainée créée */
      while((strcmp(conversion(temp->cls),"ERREUR_TOKEN")!=0)&&(temp->next!=NULL))
      {
       temp=temp->next;
       i =i+1;
      }
      /* affichage de resulat de vérification */
       if (temp!=NULL && temp->cls!=EOF_TOKEN){
       printf("               !!!!!!!!!lexique incorecte!!!!!!! %s ligne %d\n",conversion(temp->cls),i);
       printf("               =================================\n");
       return 1;
       }
       else{
       printf("            ==========   LEXIQUE CORRECTE   ==========\n");
       printf("                      ======================\n");
       return 0;
       }
     }
/* lecture des caractères à partir du cfichier */

    char Lire_Car(){
        Car_Cour = fgetc(fichier);
        return Car_Cour;
    }
 /* verificaion d'un mot */

    CODES_LEX lire_mot(){

 /* constitution de mot à vérifier */
     while(((Car_Cour>='a'&& Car_Cour<='z' ) || (Car_Cour>='A'&& Car_Cour<='Z') || (Car_Cour>='0' && Car_Cour<='9')) && (Car_Cour!=' ')){
        strncat(mot, &Car_Cour,1);
        Lire_Car();
    }
/* test sur le constitué */

    if(strcmp(mot, "program")==0){
        printf("%s ===> PROGRAM_TOKEN\n",mot);
        temp->cls=PROGRAM_TOKEN;
    }else if (strcmp(mot, "var")==0){
        printf("%s ===> VAR_TOKEN\n",mot);
        temp->cls=VAR_TOKEN;
    }else if (strcmp(mot, "begin")==0){
        printf("%s ===> BEGIN_TOKEN\n",mot);
        temp->cls=BEGIN_TOKEN;
    }else if (strcmp(mot, "end")==0){
        printf("%s ===> END_TOKEN\n",mot);
        temp->cls=END_TOKEN;
    }else if (strcmp(mot, "if")==0){
        printf("%s ===> IF_TOKEN\n",mot);
        temp->cls=IF_TOKEN;
    }else if (strcmp(mot, "then")==0){
        printf("%s ===> THEN_TOKEN\n",mot);
        temp->cls=THEN_TOKEN;
    }else if (strcmp(mot, "while")==0){
        printf("%s ===> WHILE_TOKEN\n",mot);
        temp->cls=WHILE_TOKEN;
    }else if (strcmp(mot, "do")==0){
        printf("%s ===> DO_TOKEN\n",mot);
        temp->cls=DO_TOKEN;
    }else if (strcmp(mot, "read")==0){
        printf("%s ===> READ_TOKEN\n",mot);
        temp->cls=READ_TOKEN;
    }else if (strcmp(mot, "write")==0){
        printf("%s ===> WRITE_TOKEN\n",mot);
        temp->cls=WRITE_TOKEN;
    }else if (strcmp(mot, "const")==0){
        printf("%s ===> CONST_TOKEN\n",mot);
        temp->cls=CONST_TOKEN;
    }else{
        printf("%s ===> ID_TOKEN\n",mot);
        temp->cls=ID_TOKEN;
    }
    temp->val='A';
    temp->nom=mot;
    ajouter();
    return temp->cls;
    }

/* test d'un nombre */

    CODES_LEX lire_nombre(){
       while(Car_Cour>='0' && Car_Cour<='9' && Car_Cour!=' '){
            strncat(mot, &Car_Cour, 1);
            Lire_Car();
        }

        if(strlen(mot)>11){
                            temp->cls=ERREUR_TOKEN;
                          }
        else{
            printf("%s ===> NUM_TOKEN\n",mot);
            temp->val=atoi(mot);
            temp->cls=NUM_TOKEN;
            temp->nom=mot;
        }
        ajouter();
    return temp->cls;
    }
/* test d'un symbole */

    CODES_LEX lire_Symbole(){

        if(Car_Cour==';'){
            printf("%c ===> PV_TOKEN\n",Car_Cour);
            temp->cls=PV_TOKEN;
            temp->nom=";";
            ajouter();
        }else if(Car_Cour=='.'){
            printf("%c ===> PT_TOKEN\n",Car_Cour);
            temp->cls=PT_TOKEN;
            temp->nom=".";
            ajouter();
        }else if(Car_Cour=='+'){
            printf("%c ===> PLUS_TOKEN\n",Car_Cour);
            temp->cls=PLUS_TOKEN;
            temp->nom="+";
            ajouter();
        }else if(Car_Cour=='-'){
            printf("%c ===> MOINS_TOKEN\n",Car_Cour);
            temp->cls=MOINS_TOKEN;
            temp->nom="-";
            ajouter();
        }else if(Car_Cour=='*'){
            printf("%c ===> MULT_TOKEN\n",Car_Cour);
            temp->cls=MULT_TOKEN;
            temp->nom="*";
            ajouter();
        }else if(Car_Cour=='/'){
            printf("%c ===> DIV_TOKEN\n",Car_Cour);
            temp->cls=DIV_TOKEN;
            temp->nom="/";
            ajouter();
        }else if(Car_Cour==','){
            printf("%c ===> VIR_TOKEN\n",Car_Cour);
            temp->cls=VIR_TOKEN;
            temp->nom=",";
            ajouter();
        }else if(Car_Cour=='='){
            printf("%c ===> EG_TOKEN\n",Car_Cour);
            temp->cls=EG_TOKEN;
            temp->nom="=";
            ajouter();
        }else if(Car_Cour==':'){char c= Car_Cour;
                                if(Lire_Car()=='='){
                                printf("%c%c ===> AFF_TOKEN\n",c,Car_Cour);
                                temp->cls=AFF_TOKEN;
                                temp->nom=":=";
                                ajouter();
                                }
        }else if(Car_Cour=='<'){char c= Car_Cour;
                                Lire_Car();
                                if(Car_Cour=='='){
                                    printf("%c%c ===> INFEG_TOKEN\n",c,Car_Cour);
                                    temp->cls=INFEG_TOKEN;
                                    temp->nom="<=";
                                    ajouter();
                                }else if (Car_Cour=='>'){
                                    printf("%c%c ===> DIFF_TOKEN\n",c,Car_Cour);
                                    temp->cls=DIFF_TOKEN;
                                    temp->nom="<>";
                                    ajouter();
                                }else if(Car_Cour!=' '){
                                    printf("%c ===> INF_TOKEN\n",c);
                                    temp->cls=INF_TOKEN;
                                    temp->nom="<";
                                    ajouter();
                                    temp->cls=analyse();
                                }else {
                                    printf("%c ===> INF_TOKEN\n",c);
                                    temp->cls=INF_TOKEN;
                                    temp->nom="<";
                                    ajouter();
                                }
        }else if(Car_Cour=='>'){ char c= Car_Cour;
                                Lire_Car();
                                if(Car_Cour=='='){
                                    printf("%c%c ===> SPEG_TOKEN\n",c,Car_Cour);
                                    temp->cls=SUPEG_TOKEN;
                                    temp->nom=">=";
                                    ajouter();
                                }else if(Car_Cour!=' '){
                                    printf("%c ===> SUP_TOKEN\n",c);
                                    temp->cls=SUP_TOKEN;
                                    temp->nom=">";
                                    ajouter();
                                    temp->cls=analyse();
                                }
                                else {
                                    printf("%c ===> SUP_TOKEN\n",Car_Cour);
                                    temp->cls=SUP_TOKEN;
                                    temp->nom=">";
                                    ajouter();
                                }
        }else if(Car_Cour=='('){
            printf("%c ===> PO_TOKEN\n",Car_Cour);
            temp->cls=PO_TOKEN;
            temp->nom="(";
            ajouter();
        }else if(Car_Cour==')'){
            printf("%c ===> PF_TOKEN\n",Car_Cour);
            temp->cls=PF_TOKEN;
            temp->nom=")";
            ajouter();
        }else if(Car_Cour==' '){
            printf("=============>SPCE_TOKEN\n");
            temp->cls=SPCE_TOKEN;
            temp->nom="espace";
       }else if(Car_Cour=='\n'){
            printf("=============>SAUT_TOKEN\n");
            temp->cls=SAUT_TOKEN;
            temp->nom="retour ligne";
        }
        else if(Car_Cour==EOF){
            printf("%c ===> FIN_TOKEN\n",Car_Cour);
            temp->cls=FIN_TOKEN;
            temp->nom="EOF";
            ajouter();
        }
    /* verification commentaire */
        else if(Car_Cour=='{'){
                                Lire_Car();
                                if(Car_Cour=='*'){ Lire_Car();
                                                    while(Car_Cour!='*')
                                                                    {Lire_Car();
                                                                    }
                                                    Lire_Car();
                                                    if (Car_Cour=='}')
                                                             {
                                                             printf("{*-----*} ->COMMENT_TOKEN\n");
                                                             temp->cls=COMMENT_TOKEN;
                                                             temp->nom="commentaire";
                                                             Lire_Car();
                                                             }
                                                     else
                                                           {printf("ERREUR_TOKEN\n");
                                                             temp->cls=ERREUR_TOKEN;
                                                             temp->nom="ERREUR";
                                                           }
                                                }
                                else {printf("%c ->GUIMO_TOKEN\n",Car_Cour );
                                temp->cls=GUIMO_TOKEN;
                                temp->nom="{";
                                 ajouter();
                                }

        }else if (Car_Cour=='}'){
            printf("%c ->GUIMF_TOKEN\n",Car_Cour);
            temp->cls=GUIMF_TOKEN;
            temp->nom="}";
            ajouter();
        }

        return temp->cls;
    }

    CODES_LEX analyse(){
      mot=(char*)malloc(sizeof (char));
      CODES_LEX b;
    if((Car_Cour>='A' && Car_Cour<='Z') || (Car_Cour>='a' && Car_Cour<='z'))
    {   b= lire_mot();}

    if (Car_Cour>='0' && Car_Cour<='9')
    {   b= lire_nombre();}

    if ((Car_Cour=='=')||(Car_Cour==' ') ||(Car_Cour=='\n') || (Car_Cour!=EOF) || (Car_Cour=='{') || (Car_Cour=='}') || (Car_Cour=='(') || (Car_Cour==')') || (Car_Cour=='<') || (Car_Cour=='>') || (Car_Cour==':') || (Car_Cour==',') || (Car_Cour=='/') || (Car_Cour=='*') || (Car_Cour=='-') || (Car_Cour=='+') || (Car_Cour==';') || (Car_Cour=='.'))
    {   b=   lire_Symbole();}
    else b= ERREUR_TOKEN;
        return b;
    }

/* ouverture du fichier */
    void openfile(char * filename){
     fichier=fopen(filename,"r");
     if(fichier==NULL){
                        fprintf(stderr,"Impossible d'ouvrir le fichier en lecture\n");
                        exit(1);
                      }
    }
/* ecriture de resultat de test sur un fichier */

  /*  void resultfile(char * filename,char * chaine){
     resultat = fopen(filename, "a");
     if (resultat!=NULL)
     {
        fprintf(resultat,"%s ",chaine);
        fclose(resultat);
    }
    else{
        fprintf(stderr,"Impossible d'ouvrir le fichier en ecriture\n");
        exit(2);
    }
  }*/

/* ajout des resultats de test dans une liste chainée */

    void ajouter(){

        class* last=head;
        class * nouveau_symb= (class *) malloc (sizeof(class));
        nouveau_symb->cls=temp->cls;
        nouveau_symb->nom=temp->nom;
        nouveau_symb->val=temp->val;
        nouveau_symb->next=NULL;
        if(head == NULL)
         head= nouveau_symb;
        else{
            while(last->next != NULL){
                                      last = last->next;
                                    }
            last->next = nouveau_symb;
          }
        return;
        }

/* affichage de la liste chainée et écriture sur le fichier résultat */

    void afficherListe(){
         printf("======================================================================\n");
         printf("===========================LISTE DES TOKENS===========================\n");
         printf("======================================================================\n");
         /* Tant que l'on n'est pas au bout de la liste */
        class * p;
        p=(class*)malloc(sizeof(class));
        p= head;
        int i = 0;
        while(p != NULL)
        {
        /* On affiche */
            printf("TOKEN %d : - %s\n",i,conversion(p->cls));
         /* On avance d'une case */
            p = p->next;
            i=i+1;
        }
    }
/* conversion des valeurs du enum créé en chaine de caractère */

    char * conversion(CODES_LEX cls){

    switch(cls){

    case 0: return "PROGRAM_TOKEN";break;
    case 1: return "ID_TOKEN";break;
    case 2: return "CONST_TOKEN";break;
    case 3: return "VAR_TOKEN";break;
    case 4: return "BEGIN_TOKEN";break;
    case 5: return "END_TOKEN";break;
    case 6: return "IF_TOKEN";break;
    case 7: return "THEN_TOKEN";break;
    case 8: return "WHILE_TOKEN";break;
    case 9: return "DO_TOKEN";break;
    case 10: return "READ_TOKEN";break;
    case 11: return "WRITE_TOKEN";break;
    case 12: return "PV_TOKEN";break;
    case 13: return "PT_TOKEN";break;
    case 14: return "PLUS_TOKEN";break;
    case 15: return "MOINS_TOKEN";break;
    case 16: return "MULT_TOKEN";break;
    case 17: return "DIV_TOKEN";break;
    case 18: return "VIR_TOKEN";break;
    case 19: return "AFF_TOKEN";break;
    case 20: return "INF_TOKEN";break;
    case 21: return "INFEG_TOKEN";break;
    case 22: return "SUP_TOKEN";break;
    case 23: return "SUPEG_TOKEN";break;
    case 24: return "DIFF_TOKEN";break;
    case 25: return "PO_TOKEN";break;
    case 26: return "PF_TOKEN";break;
    case 27: return "FIN_TOKEN";break;
    case 28: return "NUM_TOKEN";break;
    case 29: return "ERREUR_TOKEN";break;
    case 30: return "EG_TOKEN";break;
    case 31: return "EOF_TOKEN";break;
    case 32: return "COMMENT_TOKEN";break;
    case 33: return "GUIMO_TOKEN";break;
    case 34: return "GUIMF_TOKEN";break;
    case 35: return "SPCE_TOKEN";break;
    case 36: return "SAUT_TOKEN";break;
    default: return"err";
    }
    }
