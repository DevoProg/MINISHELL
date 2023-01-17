/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:49:47 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 00:51:43 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_res_pipe(t_data *minis, int res)
{
	t_var	*ptr;
	char	*new_value;
	int		i;

	ptr = lst_name_finding(minis->env, "?");
	new_value = ft_itoa(res);
	if (!new_value)
		exit(1);
	free(ptr->value);
	ptr->value = ft_strdup(new_value);
	if (!ptr->value)
		exit(1);
}

t_var	*lst_name_finding(t_var *lst, char *name)
{
	while (lst->next != NULL && ft_strcmp(lst->name, name) != 0)
		lst = lst->next;
	if (ft_strcmp(lst->name, name) == 0)
		return (lst);
	else
		return (NULL);
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
	Fonction servant a ajouter un ptr 
	de variable complèté dans la liste "minis->env". 
*/
void	lst_add(t_var **lst, t_var *new)
{
	t_var	*aux_lst;

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
void	ft_malloc_empty(t_var *ptr)
{
	ptr->value = malloc(sizeof(char) * 3);
	if (!ptr->value)
		exit(1);
	ptr->value[0] = 39;
	ptr->value[1] = 39;
	ptr->value[2] = '\0';
}
