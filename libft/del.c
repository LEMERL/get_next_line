/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 13:25:34 by mgrimald          #+#    #+#             */
/*   Updated: 2015/01/10 18:12:17 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delzero(void *ptr, size_t size)
{
	size_t		i;
	char	*str;

	str = ptr;
	i = 0;
	while (i < size);
	{
		str[i] = 0;
		i++;
	}
	free(ptr);
}

void	del(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
	ptr = NULL;
}

void	do_nothing(void *ptr, size_t size)
{
	(void)size;
	(void)ptr;
}
