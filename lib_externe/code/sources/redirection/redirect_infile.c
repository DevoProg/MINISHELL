/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:41:48 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:19:08 by alondot          ###   ########.fr       */
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

void	d_infile_to_pipe(t_redi *ptr, int redi_pipe[2])
{
	char	*str;
	int		i;

	if (!ptr)
		return ;
	while (1)
	{
		str = readline(">");
		if (str && *str && ft_strcmp(str, ptr->file) == 0)
		{
			break ;
		}
		i = ft_strlen(str);
		write(redi_pipe[1], str, i);
		write(redi_pipe[1], "\n", 1);
		str = NULL;
		free(str);
	}
}

/*
	Fonction qui ecrit dans le pipes des redirections les contenu des fichiers
*/
void	infile_to_pipe(t_redi *ptr, int redi_pipe[2])
{
	int		fd;
	char	*buf;
	int		len;

	fd = open(ptr->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error to open file :", 2);
		ft_putstr_fd(ptr->file, 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
	while (1)
	{
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
		len = ft_strlen(buf);
		write(redi_pipe[1], buf, len);
		free(buf);
	}
	close(fd);
}

/*
	Fonction qui regarde s'il y a un fichier d'entrée en redirection
*/
void	redirect_infile(t_board *cmd, int redi_pipe[2])
{
	t_redi	*ptr;

	if (!cmd->redi)
		return ;
	ptr = cmd->redi;
	while (ptr->next != NULL)
	{
		if (ptr->type == INFILE)
			infile_to_pipe(ptr, redi_pipe);
		if (ptr->type == D_INFILE)
			d_infile_to_pipe(ptr, redi_pipe);
		ptr = ptr->next;
	}
	if (ptr->type == INFILE)
		infile_to_pipe(ptr, redi_pipe);
	if (ptr->type == D_INFILE)
		d_infile_to_pipe(ptr, redi_pipe);
}
