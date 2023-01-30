/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:22:36 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:23:05 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_signals_h_doc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_h_doc);
}

void	signal_handler_h_doc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	line_empty_h_doc(void)
{
	exit(0);
}
