/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:07:36 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:35:50 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_one_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], t_board *cmd)
{
	if(redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], 0);
	if(redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], 1);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(cmd))
		execve(cmd->cmd_path, cmd->tab, envp);
	builtins_with_fork(minis, cmd);
	exit(1);
}

void	fork_first_cmd(t_data *minis, char **envp,
		int redi_pipe[2][2], int i)
{
	t_board *cmd;

	cmd = &minis->cmd[i];
	if(redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], 0);
	if(redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], minis->cmd[0].pipe_fd[1]);
	dup2(minis->cmd[0].pipe_fd[1], 1);
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
	t_board *cmd;

	cmd = &minis->cmd[i];
	if(redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], minis->cmd[i - 1].pipe_fd[0]);
	dup2(minis->cmd[i - 1].pipe_fd[0], 0);
	if(redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], minis->cmd[i].pipe_fd[1]);
	dup2(minis->cmd[i].pipe_fd[1], 1);
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
	t_board *cmd;

	cmd = &minis->cmd[i];
	if(redirect_infile(cmd, redi_pipe[0]))
		dup2(redi_pipe[0][0], minis->cmd[i - 1].pipe_fd[0]);
	dup2(minis->cmd[i - 1].pipe_fd[0], 0);
	if(redirect_outfile(cmd, redi_pipe[1]))
		dup2(redi_pipe[1][1], 1);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	if (!ft_is_builtins(&minis->cmd[i]))
		execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
	builtins_with_fork(minis, &minis->cmd[i]);
	exit(1);
}
