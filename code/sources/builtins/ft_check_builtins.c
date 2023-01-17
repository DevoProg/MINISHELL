/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:51:20 by alondot           #+#    #+#             */
/*   Updated: 2023/01/16 23:12:10 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ft_exit(minis);
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
		ft_exit(minis);
	else if (ft_strcmp(cmd->tab[0], "cd") == 0)
		ft_cd(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "export") == 0 && cmd->nb_words > 2)
		ft_export(minis, cmd);
	else if (ft_strcmp(cmd->tab[0], "unset") == 0)
		ft_unset(minis, cmd);
}
