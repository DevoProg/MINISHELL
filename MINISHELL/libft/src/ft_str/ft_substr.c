/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:25:50 by alondot           #+#    #+#             */
/*   Updated: 2022/02/23 17:28:54 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_size(char const *s, unsigned int start, size_t len)
{
	if (len >= ft_strlen(s) - start)
		return (ft_strlen(s) - start);
	else if (start >= ft_strlen(s))
		return (0);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (malloc_size(s, start, len) + 1));
	if (!str)
		return (0);
	if ((size_t)start >= ft_strlen(s))
	{
		str[0] = '\0';
		return (str);
	}
	i = 0;
	while (i < len && i <= ft_strlen(s) - start)
	{
		str[i] = *(s + start + i);
		i++;
	}
	str[i] = '\0';
	return (str);
}
