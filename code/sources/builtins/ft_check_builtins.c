/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:51:20 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:21:16 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    Cas commande : EXIT
    Fonction servant a exit. 
    Free tout les elements en mémoire.
*/
int	ft_is_digital(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_data *minis, t_board *cmd)
{
	int	exit_code;
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd->nb_words > 3)
	{
		ft_putstr_fd("too much argument for exit\n", 2);
		put_res_pipe(minis, 1);
		return ;
	}
	if(cmd->nb_words == 3)
	{
		if (cmd->tab[1][0] == '-')
			i++;
		if (!ft_is_digital(cmd->tab[1] + i))
			exit_code = 255;
		else
			exit_code = ft_atoi(cmd->tab[1]);
	}
	else
		exit_code = 0;
	rl_clear_history();
	free_struct(minis);
	free_list(minis->env);
	free_redi(minis);
	exit(exit_code);
}

/*
	Fonction servant a check si une commande contient les différentes fct bash.
*/
void	builtins_with_fork(t_data *minis, t_board *cmd)
{
	if (ft_strcmp(cmd->tab[0], "pwd") == 0)
		ft_pwd(minis);
	else if (ft_strcmp(cmd->tab[0], "env") == 0)
		ft_envp(minis);
	else if (ft_strcmp(cmd->tab[0], "echo") == 0)
		ft_echo(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "exit") == 0)
		ft_exit(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}

/*
	Fonction qui execute les buitlins si il y a pas besoin de fork
*/
void	butiltins_without_fork(t_data *minis, t_board *cmd, int i)
{
	if (minis->nb_cmd != 1 && i != (minis->nb_cmd - 1))
		return ;
	if (ft_strcmp(cmd->tab[0], "exit") == 0)
		ft_exit(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0 && cmd->nb_words > 2)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}
