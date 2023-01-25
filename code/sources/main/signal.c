/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adevos <adevos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:03:10 by alondot           #+#    #+#             */
/*   Updated: 2023/01/25 21:12:36 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (code_erreur != 130)
			rl_redisplay();
	}
}

/*
	Fonction interceptant les signaux.
	Le premier appel de signal sert a ignorer les appels de ctrl+\.
	Le second exec le signal_handler qui s'occupera de reprompt.	
*/
void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

/*
	Fonction servant a gerer le cas d'un signal ctrl+d.
	Free le minishell avant le exit.
*/
void	line_empty(t_data *minis)
{
	free_list(minis->env);
	rl_clear_history();
	if (errno == ENOMEM)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
