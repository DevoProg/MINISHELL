#include "../../includes/minishell.h"

void put_res_pipe(t_data *minis, int res)
{
    t_var *ptr;
    char *new_value;
    int i;

    ptr = lst_name_finding(minis->env, "?");
    new_value = ft_itoa(res);
    if(!new_value)
        exit(1);//quitter prorperement
    free(ptr->value);
    ptr->value = ft_strdup(new_value);
    if(!ptr->value)
        exit(1);//quitter prorpement
}

t_var *lst_name_finding(t_var *lst, char *name)
{
    while(lst->next != NULL && ft_strcmp(lst->name, name) != 0)
        lst = lst->next;
    if (ft_strcmp(lst->name, name) == 0)
        return(lst);
    else
        return(NULL);
}

/*
    Fonction servant a récupérer le dernier element t_var de la liste.
*/
t_var	*lst_last(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
    Fonction servant a ajouter un ptr de variable complèté dans la liste "minis->env". 
*/
void lst_add(t_var **lst, t_var *new)
{
	t_var   *aux_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = lst_last(*lst);
		aux_lst->next = new;
	}
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
