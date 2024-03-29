/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:38:47 by alondot           #+#    #+#             */
/*   Updated: 2022/06/03 12:09:32 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

char		*get_next_line(int fd);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strdup_gnl(const char *s1);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
char		*ft_strchr_gnl(const char *s, int c);
char		*ft_strnew_gnl(size_t size);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
void		ft_strdel(char **as);

#endif
