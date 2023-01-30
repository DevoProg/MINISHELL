/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:08:24 by alondot           #+#    #+#             */
/*   Updated: 2023/01/25 21:19:06 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pipe_at_end(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
	{
		ft_printf("Error parsing : unexpected token `|'\n");
		code_erreur = 258;
		return (1);
	}
	if (str[i] == '|')
	{
		ft_printf("Error parsing : unexpected token `|'\n");
		code_erreur = 258;
		return (1);
	}
	if (!str[i])
	{
		ft_printf("Error parsing : unexpected token `|'\n");
		code_erreur = 258;
		return (1);
	}
	return(0);
}

int unknow_env_redi(t_data *minis, char *str, int i)
{
	char *var_env;
	char *res_env;
	
	if(str[i] == '$')
	{
		var_env = search_env_var(str, i, minis);
		res_env = list_chr(minis->env, var_env);
		free(var_env);
		if(!res_env || res_env[0] == '\0')
			return (1);
	}
	return(0);
}

int nothing_after_redi(t_data *minis, char *str, int i)
{
	char *new_str;

	new_str = ft_strdup(str);
	if(!new_str)
		ft_error("Malloc", minis, 2, 1);
	new_str = get_new_str(new_str);
	if(!new_str)
		ft_error("Malloc", minis, 2, 1);
	while (new_str[i] && new_str[i] == ' ')
		i++;
	if (new_str[i] == '<' || new_str[i] == '>')
	{
		ft_printf("Error parsing\n");
		code_erreur = 258;
		free(new_str);
		return (1);
	}
	if (new_str[i] == '|')
	{
		ft_printf("Error parsing : unexpected token `|'\n");
		code_erreur = 258;
		free(new_str);
		return (1);
	}
	if(unknow_env_redi(minis, str, i))
	{
		ft_printf("ambiguous redirect\n");
		code_erreur = 1;
		free(new_str);
		return (1);
	}
	if (!new_str[i])
	{
		ft_printf("Error parsing\n");
		code_erreur = 258;
		free(new_str);
		return (1);
	}
	free(new_str);
	return (0);
}

int	parse(t_data *minis, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && is_no_open_quote(str, i))
		{
			if(pipe_at_end(str, i + 1))
				return(0);
		}
		else if (str[i] == '>' && is_no_open_quote(str, i))
		{
			if(str[i + 1] == '>')
				i++;
			if (nothing_after_redi(minis, str, i + 1))
				return (0);
		}
		else if (str[i] == '<' && is_no_open_quote(str, i))
		{
			if (str[i + 1] == '<')
				i++;
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				ft_printf("Error parsing\n");
				code_erreur = 258;
				return (0);
			}
			while (str[i] && str[i] == ' ')
				i++;
			i++;
			if (!str[i])
			{
				ft_printf("Error parsing\n");
				code_erreur = 258;
				return (0);
			}
		}
		i++;
	}
	return (1);
}
