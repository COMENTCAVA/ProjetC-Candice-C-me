#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct s_d_cell
{
    int value;
    int level;
    struct s_d_cell **next;
} t_d_cell;

typedef struct s_d_list
{
    int niveau_max;
    t_d_cell **heads;
} t_d_list;

t_d_cell *createCell(int value, int levels);
t_d_list *createList(int levels, int max);
void insert_Cell_Head(t_d_list *list, int value, int level);
void displayCell_atLevel(t_d_list *list, int i);
void displayCell(t_d_list *list, int niveau);
int maxLevelResearch(t_d_list *list, int value);
int * createNiveau(int niveaux, int max_cell);
int classicResearchByLevel(t_d_list *list, int value, int level);
int classicResearch(t_d_list *list, int value);
void insert_Cell(t_d_list *list, int value, int level);