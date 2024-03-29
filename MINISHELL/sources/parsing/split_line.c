/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:50:01 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:52:55 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_command(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_no_open_quote(line, i) && line[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

char	*str_cpy_cmd(char *line, int *i, t_data *minis)
{
	char	*new;
	int		j;
	int		k;

	j = ft_len_cmd(line);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		ft_error("Malloc", minis, 1, 1);
	j = 0;
	k = 0;
	if (line[j] == '|')
		j++;
	while (line[j])
	{
		if (is_no_open_quote(line, j) && line[j] == '|')
			break ;
		new[k] = line[j];
		k++;
		j++;
	}
	new[k] = '\0';
	*i += j;
	return (new);
}

void	line_to_cmd(t_data *minis)
{
	int	i;
	int	nb_cmd;

	if (minis->line && *minis->line == '|')
		ft_error("Parsing error", minis, 0, 0);
	nb_cmd = ft_count_command(minis->line);
	minis->tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!minis->tab_cmd)
		ft_error("Malloc", minis, 0, 1);
	i = 0;
	minis->nb_cmd = 0;
	while (minis->nb_cmd < nb_cmd)
	{
		minis->tab_cmd[minis->nb_cmd] = str_cpy_cmd(minis->line + i, &i, minis);
		minis->nb_cmd++;
	}
	minis->tab_cmd[minis->nb_cmd] = malloc(sizeof(char) * 1);
	if (!minis->tab_cmd[minis->nb_cmd])
		ft_error("Malloc", minis, 1, 1);
	minis->tab_cmd[minis->nb_cmd][0] = '\0';
}

void	ft_write(char *new, char *str, int *i, int *j)
{
	new[*j] = str[*i];
	*i += 1;
	*j += 1;
}
