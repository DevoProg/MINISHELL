#include "../../includes/minishell.h"

/*
    Fonction servant a liberer l espace memoire d'un tableau.
*/
void free_tab(char **tab, int i)
{
    int j;

    j = 0;
    while(j < i)
    {
        free(tab[j]);
        j++;
    }
    free(tab);
}

/*
    Fonction servant a gerer les cas d'erreurs.
*/
void ft_error(char *message, t_data *minis, int z)
{
    if(z == 1 || z == 2)
        free(minis->line);
    if(z == 2)
        free_tab(minis->tab_cmd, minis->nb_cmd);
    perror(message);
    exit(1);
}