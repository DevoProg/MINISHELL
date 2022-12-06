/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:35:19 by alondot           #+#    #+#             */
/*   Updated: 2022/02/07 16:22:44 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (s == NULL)
		return (NULL);
	subs = ft_strnew(len);
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}

static char	*cut_function(char **str)
{
	int		len;
	char	*tmp;
	char	*line;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
			len++;
	if ((*str)[len] == '\n')
	{
		line = ft_strsub(*str, 0, len + 1);
		tmp = ft_strdup(&((*str)[len + 1]));
		free(*str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (line);
}

static char	*output(char **str, int ret)
{
	if (ret < 0)
		return (NULL);
	else if (ret == 0 && *str == NULL)
		return (0);
	else
		return (cut_function(&(*str)));
}

char	*get_next_line(int fd)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	static char	*str;
	char		*tmp;

	while (1)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buff[ret] = '\0';
		if (str == NULL)
			str = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
		}
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (output(&str, ret));
}
