/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:07:36 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 01:10:38 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_one_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], t_board *cmd)
{
	redirect_infile(cmd, redi_pipe[0]);
	if (is_redi_outfile(cmd))
		dup2(redi_pipe[1][1], STDOUT_FILENO);
	if (is_redi_infile(cmd))
		dup2(redi_pipe[0][0], STDIN_FILENO);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(cmd))
		execve(cmd->cmd_path, cmd->tab, envp);
	builtins_with_fork(minis, cmd);
	exit(1);
}

void	fork_first_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	redirect_infile(&minis->cmd[0], redi_pipe[0]);
	//if (is_redi_infile(&minis->cmd[i]))
		dup2(redi_pipe[0][0], STDIN_FILENO);
	dup2(redi_pipe[1][1], STDOUT_FILENO);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[0]))
		execve(minis->cmd[0].cmd_path, minis->cmd[0].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	exit(1);
}

void	fork_middle_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	if (!ft_is_not_fork(&minis->cmd[i - 1]))
	{
		if(!res_cmd_to_pipe(minis->cmd[i - 1].pipe_fd,
			redi_pipe[0], &minis->cmd[i], 0))
			ft_error_in_fork(minis, redi_pipe);
		redirect_infile(&minis->cmd[i], redi_pipe[0]);
	}
	dup2(redi_pipe[0][0], STDIN_FILENO);
	dup2(redi_pipe[1][1], STDOUT_FILENO);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[i]))
		execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	exit(1);
}

void	fork_last_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	if (!ft_is_not_fork(&minis->cmd[i - 1]))
	{
		if(!res_cmd_to_pipe(minis->cmd[i - 1].pipe_fd, redi_pipe[0],
			&minis->cmd[i], 0))
			ft_error_in_fork(minis, redi_pipe);
		redirect_infile(&minis->cmd[i], redi_pipe[0]);
	}
	dup2(redi_pipe[0][0], STDIN_FILENO);
	if (is_redi_outfile(&minis->cmd[i]))
		dup2(redi_pipe[1][1], STDOUT_FILENO);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[i]))
		execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	exit(1);
}
