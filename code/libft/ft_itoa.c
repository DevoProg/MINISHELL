/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:24:29 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 12:28:09 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_nb_digit(long nb_long, int signe)
{
	unsigned int	nb_digit;

	if (nb_long == 0)
		return (1);
	nb_digit = 0;
	while (nb_long > 0)
	{
		nb_long /= 10;
		nb_digit++;
	}
	if (signe == -1)
		nb_digit++;
	return (nb_digit);
}

static void	convert_nb(char *nb, long nb_long, unsigned int nb_digit, int sign)
{
	nb[nb_digit] = '\0';
	nb[--nb_digit] = nb_long % 10 + '0';
	nb_long /= 10;
	while (nb_long > 0)
	{
		nb[--nb_digit] = nb_long % 10 + '0';
		nb_long /= 10;
	}
	if (sign == -1)
		nb[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*nb;
	long			nb_long;
	unsigned int	nb_digit;
	int				signe;

	signe = 1;
	if (n < 0)
	{
		nb_long = (long)n * -1;
		signe = -1;
	}
	else
		nb_long = n;
	nb_digit = get_nb_digit(nb_long, signe);
	nb = malloc(sizeof(char) * nb_digit + 1);
	if (!nb)
		return (NULL);
	convert_nb(nb, nb_long, nb_digit, signe);
	return (nb);
}
