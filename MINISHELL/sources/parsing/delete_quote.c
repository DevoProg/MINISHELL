/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:45:13 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:19:28 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_new_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = count_new_quote(str);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
	{
		free(str);
		return (NULL);
	}
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

void	delete_quote(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		minis->cmd[i].line_cmd = get_new_str(minis->cmd[i].line_cmd);
		if (!minis->cmd[i].line_cmd)
			ft_error("Malloc", minis, 2, 1);
		i++;
	}
}