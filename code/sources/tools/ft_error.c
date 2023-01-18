/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:47:29 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 00:48:33 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_struct_cmd(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (minis->cmd[i].line_cmd)
			free(minis->cmd[i].line_cmd);
		if (minis->cmd[i].tab)
			free_tab(minis->cmd[i].tab, minis->cmd[i].nb_words);
		if (minis->cmd[i].cmd_path)
			free(minis->cmd[i].cmd_path);
		i++;
	}
	free(minis->cmd);
}

void	free_tab(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if(tab[j])
			free(tab[j]);
		j++;
	}
	free(tab);
}

void	free_list(t_var *env)
{
	if(!env)
		return ;
	while (env->next)
	{
		env = ft_delete_first_node(env);
	}
	ft_delete_first_node(env);
}

void	ft_error(char *message, t_data *minis, int z, int is_perror)
{
	if (z >= 0)
		free_list(minis->env);
	if (z > 0)
	{
		//rl_clear_history();
		free(minis->line);
	}
	if (z == 1)
		free_tab(minis->tab_cmd, minis->nb_cmd + 1);
	if (z >= 2)
		free_struct_cmd(minis);
	if(z >= 3)
		free_redi(minis);
	if (is_perror == 1)
		perror(message);
	else
		ft_putstr_fd(message, 2);
	exit(1);
}

void ft_error_fork(t_data *minis, int redi_pipe[2][2], int y)
{
	close(redi_pipe[0][1]);
	close(redi_pipe[1][1]);
	close(redi_pipe[0][0]);
	close(redi_pipe[1][0]);
	if(y == 1)
		close_all_pipes(minis);
	ft_error("Fork", minis, 3, 1);
}

void ft_error_pipe(t_data *minis, int redi_pipe[2][2], int y, int z)
{
	if(y == 0 || y == 1)
	{
		close(redi_pipe[0][1]);
		close(redi_pipe[1][1]);
	}
	if(y == 0 || y == 2)
	{
		close(redi_pipe[0][0]);
		close(redi_pipe[1][0]);
	}
	if(z == 1)
		close_all_pipes(minis);
	ft_error("Malloc", minis, 3, 1);
}

void ft_error_in_fork(t_data *minis, int redi_pipe[2][2])
{
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	ft_error("Malloc", minis, 3, 1);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	ft_error("Malloc", minis, 3, 1);

}
