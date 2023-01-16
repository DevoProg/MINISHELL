/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:41:43 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 19:47:07 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction qui retourne une chaine de charactere allouée 
	avec le nom de la variable d'evironnement
*/
char	*get_name(char *str, t_data *minis)
{
	int		i;
	char	*str_ret;

	str_ret = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	str_ret = malloc(sizeof(char) * (i + 1));
	if (!str_ret)
		ft_error("Malloc", minis, 2, 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		str_ret[i] = str[i];
		i++;
	}
	str_ret[i] = '\0';
	return (str_ret);
}

/*
	Fonction pour assigner une nouvelle valeur
   	a une node qui possede deja une valeur
*/
void	ft_assign_new_value(t_data *minis, char *str, char *name)
{
	t_var	*ptr;

	ptr = lst_name_finding(minis->env, name);
	free(ptr->value);
	ft_get_value(str, ptr);
}

/*
	Creation d'une	nouvelle node et ajout dans la liste
*/
void	ft_create_variable(t_data *minis, char *str)
{
	t_var	*ptr;

	ptr = malloc(sizeof(t_var));
	if (!ptr)
		ft_error("Malloc", minis, 2, 1);
	ptr->next = NULL;
	ft_get_value(str, ptr);
	if (!ptr->value)
		ft_error("Malloc", minis, 2, 1);
	ft_get_name(str, ptr);
	if (!ptr->name)
		ft_error("Malloc", minis, 2, 1);
	ptr->is_export = 1;
	ptr->is_print = 0;
	lst_add(&minis->env, ptr);
	ptr = NULL;
}

int	export_arg(t_data *minis, t_board *cmd, int i)
{
	char	*name;

	name = get_name(cmd->tab[i], minis);//alloue name
	if (ft_strchr(cmd->tab[i], '=') && !list_chr(minis->env, name))//si le name existe pas dans la liste chainee de variable d'env
		ft_create_variable(minis, cmd->tab[i]);//alors on cree une nouvelle node ett on la met dans la liste
	else if (ft_strchr(cmd->tab[i], '=') && list_chr(minis->env, name))//si elle existe deja dans la liste
		ft_assign_new_value(minis, cmd->tab[i], name);//alors on lui donne une nouvelle valuer
	else if (!ft_strchr(cmd->tab[i], '=') && list_chr(minis->env, name))//si il n'y a pas d'egal et qu'elle existe deja
	{
		free(name);
		return (0);
	}
	else if (!ft_strchr(cmd->tab[i], '=') && !list_chr(minis->env, name))//si pas egal et existe pas ->vide
		ft_create_variable(minis, cmd->tab[i]);
	free(name);//désalloue name
	return (1);
}

/*
	Cas commande : EXPORT.
*/
void	ft_export(t_data *minis, t_board *cmd)
{
	int	i;

//si export ne possede pas d'argument il doit printlist
	if (cmd->nb_words == 2)
	{
		print_list(minis->env, 1);
		put_res_pipe(minis, 0);
		return ;
	}
	i = 1;
	while (i < cmd->nb_words - 1)
	{
		if (!export_arg(minis, cmd, i))
			return ;
		i++;
	}
	put_res_pipe(minis, 0);
}
