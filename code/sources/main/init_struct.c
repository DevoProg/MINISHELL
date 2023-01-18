/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:28:43 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 00:30:35 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redi(t_data *minis)
{
	int		i;
	t_redi	*current;
    t_redi	*next;

	i = 0;
    while (i < minis->nb_cmd) {
        current = minis->cmd[i].redi;
        if (!current)
            return ;
        while (current->next) {
			next = current->next;
            free(current->file);
            free(current);
            current = next;
        }
        free(current->file);
        free(current);
		i++;
	}
}

void	free_struct(t_data *minis)
{
	free_struct_cmd(minis);
	free(minis->line);
	free_redi(minis);
}

/*
	Fonction servant a init la structure "minis".
*/
void	init_struct(t_data *minis)
{
	int	i;

	minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);
	if (!minis->cmd)
		ft_error("Malloc", minis, 1, 1);
	i = 0;
	while (i < minis->nb_cmd)
	{
		minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
		if (!minis->cmd[i].line_cmd)
			ft_error("Malloc", minis, 2, 1);
		minis->cmd[i].cmd_path = NULL;
		i++;
	}
	free_tab(minis->tab_cmd, minis->nb_cmd + 1);
}
