#include "../includes/minishell.h"

void ft_export(t_data *minis, t_board *cmd)
{
    t_var *ptr;
    char *name;
    char *value;
    int i;

    if(cmd->nb_words == 2)
    {
        print_list(minis->env, 1);
        return ;
    }
    i = 1;
    while(i < cmd->nb_words - 1)
    {
        if(ft_strchr(cmd->tab[i], '='))
        {
            ptr = malloc(sizeof(t_var));
            if(!ptr)
                exit(1);
            ptr->next = NULL;
            ft_get_value(cmd->tab[i], ptr);
            ft_get_name(cmd->tab[i], ptr);
            ptr->is_export = 1;
            lst_add(&minis->env, ptr);
            ptr = NULL;
        }
        i++;
    }
}