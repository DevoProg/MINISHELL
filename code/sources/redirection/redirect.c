/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:19:44 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:16:20 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction qui retourne le fichier atttribué a la redirection
*/
char	*get_file_redi(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (*str && *str == ' ')
		str++;
	while (str[i] && str[i] != ' ')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*
	Fonction qui stock la redirection dans une liste chainée de redirection
*/
void	stock_redi(t_data *minis, t_board *cmd, char *str, int res)
{
	t_redi	*redi;
	int		j;

	j = 0;
	if (res == INFILE || res == OUTFILE)
		j = 1;
	else if (res == D_INFILE || res == D_OUTFILE)
		j = 2;
	redi = malloc(sizeof(t_redi));
	if (!redi)
		ft_error("Malloc", minis, 3, 1);
	redi->type = res;
	redi->file = get_file_redi(str + j);
	if (!redi->file)
	{
		free(redi);
		ft_error("Malloc", minis, 3, 1);
	}
	redi->next = NULL;
	lst_add_redi(&cmd->redi, redi);
}

/*
	Fonction qui retire les redirections de la commande
*/
void	clean_this_redi(char *str, int j, int res)
{
	str[j] = ' ';
	if (res == D_INFILE || res == D_OUTFILE)
	{
		j++;
		str[j] = ' ';
	}
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != ' ')
	{
		str[j] = ' ';
		j++;
	}
}

/*
	Fonction qui parcourt toutes les commandes
   	pour stocker les redirection dans la strucutre
*/
void	redirection(t_data *minis)
{
	int		i;
	size_t	j;
	int		res;

	i = 0;
	while (i < minis->nb_cmd)
	{
		j = 0;
		minis->cmd[i].redi = NULL;
		while (j < ft_strlen(minis->cmd[i].line_cmd))
		{
			res = ft_is_redi(minis->cmd[i].line_cmd, j);
			if (res != 0)
			{
				stock_redi(minis, &minis->cmd[i],
					minis->cmd[i].line_cmd + j, res);
				clean_this_redi(minis->cmd[i].line_cmd, j, res);
				if (res == D_INFILE || res == D_OUTFILE)
					j++;
			}
			j++;
		}
		i++;
	}
}
