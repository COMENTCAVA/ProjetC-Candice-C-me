#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct contact{
    char* nom;
    char* prenom;
    struct RDV *rendez_vous;
    struct contact ** next;
}Contact;

typedef struct rdv{
    int jour,mois,annee,heure,minute,heure_duree,minute_duree;
    char *objet_rdv;
    int nb;
    struct rdv *next;
}RDV;

typedef struct agenda{
    int max_levels;
    Contact **head;
}Agenda;

Contact* rechercherContact(Agenda agenda,const char* contact);
void ajouter_rdv(Contact *contact, RDV *rdv);
void supprimer_rdv(Contact * contact,int numero_rdv);
void afficher_rdv_contact(Contact * un_contact);
RDV *createRendezvous(int jour, int mois, int annee, int heure, int minute, int heure_duree, int minute_duree, char *objet_rdv );
Contact * createContact(char* name,char* first_name);
char *scanString(int);
void insertCellAgenda(Agenda *agenda, Contact *c, RDV *rdv);
void display_list(Agenda agenda);
Agenda *createAgenda(int max);
void inserta_Agenda(Contact * new_cell, Agenda *agenda);