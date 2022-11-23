/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:45:40 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 10:51:11 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newdest;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	newdest = malloc((i + 1) * sizeof(char));
	if (!newdest || !f)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newdest[i] = f(i, s[i]);
		i++;
	}
	newdest[i] = '\0';
	return (newdest);
}
