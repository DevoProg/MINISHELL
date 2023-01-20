/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:06:24 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 01:06:35 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction servant a recuperer le nom de la variable d'environnement.
	Le nom est stocké dans la structure "t_var ptr".
*/
void	ft_get_name(char *str, t_var *ptr)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ptr->name = malloc(sizeof(char) * (i + 1));
	if (!ptr->name)
	{
		free(ptr);
		return ;
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		ptr->name[i] = str[i];
		i++;
	}
	ptr->name[i] = '\0';
}

/*
	Fonction servant a récupérer la valeur de la variable d'environnement.
	La valeur est stocké dans la structure "t_var ptr".
*/
void	ft_get_value(char *str, t_var *ptr)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
	{
		ft_malloc_empty(ptr);
		return ;
	}
	i++;
	ptr->value = ft_strdup(str + i);
	if (!ptr->value)
	{	
		free(ptr->name);
		free(ptr);
		return ;
	}
}

void	create_var_interr(t_data *minis)
{
	t_var	*ptr;

	ptr = malloc(sizeof(t_var));
	if (!ptr)
		ft_error("Malloc", minis, 0, 1);
	ptr->name = malloc(sizeof(char) * 2);
	if (!ptr->name)
		ft_error_ptr(minis, ptr, 1);
	ptr->name[0] = '?';
	ptr->name[1] = '\0';
	ptr->value = malloc(sizeof(char) * 2);
	if (!ptr->value)
		ft_error_ptr(minis, ptr, 1);
	ptr->value[0] = '1';
	ptr->value[1] = '\0';
	ptr->next = NULL;
	ptr->is_export = 0;
	ptr->is_print = 0;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}


void	create_var(t_data *minis, char **envp, int i)
{
	t_var	*ptr;

	ptr = malloc(sizeof(t_var));
	if (!ptr)
		ft_error("Malloc", minis, 0, 1);
	ft_get_name(envp[i], ptr);
	if (!ptr->name)
		ft_error_ptr(minis, ptr, 1);
	ft_get_value(envp[i], ptr);
	if (!ptr->value)
		ft_error_ptr(minis, ptr, 2);
	if (ptr->name && ptr->name[0] == '_' && ptr->name[1] == '\0')
		ptr->is_export = 0;
	else
		ptr->is_export = 1;
	ptr->is_print = 1;
	ptr->next = NULL;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}

/*
	Fonction servant a recuperer les variables d'environnement
	et de creer une liste chainée
*/
void	ft_create_env(t_data *minis, char **envp)
{
	int	i;

	minis->env = NULL;
	i = 0;
	while (envp[i])
	{
		create_var(minis, envp, i);
		i++;
	}
	create_var_interr(minis);
}
