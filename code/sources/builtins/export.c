#include "../includes/minishell.h"

char *get_name(char *str)
{
    int i;
    char *str_ret;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    str_ret = malloc(sizeof(char) * (i + 1));
    if(!str_ret)
        exit(1);//il faudra quitter proprement
    i = 0;
    while(str[i] && str[i] != '=')
    {
        str_ret[i] = str[i];
        i++;
    }
    str_ret[i] = '\0';
    return(str_ret);
}

void ft_assign_new_value(t_data *minis, char *str, char *name)
{
    t_var *ptr;

    ptr = lst_name_finding(minis->env, name);
    free(ptr->value);
    ft_get_value(str, ptr);
}

void ft_create_variable(t_data *minis, char *str)
{
    t_var *ptr;
    
    ptr = malloc(sizeof(t_var));
    if(!ptr)
        exit(1);
    ptr->next = NULL;
    ft_get_value(str, ptr);
    ft_get_name(str, ptr);
    ptr->is_export = 1;
    lst_add(&minis->env, ptr);
    ptr = NULL;
}

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
        name = get_name(cmd->tab[i]);
        if(ft_strchr(cmd->tab[i], '=') && !list_chr(minis->env, name))
            ft_create_variable(minis, cmd->tab[i]);
        else if(ft_strchr(cmd->tab[i], '=') && list_chr(minis->env, name))
            ft_assign_new_value(minis, cmd->tab[i], name);
        free(name);
        i++;
    }
}