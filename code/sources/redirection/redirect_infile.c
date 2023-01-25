/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:41:48 by alondot           #+#    #+#             */
/*   Updated: 2023/01/25 21:08:01 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redi	*last_redi_out(t_redi *redi)
{
	t_redi	*ptr;
	t_redi	*res;

	if (!redi)
		return (NULL);
	ptr = redi;
	res = NULL;
	while (ptr->next != NULL)
	{
		if (ptr->type == OUTFILE || ptr->type == D_OUTFILE)
			res = ptr;
		ptr = ptr->next;
	}
	if (ptr->type == OUTFILE || ptr->type == D_OUTFILE)
			res = ptr;
	return (res);
}

int	d_infile_to_pipe(t_redi *ptr, int redi_pipe[2])
{
	char	*str;
	int		i;
	int		res;

	res = 0;
	if (!ptr)
		return (res);
	while (1)
	{
		str = readline(">");
		if (str && *str && ft_strcmp(str, ptr->file) == 0)
			break ;
		i = ft_strlen(str);
		if (!is_redi_infile(ptr->next))
		{
			write(redi_pipe[1], str, i);
			write(redi_pipe[1], "\n", 1);
			res = 1;
		}
		str = NULL;
		free(str);
	}
	return (res);
}

/*
	Fonction qui ecrit dans le pipes des redirections les contenu des fichiers
*/
int	infile_to_pipe(t_redi *ptr, int redi_pipe[2])
{
	int	fd;
	int	res;

	res = 0;
	fd = open(ptr->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error to open file :", 2);
		ft_putstr_fd(ptr->file, 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
	if (!is_redi_infile(ptr->next))
	{
		dup2(fd, redi_pipe[0]);
		res = 1;
	}
	close(fd);
	return (res);
}

/*
	Fonction qui regarde s'il y a un fichier d'entrée en redirection
*/
int	redirect_infile(t_board *cmd, int redi_pipe[2])
{
	t_redi	*ptr;
	int		res;

	res = 0;
	if (!cmd->redi)
		return (res);
	ptr = cmd->redi;
	while (ptr->next != NULL)
	{
		if (ptr->type == INFILE)
			res = infile_to_pipe(ptr, redi_pipe);
		if (ptr->type == D_INFILE)
			res = d_infile_to_pipe(ptr, redi_pipe);
		ptr = ptr->next;
	}
	if (ptr->type == INFILE)
		res = infile_to_pipe(ptr, redi_pipe);
	if (ptr->type == D_INFILE)
		res = d_infile_to_pipe(ptr, redi_pipe);
	return (res);
}
