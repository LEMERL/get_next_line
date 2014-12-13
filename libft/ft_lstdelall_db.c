/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelall_db.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 15:56:44 by mgrimald          #+#    #+#             */
/*   Updated: 2014/12/13 15:57:03 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdelall_db(t_lst_db **lst)
{
	while (lst && (*lst) && (*lst)->prev != NULL)
	{
		(*lst)->prev->next = *lst;
		*lst = (*lst)->prev;
	}
	while (lst && (*lst) && (*lst)->next != NULL)
	{
		if ((*lst)->content != NULL)
		{
			ft_memdel(&((*lst)->content));
			(*lst)->content_size = 0;
		}
		*lst = (*lst)->next;
		ft_memdel((void**)&(*lst)->prev);
	}
	if (lst)
		ft_memdel((void**)lst);
}
