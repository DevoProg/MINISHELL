#include "../includes/minishell.h"

void free_struct(t_data *minis)//free le tableau de structure
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        free(minis->cmd[i].line_cmd);
        i++;
    }
    free(minis->cmd);
}


void init_struct(t_data *minis)//allocation d'un tableau de strcuture et copier le tableau dans chaque structure
{
    int i;

    minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);//allocation d'un tableau de structure
    if(!minis->cmd)
        ft_error("Malloc", minis, 2);
    i = 0;
    while(i < minis->nb_cmd)//boucle qui met les commandes dans le tableau de structure
    {
        minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
        if(!minis->cmd[i].line_cmd)
            ft_error("Malloc", minis, 3);
        i++;
    }
    free_tab(minis->tab_cmd, minis->nb_cmd + 1);//free le tableau du split_cmd car les lignes ont ete copiee dans cmd[i]->cmd_line
    i = 0;
    while(i < minis->nb_cmd)//boucle des structure de commandes
    {
        minis->cmd[i].line_cmd = get_envp_var(minis->cmd[i].line_cmd);//la $variable d'environnement remplacée par son contenu pour chaque commandes
        i++;
    }
    
    i = 0;
    while(i < minis->nb_cmd)//boucle pour imprimer les commandes de la struct
    {
        printf("->%s\n", minis->cmd[i].line_cmd);
        // if(i < minis->nb_cmd - 1)
        //     printf("--->il faudra pipe le fd\n");
        i++;
    }
}