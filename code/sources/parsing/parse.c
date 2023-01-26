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

int	parse(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && is_no_open_quote(str, i))
		{
			if (!str[i + 1])
			{
				ft_printf("Error parsing : unexpected token `|'\n");
				code_erreur = 258;
				return (0);
			}
			if (str[i + 1] == '|')
			{
				ft_printf("Error parsing : unexpected token `|'\n");
				code_erreur = 258;
				return (0);
			}
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i])
			{
				ft_printf("Error parsing : unexpected token `|'\n");
				code_erreur = 258;
				return (0);
			}
		}
		else if (str[i] == '>' && is_no_open_quote(str, i))
		{
			if (str[i + 1] == '>')
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
