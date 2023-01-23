/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:03:10 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 00:19:21 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
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
	Free tout les elements de minis->env, afin de preparer le exit().
*/
// void	free_env(t_data *minis)
// {
// 	t_var	*tmp;

// 	while (minis->env->next != NULL)
// 	{
// 		tmp = minis->env;
// 		minis->env = minis->env->next;
// 		if (tmp->name)
// 		{
// 			tmp->name = NULL;
// 			free(tmp->name);
// 		}
// 		if (tmp->value)
// 		{
// 			tmp->value = NULL;
// 			free(tmp->value);
// 		}
// 		if (tmp)
// 		{
// 			tmp->next = NULL;
// 			tmp = NULL;
// 			free(tmp);
// 		}
// 	}
// 	free(minis->env->name);
// 	free(minis->env->value);
// 	free(minis->env);
// }

/*
	Fonction servant a gerer le cas d'un signal ctrl+d.
	Free le minishell avant le exit.
*/
void	line_empty(t_data *minis)
{
	free_list(minis->env);
	if (errno == ENOMEM)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
