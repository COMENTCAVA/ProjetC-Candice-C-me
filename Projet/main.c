#include <stdio.h>
#include <stdlib.h>
#include "partie 2/timer.h"
#define NBMAX 5
#include <math.h>
#include <stdbool.h>
#include "partie 3/contact.h"
#include "partie 1/fichier.h"

int main() {
    printf("\n");

    /*t_d_list* list1 = createList(8, 10);
    insert_Cell(list1, 3, 2);
    insert_Cell(list1, 5, 3);
    insert_Cell(list1, 9, 4);
    insert_Cell(list1, 2, 5);
    displayCell(list1, 8);

    printf("\n");
    printf("\n");

    int levels = 10000;
    t_d_list* list = createList(levels, 10000);
    int* l = createNiveau(levels, 10000);

    for(int i = 0; i<levels; i++){
        if(i == 0){
            insert_Cell(list, i+1, l[i] + 1);
        }else{
            insert_Cell(list, i, l[i] + 1);
        }
    }
    //displayCell(list, 10);
    printf("nombre de niveaux %d\n", levels);
    int tab[3] = {1000, 10000, 100000};
    for(int a = 0; a<3; a++){
        printf("%d recherches : \n", tab[a]);
        int res = tab[a];
        startTimer();
        for(int i = 0; i<res; i++){
            int n = rand() % 10000 + 1;
            classicResearch(list, n);
        }
        stopTimer();
        displayTime();

        startTimer();
        for(int i = 0; i<res; i++){
            int n = rand() % 10000 + 1;
            maxLevelResearch(list, n);
        }
        stopTimer();
        displayTime();
    }*/


    /*startTimer();
    maxLevelResearch(list, i);
    stopTimer();
    displayTime();*/



    char* obj = scanString(1);
    RDV *rdv = createRendezvous(3, 4, 4, 32, 3, 2, 4, obj);

    char* nom = scanString(2);
    char* prenom = scanString(3);
    Contact * contact = createContact(nom, prenom);
    contact->rendez_vous= (struct RDV *) rdv;
    afficher_rdv_contact(contact);

    obj = scanString(1);
    RDV *rdv1 = createRendezvous(3, 4, 4, 32, 3, 2, 4, obj);
    nom = scanString(2);
    prenom = scanString(3);

    Contact *c2 = createContact(nom, prenom);
    c2->rendez_vous= (struct RDV *) rdv1;

    Agenda *agenda = createAgenda(4);
    agenda->head[0] = contact;
    agenda->head[0]->next[0] = c2;
    afficher_rdv_contact(c2);
    printf("%s", agenda->head[0]->nom);

    printf("\n");
    prenom = scanString(3);
    rechercherContact(*agenda, prenom);
    display_list(*agenda);

    return 0;
}