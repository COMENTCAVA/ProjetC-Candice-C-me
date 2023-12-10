#include "fichier.h"

t_d_cell *createCell(int value, int levels) {
    t_d_cell *cell = malloc(sizeof(t_d_cell));

    // Alloue correctement la mémoire pour le tableau de pointeurs
    cell->next = malloc(sizeof(t_d_cell *) * levels);
    cell->level = levels;

    // Initialise les pointeurs à NULL
    for (int i = 0; i < levels; i++) {
        cell->next[i] = NULL;
    }

    cell->value = value;
    return cell;
}

t_d_list *createList(int levels, int max) {
    t_d_list *list = malloc(sizeof(t_d_list));
    list->heads = malloc(sizeof(t_d_cell *) * levels);
    list->niveau_max = max;

    // Initialize heads to NULL
    for (int i = 0; i < levels; i++) {
        list->heads[i] = NULL;
    }

    return list;
}

void insert_Cell_Head(t_d_list *list, int value, int level){
    if (level > list->niveau_max){
        printf("Le niveau demandé est supérieur au niveau maximum de la liste.\n");
        return;
    }
    t_d_cell *newCell = createCell(value, level);

    // Mettre à jour les pointeurs next pour chaque niveau
    for (int i = 0; i < level; i++){
        newCell->next[i] = list->heads[i];
        list->heads[i] = newCell;
    }
}


void displayCell_atLevel(t_d_list *list, int i) {
    if (list->heads[i] == NULL) {
        printf("[list head_%d @-]--> NULL\n", i);
        return;
    }

    t_d_cell *current = list->heads[i];
    t_d_cell *previous = NULL;

    printf("[list head_%d @-]--> ", i);

    while (current != NULL) {
        t_d_cell *next = current->next[i];
        if (previous == NULL || previous->value != current->value) {
            printf("[%d | @->]", current->value);
        } else {
            printf(" --> [%d | @->]", current->value);
        }

        previous = current;
        current = next;

        if (current != NULL) {
            printf("--> ");
        }
    }

    printf(" --> NULL\n");
}

void displayCell(t_d_list *list, int niveau) {
    for (int i = 0; i < niveau; i++) {
        displayCell_atLevel(list, i);
    }
}

void insert_Cell_(t_d_list *list, int val, int level)
{
    t_d_cell *newcell = createCell(val, level);

    if (list->heads[0] == NULL || val <= list->heads[0]->value)
    {
        // Si la liste est vide ou la valeur à insérer est inférieure à la tête,
        // utilisez la fonction d'insertion en tête
        insert_Cell_Head(list, val, level);
        return;
    }

    t_d_cell *temp = list->heads[0];
    t_d_cell *update = NULL;

    // Trouver l'endroit où la nouvelle cellule doit être insérée
    for (int i = list->niveau_max - 1; i >= 0; i--)
    {
        while (temp->next[i] != NULL && temp->next[i]->value < val)
        {
            temp = temp->next[i];
        }

        if (i <= level - 1)
        {
            // Insérer la nouvelle cellule après le nœud "update" dans le niveau actuel
            newcell->next[i] = temp->next[i];
            temp->next[i] = newcell;

            // Mettre à jour le nœud "update" pour le niveau suivant
            if (i == 0)
            {
                update = newcell;
            }
        }
    }

    // Mettre à jour les niveaux inférieurs de la nouvelle cellule
    for (int i = 0; i < level; i++)
    {
        while (update->next[i] != NULL && update->next[i]->value < val)
        {
            update = update->next[i];
        }

        newcell->next[i] = update->next[i];
        update->next[i] = newcell;
    }
}


void insert_Cell(t_d_list *list, int value, int level) {
    if(value == 1 && level!=1){
        return;
    }

    if (list->heads[0] == NULL) {
        insert_Cell_Head(list, value, level);
        return;
    }

    t_d_cell *newcell = createCell(value, level);
    t_d_cell *current, *last;
    for (int i = 0; i < level; i++) {
        current = list->heads[i];
        last = NULL;

        while (current != NULL && value > current->value) {
            last = current;
            current = current->next[i];
        }

        if (last == NULL) {
            newcell->next[i] = list->heads[i];
            list->heads[i] = newcell;
        } else {
            newcell->next[i] = current;
            last->next[i] = newcell;
        }
    }
}

int classicResearch(t_d_list *list, int value){
    t_d_cell *current = list->heads[0];
    while(current->next[0] != NULL){
        if(current->value == value){
            return 1;
        }
        current=current->next[0];
    }
    if(current->value == value){
        return 1;
    }
    return 0;
}

int classicResearchByLevel(t_d_list *list, int value, int level){
    if(list->heads[level] == NULL){
        return 0;
    }
    t_d_cell *current = list->heads[level];
    while(current->next[level] != NULL){
        if(current->value == value){
            return 1;
        }
        current=current->next[level];
    }
    if(current->value == value){
        return 1;
    }
    return 0;
}

int maxLevelResearch(t_d_list *list, int value){
    for(int i = list->niveau_max; i>=0; i--){
        if(classicResearchByLevel(list, value, i) == 1){
            return 1;
        }
    }
    return 0;
}

//fonction permettant de connaître à quel niveau insérer quelle valeur
int * createNiveau(int niveaux, int max_cell){
    int* level = malloc(sizeof(int)*max_cell);
    for(int i = 0; i<niveaux; i++){
        int interval = pow(2, i);
        for(int j = 0; j<max_cell; j++){
            if(j % interval == 0 && j<max_cell){
                level[j] = i;
            }
        }
    }
    return level;
}