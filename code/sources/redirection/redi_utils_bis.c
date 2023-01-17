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

void	ft_pipe_redi(int redi_pipe[2][2])
{
	if (pipe(redi_pipe[0]) == -1)
		exit(1);
	if (pipe(redi_pipe[1]) == -1)
		exit(1);
}

/*
	Ferme tous les pipes de redirections
*/
void	close_redi_pipe(int redi_pipe[2][2])
{
	close(redi_pipe[0][0]);
	close(redi_pipe[0][1]);
	close(redi_pipe[1][0]);
	close(redi_pipe[1][1]);
}

/*
	Fonction qui regarde s'il il y a une redirection
*/
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

/*
	Fonction qui retourne la liste de la derniere redi
*/
t_redi	*lst_last_redi(t_redi *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
	Fonction qui lajoute la redirection a  la liste chainée
*/
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
