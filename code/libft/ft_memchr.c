/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:03:40 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 12:04:28 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cpy;
	unsigned int	i;

	cpy = (unsigned char *)s;
	i = 0;
	while (i < n && cpy[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)&cpy[i]);
}
