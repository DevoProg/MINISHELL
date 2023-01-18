/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:33:55 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:39:35 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	res_cmd_to_pipe(int fd[2], int redi_pipe[2], t_board *cmd, int is_outf)
{
	t_redi	*ptr;
	int		res;
	char	*buf;

	if (is_outf == 1)
		open_all_redi_files(cmd);
	while (1)
	{
		buf = malloc(sizeof(char) * 2);
		if (!buf)
			return(0);
		res = read(fd[0], buf, 1);
		if (res == -1 || res == 0)
		{
			free(buf);
			break ;
		}
		buf[1] = '\0';
		write(redi_pipe[1], buf, 1);
		if (is_outf == 1 && is_redi_outfile(cmd))
		{
			ptr = last_redi_out(cmd->redi);
			write(ptr->file_fd, buf, 1);
		}
		free(buf);
	}
	if (is_outf == 1)
		close_all_redi_files(cmd);
	return (1);
}

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

/*
	Fonction qui ecrit le resultat de la commande dans 
	le dernier fichier de redirection de sortie ou le print
*/
void	write_in_last_file(char *buf, t_board *cmd)
{
	t_redi	*ptr;

	if (!is_redi_outfile(cmd))
	{
		ft_printf("%s", buf);
		return ;
	}
	ptr = last_redi_out(cmd->redi);
	if (ptr)
		write(ptr->file_fd, buf, 1);
}

/*
	Fonction qui lit le resultat de la commande(pipe redi)
*/
void	redirect_outfile(t_data *minis, t_board *cmd, int redi_pipe[2][2])
{
	char	*buf;
	int		res_read;

	open_all_redi_files(cmd);
	while (1)
	{
		buf = malloc(sizeof(char) * 2);
		if (!buf)
		{
			close(redi_pipe[0][0]);
			close(redi_pipe[1][0]);
			if(minis->nb_cmd > 1)
				close_all_pipes(minis);
			ft_error("Malloc", minis, 3, 1);
		}
		res_read = read(redi_pipe[1][0], buf, 1);
		if (res_read == -1 || res_read == 0)
		{
			free(buf);
			return ;
		}
		buf[1] = '\0';
		write_in_last_file(buf, cmd);
		free(buf);
	}
	close_all_redi_files(cmd);
}
