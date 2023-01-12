#include "../../includes/minishell.h"

/*
    fonction qui regarde si il ne faut pas fork pour la commande
*/
int ft_is_not_fork(t_board *cmd)
{
    int res;

    res = 0;
    if(ft_strcmp(cmd->tab[0], "pwd") == 0 && cmd->nb_words == 2)//==2 ->aucune options ni arg
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "exit") == 0 && cmd->nb_words == 2)//==2 ->aucune options ni arg
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "cd") == 0)
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "export") == 0 && cmd->nb_words != 2)
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "unset") == 0)
        res = 1;
    return(res);
}

 /*
    fonction qui regarde si la commande est un builtin
*/
int ft_is_builtins(t_board *cmd)
{
    int res;

    res = 0;
    if(ft_strcmp(cmd->tab[0], "pwd") == 0)//==2 ->aucune options ni arg
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "env") == 0)
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "echo") == 0)
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "exit") == 0)//==2 ->aucune options ni arg
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "cd") == 0)
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "export") == 0)
        res = 1;
    else if(ft_strcmp(cmd->tab[0], "unset") == 0)
        res = 1;
    return(res);
}

/*
    fonction qui regarde print les variable d'env et var exportées //si i = 1 print var_export //si i == 0 print env
*/
void print_list(t_var *exp, int i)
{
    if(!exp)
        return ;
    while(exp->next != NULL)
    {
        if((i == 1 && exp->is_export == 0) || exp->is_print == 0)
        {
            exp= exp->next;
            continue;
        }
        else
        {
            ft_putstr_fd(exp->name, 1);
            ft_putchar_fd('=', 1);
            ft_putstr_fd(exp->value, 1);
            ft_putchar_fd('\n', 1);
            exp = exp->next;
        }
    }
    if((i == 1 && exp->is_export == 0) || exp->is_print == 0)
        return;
    ft_putstr_fd(exp->name, 1);
    ft_putchar_fd('=', 1);
    ft_putstr_fd(exp->value, 1);
    ft_putchar_fd('\n', 1);
}

/*
    foncttion qui retourne la valeur grace au name de la liste
*/
char *list_chr(t_var *exp, char *str_name)
{
    while(exp->next != NULL)
    {
        if(ft_strcmp(exp->name, str_name) == 0)
            return(exp->value);
        exp = exp->next;
    }
    if(ft_strcmp(exp->name, str_name) == 0)
        return(exp->value);
    return(NULL);
}

/*
    compare deux chaine de charactere
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}