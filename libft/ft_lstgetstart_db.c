/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetstart_db.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 21:02:12 by mgrimald          #+#    #+#             */
/*   Updated: 2015/01/06 16:10:56 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst_db	*ft_lstgetstart_db(t_lst_db **lst)
{
	if (lst && *lst)
		while ((*lst)->prev)
			*lst = (*lst)->prev;
	return (*lst);
}
