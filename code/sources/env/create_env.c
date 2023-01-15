#include "../../includes/minishell.h"

/*
    Fonction servant a recuperer le nom de la variable d'environnement.
    Le nom est stocké dans la structure "t_var ptr".
*/
void ft_get_name(char *str, t_var *ptr)
{
    int i;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    ptr->name = malloc(sizeof(char) * (i + 1));
    if(!ptr->name)
    {
        free(ptr);
        return;
    }
    i = 0;
    while(str[i] && str[i] != '=')
    {
        ptr->name[i] = str[i];
        i++;
    }
    ptr->name[i] = '\0';
}


/*
    Si il n'y a pas de égal dans le get_value de export sa value = ''
*/
void ft_malloc_empty(t_var *ptr)
{
    ptr->value = malloc(sizeof(char) * 3);
    if(!ptr->value)//quitter prorpement
        exit(1);
    ptr->value[0] = 39;// '
    ptr->value[1] = 39;// '
    ptr->value[2] = '\0';
}

/*
    Fonction servant a récupérer la valeur de la variable d'environnement.
    La valeur est stocké dans la structure "t_var ptr".
*/
void ft_get_value(char *str, t_var *ptr)
{
    int i;
    int j;
    int len;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    if(str[i] != '=')
    {
        ft_malloc_empty(ptr);
        return;
    }
    i++;
    len = ft_strlen(str + i);
    ptr->value = malloc(sizeof(char) * (len + 1));
    if(!ptr->value)
    {   
        free(ptr->name);
        free(ptr);
        return;
    }
    j = 0;
    while(str[i])
    {
        ptr->value[j] = str[i];
        j++;
        i++;
    }
    ptr->value[j] = '\0';
}


/*
    Fonction servant a recuperer les variables d'environnement et de creer une liste chainée
*/
void ft_create_env(t_data *minis, char **envp)
{
    t_var *ptr;
    int i;

    minis->env = NULL;
    i = 0;
    while(envp[i])
    {
        ptr = malloc(sizeof(t_var));
        if(!ptr)
            ft_error("Malloc", minis, 0, 1);
        ft_get_name(envp[i], ptr);
        if(!ptr->name)
            ft_error("Malloc", minis, 0, 1);//ptr est free dans ft_get_name
        ft_get_value(envp[i], ptr);
        if(!ptr->value)
            ft_error("Malloc", minis, 0, 1);// ptr et ptr name free dans ft_get_value
        if(ptr->name && ptr->name[0] == '_' && ptr->name[1] == '\0')
            ptr->is_export = 0;
        else
            ptr->is_export = 1;
        i++;
        ptr->is_print = 1;
        ptr->next = NULL;
        lst_add(&minis->env, ptr);
        ptr = NULL;
    }
    //creer une fontion pour tout ce bloc en dessous ->allocation d'une liste pour la variable $?
    ptr = malloc(sizeof(t_var));
    if(!ptr)
        exit(1);//quitter proprement
    ptr->name = malloc(sizeof(char) * 2);
    if(!ptr->name)
        exit(1);
    ptr->name[0] = '?';// je sais pas si on peut faire ainsi
    ptr->name[1] ='\0';
    ptr->value = malloc(sizeof(char) * 2);
    if(!ptr->value)
        exit(1);
    ptr->value[0] = '1';
    ptr->value[1] = '\0';
	ptr->next = NULL;
	ptr->is_export = 0;
	ptr->is_print = 0;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}