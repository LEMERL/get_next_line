/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_db.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 19:38:55 by mgrimald          #+#    #+#             */
/*   Updated: 2014/12/17 13:59:04 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_db(t_lst_db **alstdb, t_lst_db *nw)
{
	if (alstdb && *alstdb && nw)
	{
		nw->prev = (*alstdb)->prev;
		nw->next = *alstdb;
		if ((*alstdb)->prev)
			(*alstdb)->prev->next = nw;
		(*alstdb)->prev = nw;
		*alstdb = nw;
	}
}
