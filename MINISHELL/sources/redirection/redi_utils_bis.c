/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:17:29 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:18:59 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe_redi(t_data *minis, int redi_pipe[2][2])
{
	if (pipe(redi_pipe[0]) == -1)
	{
		close_all_pipes(minis);
		ft_error("Pipe", minis, 3, 1);
	}
	if (pipe(redi_pipe[1]) == -1)
	{
		close_all_pipes(minis);
		close(redi_pipe[0][1]);
		close(redi_pipe[0][0]);
		ft_error("Pipe", minis, 3, 1);
	}
}

void	close_redi_pipe(int redi_pipe[2][2])
{
	close(redi_pipe[0][0]);
	close(redi_pipe[0][1]);
	close(redi_pipe[1][0]);
	close(redi_pipe[1][1]);
}

int	ft_is_redi(char *str, size_t i)
{
	if (ft_strncmp("<<", str + i, 2) == 0 && is_no_open_quote(str, i))
		return (D_INFILE);
	else if (ft_strncmp("<", str + i, 1) == 0 && is_no_open_quote(str, i))
		return (INFILE);
	else if (ft_strncmp(">>", str + i, 2) == 0 && is_no_open_quote(str, i))
		return (D_OUTFILE);
	else if (ft_strncmp(">", str + i, 1) == 0 && is_no_open_quote(str, i))
		return (OUTFILE);
	return (0);
}

t_redi	*lst_last_redi(t_redi *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add_redi(t_redi **lst, t_redi *new)
{
	t_redi	*aux_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = lst_last_redi(*lst);
		aux_lst->next = new;
	}
}
