#include "../../includes/minishell.h"

/*
    Fonction qui retourne une chaine de charactere allouée avec le nom de la variable d'evironnement
*/
char *get_name(char *str, t_data *minis)
{
    int i;
    char *str_ret = NULL;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    str_ret = malloc(sizeof(char) * (i + 1));
    if(!str_ret)
        ft_error("Malloc", minis, 2, 1);
    i = 0;
    while(str[i] && str[i] != '=')
    {
        str_ret[i] = str[i];
        i++;
    }
    str_ret[i] = '\0';
    return(str_ret);
}

/*
    Fonction pour assigner une nouvelle valeur a une node qui possede deja une valeur
*/
void ft_assign_new_value(t_data *minis, char *str, char *name)
{
    t_var *ptr;

    ptr = lst_name_finding(minis->env, name);
    free(ptr->value);
    ft_get_value(str, ptr);
}

/*
    Creation d'une  nouvelle node et ajout dans la liste
*/
void ft_create_variable(t_data *minis, char *str)
{
    t_var *ptr;
    
    ptr = malloc(sizeof(t_var));
    if(!ptr)
        ft_error("Malloc", minis, 2, 1);
    ptr->next = NULL;
    ft_get_value(str, ptr);
    if(!ptr->value)
        ft_error("Malloc", minis, 2, 1);
    ft_get_name(str, ptr);
    if(!ptr->name)
        ft_error("Malloc", minis, 2, 1);
    ptr->is_export = 1;
    lst_add(&minis->env, ptr);
    ptr = NULL;
}

/*
    Cas commande : EXPORT.
*/
void ft_export(t_data *minis, t_board *cmd)
{
    t_var *ptr;
    char *name;
    char *value;
    int i;

    if(cmd->nb_words == 2)//si export ne possede pas d'argument il doit printlist
    {
        print_list(minis->env, 1);
        return ;
    }
    i = 1;
    while(i < cmd->nb_words - 1)
    {
        name = get_name(cmd->tab[i], minis);//alloue name
        if(ft_strchr(cmd->tab[i], '=') && !list_chr(minis->env, name))//si le name existe pas dans la liste chainee de variable d'env
            ft_create_variable(minis, cmd->tab[i]);//alors on cree une nouvelle node ett on la met dans la liste
        else if(ft_strchr(cmd->tab[i], '=') && list_chr(minis->env, name))//si elle existe deja dans la liste
            ft_assign_new_value(minis, cmd->tab[i], name);//alors on lui donne une nouvelle valuer
        free(name);//désalloue name
        i++;
    }
}