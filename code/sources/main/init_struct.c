#include "../../includes/minishell.h"

void free_struct(t_data *minis)//free le tableau de structure
{
    free_struct_cmd(minis);
    free(minis->line);
    free_redi(minis);
}


void    free_redi(t_data *minis)
{
    int        i;
    t_redi *current;
    t_redi *next;

    i = 0;
    while (i < minis->nb_cmd) {
        current = minis->cmd[i].redi;
        while (current) {
            next = current->next;
            free(current->file);
            free(current);
            current = next;
        }
        free(minis->cmd[i].redi);
        free(minis->cmd[i].redi);
        i++;
    }
}

/*
    Fonction servant a init la structure "minis".
*/
void init_struct(t_data *minis)//allocation d'un tableau de strcuture et copier le tableau dans chaque structure
{
    int i;

    minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);           //allocation d'un tableau de structure
    if(!minis->cmd)
        ft_error("Malloc", minis, 1, 1);
    i = 0;
    while(i < minis->nb_cmd)                                        //boucle qui met les commandes dans le tableau de structure
    {
        minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
        if(!minis->cmd[i].line_cmd)
            ft_error("Malloc", minis, 2, 1);
        minis->cmd[i].cmd_path = NULL;
        i++;
    }
    free_tab(minis->tab_cmd, minis->nb_cmd + 1);                        //free le tableau du split_cmd car les lignes ont ete copiee dans cmd[i]->cmd_line
}