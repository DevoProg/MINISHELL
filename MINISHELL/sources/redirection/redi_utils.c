/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:31:51 by alondot           #+#    #+#             */
/*   Updated: 2023/01/25 21:05:28 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redi_infile(t_redi *ptr)
{
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
	{
		if (ptr->type == INFILE)
			return (1);
		if (ptr->type == D_INFILE)
			return (1);
		ptr = ptr->next;
	}
	if (ptr->type == INFILE)
		return (1);
	if (ptr->type == D_INFILE)
		return (1);
	return (0);
}

int	is_redi_outfile(t_redi *ptr)
{
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
	{
		if (ptr->type == OUTFILE)
			return (1);
		if (ptr->type == D_OUTFILE)
			return (1);
		ptr = ptr->next;
	}
	if (ptr->type == OUTFILE)
		return (1);
	if (ptr->type == D_OUTFILE)
		return (1);
	return (0);
}

void	try_open_file(t_redi *ptr)
{
	if (ptr->type == OUTFILE || ptr->type == D_OUTFILE)
	{
		if (ptr->type == OUTFILE)
			ptr->file_fd = open(ptr->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else
			ptr->file_fd = open(ptr->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (ptr->file_fd == -1)
		{
			ft_putstr_fd("Error to open file :", 2);
			ft_putstr_fd(ptr->file, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
	}
}

void	open_all_redi_files(t_board *cmd)
{
	t_redi	*ptr;

	if (!cmd->redi)
		return ;
	ptr = cmd->redi;
	while (ptr->next != NULL)
	{
		try_open_file(ptr);
		ptr = ptr->next;
	}
	try_open_file(ptr);
}

void	close_all_redi_files(t_board *cmd)
{
	t_redi	*ptr;

	if (!cmd->redi)
		return ;
	ptr = cmd->redi;
	while (ptr->next != NULL)
	{
		if (ptr->type == OUTFILE || ptr->type == D_OUTFILE)
			close(ptr->file_fd);
		ptr = ptr->next;
	}
	if (ptr->type == OUTFILE || ptr->type == D_OUTFILE)
		close(ptr->file_fd);
}
