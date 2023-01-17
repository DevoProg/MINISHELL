/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:45:13 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:49:07 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction qui compte le nombre de lettre pour la nouvelle string
*/
int	count_new_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count += count_to_new_quote(str, &i, 39);
		else if (str[i] == 34)
			count += count_to_new_quote(str, &i, 34);
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

/*
	Fonction qui sert a copier la string jusqu'au prochain single quote
*/
void	write_to_new_singlequote(char *str, char *new, int *i, int *j)
{
	*i += 1;
	while (str[*i] && str[*i] != 39)
	{
		new[*j] = str[*i];
		*i += 1;
		*j += 1;
	}
	if (str[*i] == 39)
		*i += 1;
}

/*
	Fonction qui sert a copier la string jusqu'au prochain double quote
*/
void	write_to_new_doublequote(char *str, char *new, int *i, int *j)
{
	*i += 1;
	while (str[*i] && str[*i] != 34)
	{
		new[*j] = str[*i];
		*i += 1;
		*j += 1;
	}
	if (str[*i] == 34)
		*i += 1;
}

/*
	Fonction qui sert a allouer de la memoire et copier la nouvelle string
*/
char	*get_new_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = count_new_quote(str);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		exit(1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 39)
			write_to_new_singlequote(str, new, &i, &j);
		else if (str[i] == 34)
			write_to_new_doublequote(str, new, &i, &j);
		else
			ft_write(new, str, &i, &j);
	}
	new[j] = '\0';
	free(str);
	return (new);
}

/*
	Fonction qui sert a remplacer chaque element du tableau 
	par son contenu en retirant les quotes
*/
void	delete_quote(t_data *minis)
{
	int	i;
	int	j;

	i = 0;
	while (i < minis->nb_cmd)
	{
		j = 0;
		while (j < minis->cmd[i].nb_words - 1)
		{
			minis->cmd[i].tab[j] = get_new_str(minis->cmd[i].tab[j]);
			j++;
		}
		i++;
	}
}
