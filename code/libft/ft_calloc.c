/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:34:17 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 12:35:50 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*dst;
	unsigned int	nb;
	unsigned int	i;

	nb = count * size;
	dst = malloc(nb);
	if (!dst)
		return (NULL);
	i = 0;
	while (nb--)
	{
		dst[i] = 0;
		i++;
	}
	return ((void *)dst);
}
