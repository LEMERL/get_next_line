/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:41:30 by mgrimald          #+#    #+#             */
/*   Updated: 2014/11/15 18:12:55 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	char	*ptr;

	ptr = s1;
	while (*ptr != '\0' && ptr != NULL)
		ptr++;
	while (*s2 != '\0' && n && s2 != NULL && ptr != NULL)
	{
		*ptr = *s2;
		ptr++;
		s2++;
		n--;
	}
	*ptr = '\0';
	return (s1);
}
