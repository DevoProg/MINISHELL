/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adevos <adevos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:31:35 by alondot           #+#    #+#             */
/*   Updated: 2023/01/24 21:35:57 by adevos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	code_erreur;

void	each_things_to_do(t_data *minis, char **envp)
{
	add_history(minis->line);
	if(!parse(minis, minis->line))
		return ;
	line_to_cmd(minis);
	init_struct(minis);
	put_env_var(minis);
	delete_quote(minis);
	redirection(minis);
	ft_split_cmd(minis);
	code_erreur = 130;
	code_erreur = ft_pipe(minis, envp);
	if (!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]))
		put_res_pipe(minis, code_erreur);
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
