/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:31:35 by alondot           #+#    #+#             */
/*   Updated: 2023/01/18 03:17:27 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	each_things_to_do(t_data *minis, char **envp)
{
	int	res;

	add_history(minis->line);
	line_to_cmd(minis);
	init_struct(minis);
	redirection(minis);
	put_env_var(minis);
	ft_split_cmd(minis);
	delete_quote(minis);
	res = ft_pipe(minis, envp);
	if (!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]))
		put_res_pipe(minis, res);
	free_struct((minis));
}

/*
	Fonction de la loop principale du shell.
	Gere les lignes recues et effectue tout type d'actions.
*/
void	minishell_loop(char **envp)
{
	t_data	minis;

	init_signals();
	ft_create_env(&minis, envp);
	while (1)
	{
		minis.line = readline(">$");
		if (!minis.line)
		{
			line_empty(&minis);
			exit(1);
		}
		else if (minis.line && *minis.line)
			each_things_to_do(&minis, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		minishell_loop(envp);
	(void)argv;
	(void)argc;
	return (1);
}
