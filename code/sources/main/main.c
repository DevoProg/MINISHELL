/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:31:35 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:49:43 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	each_things_to_do(t_data *minis, char **envp)
{
	int	res;

	//add_history(minis->line);
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
void minishell_loop(char **envp)
{
	t_data minis;

	init_signals();									// Analyse les siganux recus
	
	ft_create_env(&minis, envp);					//ne pas oublier de free avec les exit	//creation d'une liste chainée avec les variable d'env
	//while(1)										//looop qui lit avec un prompt
	//{
		minis.line = ft_strdup("ls | cat | cat");
		if(!minis.line)								// pour le control D
		{
			line_empty(&minis);						// Free minis si signal ctrl+d, puis exit
			exit(1);
		}
		else if(minis.line && *minis.line)
			each_things_to_do(&minis, envp);
	//}
	free_list(minis.env);
	
	//rl_clear_history();
	//free_history_entry(current_history());
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		minishell_loop(envp);
	(void)argv;
	(void)argc;
	return (1);
}
