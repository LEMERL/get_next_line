/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 12:43:49 by mgrimald          #+#    #+#             */
/*   Updated: 2014/12/13 16:21:04 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		gnl_rest(int fd, t_lst_db **lst, char *rst)
{
	static t_lst_db		*rest = NULL;
	char				*tmp;
	int					rd;

	rd = 0;
	if (rst != NULL)
	{
		if (ft_strlen(rst) > 0)
			rest = ft_lstnew_db(rst, ft_strlen(rst));
		else
			rest = NULL;
		return (1);
	}
	if (rest == NULL)
	{
		tmp = ft_strnew(BUFF_SIZE);
		if ((rd = read(fd, tmp, BUFF_SIZE)) < 0)
			return (-1);
		rest = ft_lstnew_db(tmp, rd);
		ft_strdel(&tmp);
	}
	ft_lstadd_db(lst, rest);
	return (1);
}

static int		gnl_act(char **line, char *str)
{
	int			i;
	char		*rtn;

	i = ft_strclen(str, '\n');
	if (i < 0)
		i = ft_strlen(str);
	str[i] = '\0';
	if ((rtn = ft_strdup(str)) == NULL)
		return (-1);
	*line = rtn;
	gnl_rest(0, NULL, str + i + 1);
	ft_strdel(&str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		*str;
	int			rd;
	t_lst_db	**lst;
	t_lst_db	*ini;
	char		*tmp;

	ini = ft_lstnew_db(NULL, 0);
	lst = &ini;
	rd = gnl_rest(fd, lst, NULL);
	if ((str = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	while (rd > 0)
	{
		if ((ft_strclen((*lst)->content, '\n') >= 0) || (rd == 0 && str))
		{
			tmp = ft_lsttochar_db(lst);
			ft_lstdelall_db(lst);
			ft_strdel(&str);
			return (gnl_act(line, tmp));
		}
		if ((rd = read(fd, str, BUFF_SIZE)) < 0)
			return (-1);
		ft_lstadd_db(lst, ft_lstnew_db(str, ft_strlen(str)));
	}
	return (0);
}
