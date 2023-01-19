/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:24:39 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:04:13 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    Cas commande : PWD.
*/
void	ft_pwd(t_data *minis)
{
	char	cwd[PATH_LEN];

	if (getcwd(cwd, PATH_LEN))
	{
		ft_putendl_fd(cwd, 1);
		put_res_pipe(minis, 0);
		return ;
	}
	put_res_pipe(minis, 1);
}

/*
    Cas commande : ENV.
*/
void	ft_envp(t_data *minis)
{
	print_list(minis->env, 0);
	put_res_pipe(minis, 0);
}

/*
    Cas commande : ECHO.
*/
void	ft_echo(t_data *minis, t_board *cmd)
{
	int	i;
	int	option;

	if (cmd->nb_words == 2)
	{
		ft_putchar_fd('\n', 1);
		put_res_pipe(minis, 0);
		return ;
	}
	if (ft_strcmp(cmd->tab[1], "-n") == 0)
	{
		option = 1;
		i = 2;
	}
	else
	{
		option = 0;
		i = 1;
	}
	ft_echo_bis(minis, cmd, i, option);
}

void	ft_echo_bis(t_data *minis, t_board *cmd, int i, int option)
{
	while (i < cmd->nb_words - 1)
	{
		if ((i > 1 && option == 0) || (i > 2 && option == 1))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd->tab[i], 1);
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', 1);
	put_res_pipe(minis, 0);
}

/*
    Cas commande : EXIT
    Fonction servant a exit. 
    Free tout les elements en mémoire.
*/
void	ft_exit(t_data *minis, t_board *cmd)
{
	int exit_code;

	if(cmd->nb_words == 2)
		exit_code = 0;
	else if(cmd->nb_words == 3)
		exit_code = ft_atoi(cmd->tab[1]);
	else
	{
		ft_putstr_fd("too much argument for exit\n", 2);
		put_res_pipe(minis, 1);
		return ;
	}
	free_struct(minis);
	free_list(minis->env);
	free_redi(minis);
	exit(exit_code);
}
