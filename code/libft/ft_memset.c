/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:54:57 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 11:56:22 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*st;

	st = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		st[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
