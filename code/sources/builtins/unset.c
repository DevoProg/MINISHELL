/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:53:53 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:14:45 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	Fonction servant a delete une node au millieu d'une liste
*/
void	ft_delete_middle_node(t_var *env)
{
	t_var	*tmp;

	tmp = env->next;
	env->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	tmp->next = NULL;
	free(tmp);
}

/*
	Fonction servant a delete la derniere node d'une liste
*/
void	ft_delete_last_node(t_var *env)
{
	t_var	*tmp;

	tmp = env->next;
	free(tmp->name);
	free(tmp->value);
	tmp->next = NULL;
	free(tmp);
	env->next = NULL;
}

/*
	Fonction servant a delete la premiere node au millieu d'une liste
*/
t_var	*ft_delete_first_node(t_var *env)
{
	t_var	*tmp;

	tmp = env;
	env = env->next;
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	tmp->next = NULL;
	free(tmp);
	return (env);
}

/*
	fonction qui supprime la variable d'environnement de la liste chainée
*/
t_var	*ft_delete_node(char *str, t_var *env)
{
	t_var	*tmp;
	t_var	*start;

	start = env;
	if (ft_strcmp(str, env->name) == 0)
	{
		env = ft_delete_first_node(env);
		return (env);
	}
	tmp = env->next;
	while (tmp->next != NULL)
	{
		if (ft_strcmp(str, tmp->name) == 0)
		{
			ft_delete_middle_node(env);
			return (start);
		}	
		env = env->next;
		tmp = env->next;
	}
	if (ft_strcmp(str, tmp->name) == 0)
		ft_delete_last_node(env);
	return (start);
}

/*
	Cas commande : UNSET
*/
void	ft_unset(t_data *minis, t_board *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->nb_words - 1)
	{
		minis->env = ft_delete_node(cmd->tab[i], minis->env);
		i++;
	}
}
