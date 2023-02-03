/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:20:32 by alondot           #+#    #+#             */
/*   Updated: 2023/01/31 11:21:46 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_bis(t_data *minis, char **envp, int i)
{
	if (i == 0)
		first_cmd(minis, envp, i);
	else if (i == minis->nb_cmd - 1)
	{
		if (is_redi_d_infile(minis->cmd[i - 1].redi))
			wait(NULL);
		last_cmd(minis, envp, i);
	}
	else
	{
		if (is_redi_d_infile(minis->cmd[i - 1].redi))
			wait(NULL);
		middle_cmd(minis, envp, i);
	}
}

int	ft_execute(t_data *minis, char **envp)
{
	int	i;
	int	res;

	init_signals_child();
	i = 0;
	while (i < minis->nb_cmd)
	{
		ft_execute_bis(minis, envp, i);
		i++;
	}
	close_all_pipes(minis);
	wait_all_pid(minis, &res);
	command_error_message(minis, 1);
	if (!minis->cmd[minis->nb_cmd - 1].cmd_path
		&& !ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
		return (127);
	return (res);
}
