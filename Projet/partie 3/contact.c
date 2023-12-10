#include "contact.h"

Contact createContact(char* name,char* first_name){
    Contact new_contact;
    new_contact.prenom=name;
    new_contact.nom=first_name;
    return new_contact;
}

RDV *createRendezvous(Date_rdv date, Heure_rdv heure, Duree_rdv duree, char *objet_rdv){
    RDV *rdv = malloc(sizeof(RDV));
    rdv->date = date;
    rdv->duree=duree;
    rdv->heure=heure;
    rdv->objet_rdv=objet_rdv;
    rdv->next = NULL;
    return rdv;
}

Agenda createAgenda(int max){
    Agenda a;
    a.head = malloc(sizeof(t_cell_agenda *) * 5);
    a.max_levels=max;
    return a;
}

p_cell_agenda createCellAgenda(Contact contact) {
    p_cell_agenda new_agenda_cell = malloc(sizeof(p_cell_agenda));
    new_agenda_cell->contact = contact;
    new_agenda_cell->rendez_vous = NULL;
    new_agenda_cell->cptRdv = 0;

    new_agenda_cell->next = malloc(sizeof(p_cell_agenda) * 5);
    for(int i = 0;i<4 ; i++){
        new_agenda_cell->next[i] = NULL;
    }

    //new_agenda_cell->levels=-1;
    return new_agenda_cell;
}

p_cell_agenda createCellAgendaRDV(Contact contact, RDV *rdv) {
    p_cell_agenda new_agenda_cell = malloc(sizeof(p_cell_agenda));
    new_agenda_cell->contact = contact;
    new_agenda_cell->rendez_vous = rdv;
    new_agenda_cell->cptRdv = 0;
    new_agenda_cell->next = NULL;
    //new_agenda_cell->levels=-1;
    return new_agenda_cell;
}

void insertCellAgenda(Agenda *agenda, Contact c, RDV *rdv){
    if(agenda->head[0] == NULL){
        p_cell_agenda cell = createCellAgenda(c);
        cell->rendez_vous=rdv;
        cell->next=NULL;
        agenda->head[0]=cell;
        return;
    }

    p_cell_agenda temp = agenda->head[0];
    p_cell_agenda prev = temp;

    p_cell_agenda cell = createCellAgenda(c);
    cell->rendez_vous=rdv;
    agenda->head[0]=cell;

    while(temp!=NULL){
        //vérifions maintenant pour tous les autres cas
        //vérifions qu'il n'est pas nul
        for(int i =0; i<4; i++){
            int add = (i == 0 ? 32 : 0);
            if(cell->contact.nom[i]+add < temp->contact.nom[i]+add){
                printf("we insert before: %s", temp->contact.nom);

                cell->next[0]=temp;
                prev->next[0]=cell;

                if(temp==agenda->head[0]){
                    agenda->head[0] = cell;
                }

                //A suivre pour les autres niveaux
                return;
            }else if(cell->contact.nom[i]+add != temp->contact.nom[i]+add){
                continue;
            }
        }


        prev=temp;
        temp=temp->next[0];
    }


}

void afficher_rdv_contact(Agenda agenda,Contact un_contact){

    p_cell_agenda temp=agenda.head[0];
    while (temp!=NULL){
        if(temp->contact.nom == un_contact.nom && temp->contact.prenom == un_contact.prenom){
            RDV *actual = temp->rendez_vous;
            int i = 0;
            while(actual!=NULL){
                printf("RDV %d prévu le %d/%d/%d,",i+1,actual->date.jour,actual->date.mois,actual->date.annee);
                printf(" à %d:%d,",actual->heure.heure,actual->heure.minute);
                printf(" Durée prévue du RDV %d:%d ",actual->duree.heure,actual->duree.minute);
                printf(", Objet du RDV : %s\n",actual->objet_rdv);
                i++;
                actual=actual->next;
            }
            return;
        }
        temp=temp->next[0];
    }
    printf("Pas de RDV prévu pour ce contact");
}

void ajouter_rdv(Agenda *agenda, Contact contact, RDV *rdv){
    if (agenda==NULL){
        printf("Impossible d'ajouter un rendez-vous à ce contact.");
        return;
    }
    //ajouter ici si le contact est innexistant un ajout de celui-ci et du rendez-vous
    p_cell_agenda temp=agenda->head[0];
    while (temp!=NULL){
        if(temp->contact.nom == contact.nom && temp->contact.prenom == contact.prenom){
            RDV *actual = temp->rendez_vous;
            if(actual==NULL){
                temp->rendez_vous=rdv;
                return;
            }
            while(actual!=NULL){
                if(actual->next==NULL){
                    actual->next=rdv;
                    return;
                }
                actual=actual->next;
            }
            return;
        }
        temp=temp->next[0];
    }
    printf("Ce contact n'existe pas.");
}

Contact rechercherContact(Agenda agenda,const char* contact) {
    p_cell_agenda temp=agenda.head[0];
    while (temp!=NULL){

        for(int i = 0; i<4; i++){
            if(temp->contact.nom[i]==contact[i] && i>=2){
                //on a trouvé le contact
                printf("Le contact a bien été trouvé, %s %s\n", temp->contact.prenom, temp->contact.nom);
                return temp->contact;
            }else{
                continue;
            }
        }
        temp=temp->next[0];
    }
    printf("Le contact n'a pas été trouvé.\n");
    Contact c = createContact("not", "found");
    return c;
}

void supprimer_rdv(Agenda *agenda,Contact contact,int numero_rdv){
    p_cell_agenda temp=agenda->head[0];
    while (temp!=NULL){
        if (temp->contact.nom==contact.nom && temp->contact.prenom==contact.prenom){
            RDV *actual = temp->rendez_vous;
            RDV *prv = actual;
            int i = 0;
            if (actual==NULL){
                printf("Pas de RDV prévu pour %s %s",temp->contact.prenom,temp->contact.nom);
            }else{
                while(actual!=NULL){
                    if(i+1==numero_rdv){
                        if(actual == temp->rendez_vous){
                            temp->rendez_vous=actual->next;
                        }
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
            return;
        }
        temp=temp->next[0];
    }
}

char *scanString(){
    char *s = malloc(sizeof(char) * 1000);
    printf("Veuillez entrer un str: ");
    scanf("%s", s);
    return s;
}

void display_list(Agenda agenda){

    for(int i = 0; i<5; i++){
        printf("LVL%d --> ", i);

        p_cell_agenda temp=agenda.head[i];
        while (temp!=NULL){
            printf("%s --> ", temp->contact.nom);

            if (temp->next[i] == NULL) {
                break;
            }

            temp=temp->next[i];
        }
        printf("\n");
    }

}

void inserta_Agenda(p_cell_agenda new_cell, Agenda *agenda) {
    // Check if the max levels is valid
    if (agenda->max_levels < 0) {
        return;
    }

    // Check if the agenda is empty
    if (agenda->head[0] == NULL) {
        // Allocate memory for the new cell's `next` array
        new_cell->next = malloc((agenda->max_levels + 1) * sizeof(t_cell_agenda*));
        // Initialize the `next` array to NULL
        for (int i = 0; i <= agenda->max_levels; i++) {
            new_cell->next[i] = NULL;
        }
        // Insert the new cell into the agenda
        for (int i = 0; i <= agenda->max_levels; i++) {
            if (new_cell->contact.nom[i] < agenda->head[i]->contact.nom[i]) {
                new_cell->next[i] = agenda->head[i];
                agenda->head[i] = new_cell;
            } else {
                p_cell_agenda copy = agenda->head[i];
                while (copy->next[i] != NULL) {
                    copy = copy->next[i];
                }
                copy->next[i] = new_cell;
            }
        }
    } else {
        // Find the appropriate location to insert the new cell
        p_cell_agenda temp = agenda->head[0];
        int i = 0;
        int j = agenda->max_levels;
        while (temp != NULL && temp->contact.nom[i] <= new_cell->contact.nom[i]) {
            i++;
            j--;
            temp = temp->next[j];
        }
        if (temp == NULL) {
            temp = agenda->head[j];
        }

        new_cell->next = malloc((j + 1) * sizeof(t_cell_agenda));
        for (int k = 0; k <= j; k++) {
            new_cell->next[k] = NULL;
        }

        for (int k = 0; k <= j; k++) {
            if (new_cell->contact.nom[i] < agenda->head[k]->contact.nom[i]) {
                new_cell->next[k] = agenda->head[k];
                agenda->head[k] = new_cell;
            } else {
                p_cell_agenda copy = agenda->head[k];
                while (copy->next[k] != NULL) {
                    copy = copy->next[k];
                }
                copy->next[k] = new_cell;
            }
        }
    }
}

