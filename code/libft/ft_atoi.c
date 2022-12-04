/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:48:39 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 13:08:12 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					signe;
	unsigned long long	nb;
	int					i;

	nb = 0;
	signe = 1;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			signe = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i++] - '0';
	}
	if (nb > LLONG_MAX && signe == 1)
		return (-1);
	if (nb - 1 > LLONG_MAX && signe == -1)
		return (0);
	return (nb * signe);
}
