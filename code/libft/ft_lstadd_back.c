/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohimon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:23:26 by gmohimon          #+#    #+#             */
/*   Updated: 2022/01/26 12:24:16 by gmohimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *newLst)
{
	t_list	*last_elem;

	if (!*alst)
	{
		*alst = newLst;
		return ;
	}
	last_elem = ft_lstlast(*alst);
	last_elem->next = newLst;
}
