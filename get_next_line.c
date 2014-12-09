/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 12:43:49 by mgrimald          #+#    #+#             */
/*   Updated: 2014/12/09 13:46:55 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_act(char **line, char *str);
int		gnl_rest(int fd, t_lst_db **lst, char *rst);

int		get_next_line(const int fd, char **line)
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
		if (ft_strclen((*lst)->content, '\n') >= 0)
		{
			tmp = ft_lsttochar_db(lst);
			ft_lstdelall_db(lst);
			return (gnl_act(line, tmp));
		}
		if ((rd = read(fd, str, BUFF_SIZE)) < 0)
			return (-1);
		ft_lstadd_db(lst, ft_lstnew_db(str, ft_strlen(str)));
	}
	if (rd == 0 && str && ft_strlen(str) != 0)
		return (gnl_act(line, str));
	return (0);
}

int		gnl_rest(int fd, t_lst_db **lst, char *rst)
{
	static t_lst_db		*rest = NULL;
	char				*tmp;
	int					rd;

	rd = 0;
	if (rst != NULL)
	{
		rest = ft_lstnew_db(rst, ft_strlen(rst));
		return (1);
	}
	else
	{
		if (rest == NULL || rest->content == NULL || rest->content_size == 0)
		{
			tmp = ft_strnew(BUFF_SIZE);
			if ((rd = read(fd, tmp, BUFF_SIZE)) < 0)
				return (-1);
			rest = ft_lstnew_db(tmp, rd);
		}
		ft_lstadd_db(lst, rest);
		return (1);
	}
}

int		gnl_act(char **line, char *str)
{
	int			i;
	char		*rtn;

	i = ft_strclen(str, '\n');
	str[i + 1] = '\0';
	if (i < 0)
		i = ft_strlen(str);
	if ((rtn = ft_strdup(str)) == NULL)
		return (-1);
	*line = rtn;
	gnl_rest(0, NULL, str + i + 1);
	ft_strdel(&str);
	return (1);
}