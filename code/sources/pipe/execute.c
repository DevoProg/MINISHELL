/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:20:32 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:41:28 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	fonction qui execute une commande car elle est seule dans la ligne lue
*/
int	just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
	int	redi_pipe[2][2];
	int	res;

	if (!infile_error_message(&minis->cmd[0], 1))
		return (1);
	if (ft_is_not_fork(cmd))
	{
		butiltins_without_fork(minis, cmd, 0);
		return (0);
	}
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 0);
	if (cmd->res_fork == 0)
		fork_one_cmd(minis, envp, redi_pipe, cmd);
	close_redi_pipe(redi_pipe);
	waitpid(minis->cmd[0].res_fork, &res, 0);
	return (WEXITSTATUS(res));
}

/*
	fonction qui execute la premiere commande
*/
void	first_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 1, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_first_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

/*
	fonction qui execute la commande du millieu
*/
void	middle_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 2, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_middle_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

/*
	fonction qui execute la derniere commande
*/
void	last_cmd(t_data *minis, char **envp, int i)
{
	t_board	*cmd;
	int		redi_pipe[2][2];

	cmd = &minis->cmd[i];
	if (error_or_not_fork(minis, cmd, 3, i))
		return ;
	ft_pipe_redi(minis, redi_pipe);
	cmd->res_fork = fork();
	if (cmd->res_fork < 0)
		ft_error_fork(minis, redi_pipe, 1);
	if (cmd->res_fork == 0)
		fork_last_cmd(minis, envp, redi_pipe, i);
	close_redi_pipe(redi_pipe);
}

/*
	fonction qui execute toutes les commandes
	en fonction de leur emplacement dans la ligne lue
*/
int	ft_execute(t_data *minis, char **envp)
{
	int	i;
	int	res;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (i == 0)
			first_cmd(minis, envp, i);
		else if (i == minis->nb_cmd - 1)
		{
			last_cmd(minis, envp, i);
			if (!minis->cmd[i].cmd_path && !ft_is_builtins(&minis->cmd[i]))
				return (127);
		}
		else
			middle_cmd(minis, envp, i);
		i++;
	}
	close_all_pipes(minis);
	i = 0;
	while (i < minis->nb_cmd)
	{
		if (!ft_is_not_fork(&minis->cmd[i])
			&& infile_error_message(&minis->cmd[i], 0))
			waitpid(minis->cmd[i].res_fork, &res, 0);
		i++;
	}
	return (WEXITSTATUS(res));
}
