/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:02:09 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 12:03:26 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;

	if (n == 0)
		return (0);
	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	while ((*s1cpy == *s2cpy) && n - 1 > 0)
	{
		s1cpy++;
		s2cpy++;
		n--;
	}
	return (*s1cpy - *s2cpy);
}
