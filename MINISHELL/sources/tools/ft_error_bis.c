/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:23:41 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:24:34 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_to_pipe(t_data *minis, int i)
{
	int	z;

	z = 0;
	while (z < i)
	{
		close(minis->cmd[z].pipe_fd[0]);
		close(minis->cmd[z].pipe_fd[1]);
			z++;
	}
	ft_error("Pipe", minis, 3, 1);
}
