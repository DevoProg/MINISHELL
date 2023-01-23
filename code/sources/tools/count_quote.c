/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:28:36 by alondot           #+#    #+#             */
/*   Updated: 2023/01/21 00:28:38 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction qui compte le nombre de lettre jusqu'au prochain quote
*/
int	count_to_new_quote(char *str, int *i, int quote)
{
	int	count;

	count = 0;
	*i += 1;
	while (str[*i] && str[*i] != quote)
	{
		*i += 1;
		count++;
	}
	return (count);
}

/*
	fonction qui regarde si il n'y a pas de 
	open single quote sur la string a l'index i
*/
int	is_no_open_single_quote(char *line, int i)
{
	int	single_quote;
	int	double_quote;
	int	j;

	j = 0;
	single_quote = 0;
	double_quote = 0;
	while (j < i)
	{
		if (line[j] == 39 && double_quote % 2 == 0)
			single_quote++;
		if (line[j] == 34 && single_quote % 2 == 0)
			double_quote++;
		j++;
	}
	if (single_quote % 2 != 0)
		return (0);
	return (1);
}

/*
	fonction qui y ait pas de single ou double pipe ouvert a l'index i
*/
int	is_no_open_quote(char *line, int i)
{
	int	single_quote;
	int	double_quote;
	int	j;

	j = 0;
	single_quote = 0;
	double_quote = 0;
	while (j < i)
	{
		if (line[j] == 39 && double_quote % 2 == 0)
			single_quote++;
		if (line[j] == 34 && single_quote % 2 == 0)
			double_quote++;
		j++;
	}
	if (single_quote % 2 != 0)
		return (0);
	if (double_quote % 2 != 0)
		return (0);
	return (1);
}
