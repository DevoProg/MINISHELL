/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:13:11 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:39:30 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cpy_cmd(t_board *cmd, char *poss, int i)
{
	int	j;

	j = 0;
	while (cmd->tab[0][j])
	{
		poss[i] = cmd->tab[0][j];
		i++;
		j++;
	}
	poss[i] = '\0';
}

char	*cpy_path(t_data *minis, t_board *cmd, char *path, int *path_len)
{
	int		i;
	char	*poss;

	*path_len = 0;
	while (path[*path_len] && path[*path_len] != ':')
		(*path_len)++;
	i = *path_len;
	i += ft_strlen(cmd->tab[0]);
	poss = malloc(sizeof(char) * (i + 2));
	if (!poss)
		ft_error("Malloc", minis, 3, 1);
	i = 0;
	while (path[i] && path[i] != ':')
	{
		poss[i] = path[i];
		i++;
	}
	poss[i] = '/';
	i++;
	cpy_cmd(cmd, poss, i);
	return (poss);
}

char	*check_acces_path(t_data *minis, t_board *cmd)
{
	char	*res;

	if(!cmd->tab[0])
		return (NULL);
	if (access(cmd->tab[0], F_OK) == 0 && access(cmd->tab[0], X_OK) != 0)
	{
		res = ft_strdup(cmd->tab[0]);
		if (!res)
			ft_error("Malloc", minis, 3, 1);
		ft_putstr_fd("Permission denied :", 2);
		ft_putstr_fd(cmd->tab[0], 2);
		ft_putchar_fd('\n', 2);
		g_code_erreur = 126;
		return (res);
	}	
	if (access(cmd->tab[0], X_OK) == 0)
	{
		res = ft_strdup(cmd->tab[0]);
		if (!res)
			ft_error("Malloc", minis, 3, 1);
		return (res);
	}
	return (NULL);
}

int	ft_move_path(char *path, int *path_len)
{
	if (path[*path_len] == ':')
		return (1);
	return (0);
}

char	*ft_try_path(t_data *minis, char *path, t_board *cmd)
{
	char	*poss;
	char	*res;
	int		path_len;

	if(!cmd->tab[0])
		return (NULL);
	res = check_acces_path(minis, cmd);
	if (res)
		return (res);
	if (!path || !*path)
		return (NULL);
	poss = cpy_path(minis, cmd, path, &path_len);
	if (access(poss, X_OK) == 0)
		return (poss);
	path += ft_move_path(path, &path_len);
	if (path[path_len])
	{
		res = ft_try_path(minis, path + path_len, cmd);
		if (res)
		{
			free(poss);
			return (res);
		}
	}
	free(poss);
	return (NULL);
}
