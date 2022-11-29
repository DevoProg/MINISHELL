#include "../includes/minishell.h"

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

void ft_error(char *message, t_data *minis, int z)
{
    if(z == 1 || z == 2)
        free(minis->line);
    if(z == 2)
        free_tab(minis->tab_cmd, minis->nb_tab);
    perror(message);
    exit(1);
}