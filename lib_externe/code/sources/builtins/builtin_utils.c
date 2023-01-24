/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adevos <adevos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:24:39 by alondot           #+#    #+#             */
/*   Updated: 2023/01/24 21:35:33 by adevos           ###   ########.fr       */
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
	Fonction servant a checker si la commande donnée en parametre est une option -n.
	Si le mot ne commence pas par '-' --> PAS OK (0).
	Si une autre lettre que n apparait suite a un '-' --> PAS OK (0).
	Si uniquement - suivit de plein de n --> OPTION OK (1).
*/
int		check_option_echo(char *cmd)
{
	int i;

	i = 0;
	if(cmd[i] == '-')
	{
		i++;
		while(cmd[i])
		{
			if(cmd[i] != 'n')
				return (0);
			i++;
		}
		return(1);
	}
	return (0);
}

/*
    Cas commande : ECHO.
*/
void	ft_echo(t_data *minis, t_board *cmd)
{
	int	i;
	int	option;

	option = 0;
	if (cmd->nb_words == 2)
	{
		ft_putchar_fd('\n', 1);
		put_res_pipe(minis, 0);
		return ;
	}
	i = 1;
	while(i < cmd->nb_words - 1)
	{
		if(!check_option_echo(cmd->tab[i]))
			break ;
		i++;
	}
	if(i > 1)
		option = 1;
	ft_echo_bis(minis, cmd, i, option);
}

void	ft_echo_bis(t_data *minis, t_board *cmd, int i, int option)
{
	while (i < cmd->nb_words - 1)
	{
		ft_putstr_fd(cmd->tab[i], 1);
		if (i < cmd->nb_words - 2)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', 1);
	put_res_pipe(minis, 0);
}
