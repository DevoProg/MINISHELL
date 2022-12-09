/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:19:59 by alondot           #+#    #+#             */
/*   Updated: 2022/01/12 11:21:57 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newElem)
{
	t_list	*aux_lst;

	if (newElem)
	{
		if (!*lst)
		{
			*lst = newElem;
			return ;
		}
		aux_lst = ft_lstlast(*lst);
		aux_lst->next = newElem;
	}
}
