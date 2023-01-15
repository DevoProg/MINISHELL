#include "../../includes/minishell.h"

void free_struct_cmd(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)                                        //boucle qui met les commandes dans le tableau de structure
    {
        if(minis->cmd[i].line_cmd)
            free(minis->cmd[i].line_cmd);
        if(minis->cmd[i].tab)
            free_tab(minis->cmd[i].tab, minis->cmd[i].nb_words);
        if(minis->cmd[i].cmd_path)                                  //il faudra free le chemin d'access sans message d'erreur
            free(minis->cmd[i].cmd_path);
        i++;
    }
    free(minis->cmd);
}

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

void    free_list(t_var *env)
{
    while(env->next)
    {
        env = ft_delete_first_node(env);
    }
    ft_delete_first_node(env);
}

void ft_error(char *message, t_data *minis, int z, int is_perror)
{
    if(z >= 0)
        free_list(minis->env);
    if(z > 0)
        free(minis->line);
    if(z == 1)//il est free dans init struct
        free_tab(minis->tab_cmd, minis->nb_cmd);
    if(z >= 2)
        free_struct_cmd(minis);
    if(is_perror == 1)
        perror(message);
    else
        ft_putstr_fd(message, 2);
    exit(1);
}