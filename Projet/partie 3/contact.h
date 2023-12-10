#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct contact{
    char* nom;
    char* prenom;
}Contact;

typedef struct date_rdv{
    int jour;
    int mois;
    int annee;
}Date_rdv;

typedef struct heure_rdv{
    int heure;
    int minute;
}Heure_rdv;

typedef struct duree_rdv{
    int heure;
    int minute;
}Duree_rdv;

typedef struct rdv{
    Date_rdv date;
    Heure_rdv heure;
    Duree_rdv duree;
    char *objet_rdv;
    struct rdv *next;
}RDV;


typedef struct s_cell_agenda{
    Contact contact;
    RDV *rendez_vous;
    //int levels;
    int cptRdv;
    struct s_cell_agenda ** next;
}t_cell_agenda,*p_cell_agenda;

typedef struct agenda{
    int max_levels;
    t_cell_agenda **head;
}Agenda;

Contact rechercherContact(Agenda agenda,const char* contact);
void ajouter_rdv(Agenda *agenda, Contact contact, RDV *rdv);
void supprimer_rdv(Agenda *agenda,Contact contact,int numero_rdv);
void afficher_rdv_contact(Agenda,Contact);
RDV *createRendezvous(Date_rdv date, Heure_rdv heure, Duree_rdv duree, char *objet_rdv);
Contact createContact(char* name,char* first_name);
char *scanString();
p_cell_agenda createCellAgenda(Contact );
void insertCellAgenda(Agenda *agenda, Contact c, RDV *rdv);
void display_list(Agenda agenda);
Agenda createAgenda(int max);
void inserta_Agenda(p_cell_agenda new_cell, Agenda *agenda);