/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adevos <adevos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:31:35 by alondot           #+#    #+#             */
/*   Updated: 2023/01/25 21:15:40 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_code_erreur;

void	each_things_to_do(t_data *minis, char **envp)
{
	int	res;

	add_history(minis->line);
	put_res_pipe(minis, g_code_erreur);
	if (!parse(minis, minis->line))
		return ;
	line_to_cmd(minis);
	init_struct(minis);
	put_env_var(minis);
	redirection(minis);
	delete_quote(minis);
	ft_split_cmd(minis);
	res = ft_pipe(minis, envp);
	if (!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]) && g_code_erreur != 126)
		g_code_erreur = res;
	free_struct((minis));
}

void	minishell_loop(char **envp)
{
	t_data	minis;

	g_code_erreur = 0;
	ft_create_env(&minis, envp);
	while (1)
	{
		init_signals();
		minis.line = readline("minishell$ ");
		if (!minis.line)
		{
			line_empty(&minis);
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
