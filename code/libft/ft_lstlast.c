/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:16:20 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 12:17:10 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cp;

	if (!lst)
		return (0);
	cp = lst;
	while (cp->next)
		cp = cp->next;
	return (cp);
}
