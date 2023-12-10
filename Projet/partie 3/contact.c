#include "contact.h"

Contact *createContact(char* name,char* first_name){
    Contact * new_contact = malloc(sizeof(Contact));

    new_contact->prenom = (char *)malloc(strlen(name) + 1);
    strcpy(new_contact->prenom, name);

    new_contact->nom = (char *)malloc(strlen(first_name) + 1);
    strcpy(new_contact->nom, name);

    new_contact->rendez_vous=NULL;
    new_contact->next=(Contact **) malloc(sizeof(Contact*) * 4);

    for (int i = 0; i < 4; i++) {
        new_contact->next[i] = NULL;
    }

    return new_contact;
}

RDV *createRendezvous(int jour, int mois, int annee, int heure, int minute, int heure_duree, int minute_duree, char *objet_rdv){
    RDV *rdv = (RDV *) malloc(sizeof(RDV));
    if(rdv==NULL){
        exit(EXIT_FAILURE);
    }
    rdv->heure_duree=heure_duree;
    rdv->minute_duree=minute_duree;

    rdv->heure=heure;
    rdv->minute=minute;

    rdv->mois=mois;
    rdv->jour=jour;
    rdv->annee=annee;

    rdv->objet_rdv = (char *)malloc(strlen(objet_rdv) + 1);
    if(rdv->objet_rdv==NULL){
        exit(EXIT_FAILURE);
    }
    strcpy(rdv->objet_rdv,objet_rdv);

    rdv->next = NULL;
    return rdv;
}

Agenda* createAgenda(int max){
    Agenda *a = (Agenda*) malloc(sizeof(Agenda));

    a->head =(Contact**) malloc(sizeof(Contact *) * 4);
    for (int i = 0; i < 4; i++) {
        a->head[i] = NULL;
    }

    a->max_levels=max;
    return a;
}

void afficher_rdv_contact(Contact * c){

    RDV *actual = (RDV *) c->rendez_vous;
    int i = 0;
    int has=0;
    while(actual!=NULL){
        printf("RDV %d prévu le %d/%d/%d,",i+1,actual->jour,actual->mois,actual->annee);
        printf(" à %d:%d,",actual->heure,actual->minute);
        printf(" Durée prévue du RDV %d:%d ",actual->heure,actual->minute);
        printf(", Objet du RDV : %s\n",actual->objet_rdv);
        i++;
        actual=actual->next;
        has+=1;
    }

    if(has==0){
        printf("Pas de RDV prévu pour ce contact");
    }
}

void ajouter_rdv(Contact * contact, RDV * rdv){
    //ajouter ici si le contact est innexistant un ajout de celui-ci et du rendez-vous
    RDV *actual = (RDV *) contact->rendez_vous;
    if(actual == NULL){
        printf("Ce contact n'existe pas.");
        return;
    }
    while(actual!=NULL){
        if(actual->next==NULL){
            actual->next=rdv;
            return;
        }
        actual=actual->next;
    }
}

Contact * rechercherContact(Agenda agenda,const char* contact) {
    Contact * temp=agenda.head[0];
    while (temp!=NULL){
        for(int i = 0; i<4; i++){
            if(temp->nom[i]==contact[i] && i>=2){
                //on a trouvé le contact
                printf("Le contact a bien été trouvé, %s %s\n", temp->prenom, temp->nom);
                return temp;
            }else{
                continue;
            }
        }
        temp=temp->next[0];
    }
    printf("Le contact n'a pas été trouvé.\n");
    return NULL;
}

void supprimer_rdv(Contact * contact,int numero_rdv){
    RDV *actual = (RDV *) contact->rendez_vous;
    RDV *prv = actual;
    int i = 0;

    while(actual!=NULL){
        if(i+1==numero_rdv){
            prv->next=actual->next;
            actual->next=NULL;
            free(actual);
            return;
        }
        prv=actual;
        actual=actual->next;
        i++;
    }

}

char *scanString(int i){
    char *s = malloc(sizeof(char) * 1000);
    if(i==1){
        printf("Veuillez entrer un Objet: ");
    }else if(i==2){
        printf("Veuillez entrer un nom: ");
    }else if(i==3){
        printf("Veuillez entrer un prenom: ");
    }
    scanf("%s", s);
    return s;
}

void display_list(Agenda agenda){

    for(int i = 0; i<5; i++){
        printf("LVL%d --> ", i);

        Contact * temp=agenda.head[i];
        while (temp!=NULL){
            printf("%s --> ", temp->nom);

            if (temp->next[i] == NULL) {
                break;
            }

            temp=temp->next[i];
        }
        printf("\n");
    }

}

void inserta_Agenda(Contact *new_cell, Agenda *agenda) {
    if (agenda->max_levels < 0) {
        return;
    }

    // Check if the agenda is empty
    if (agenda->head[0] == NULL) {
        new_cell->next = malloc((agenda->max_levels + 1) * sizeof(Agenda*));
        for (int i = 0; i <= agenda->max_levels; i++) {
            new_cell->next[i] = NULL;
        }
        // Insert the new cell into the agenda
        for (int i = 0; i <= agenda->max_levels; i++) {
            if (new_cell->nom[i] < agenda->head[i]->nom[i]) {
                new_cell->next[i] = agenda->head[i];
                agenda->head[i] = new_cell;
            } else {
                Contact * copy = agenda->head[i];
                while (copy->next[i] != NULL) {
                    copy = copy->next[i];
                }
                copy->next[i] = new_cell;
            }
        }
    } else {

        Contact *temp = agenda->head[0];
        int i = 0;
        int j = agenda->max_levels;
        while (temp != NULL && temp->nom[i] <= new_cell->nom[i]) {
            i++;
            j--;
            temp = temp->next[j];
        }
        if (temp == NULL) {
            temp = agenda->head[j];
        }

        new_cell->next = malloc((j + 1) * sizeof(Contact));
        for (int k = 0; k <= j; k++) {
            new_cell->next[k] = NULL;
        }

        for (int k = 0; k <= j; k++) {
            if (new_cell->nom[i] < agenda->head[k]->nom[i]) {
                new_cell->next[k] = agenda->head[k];
                agenda->head[k] = new_cell;
            } else {
                Contact * copy = agenda->head[k];
                while (copy->next[k] != NULL) {
                    copy = copy->next[k];
                }
                copy->next[k] = new_cell;
            }
        }
    }
}

