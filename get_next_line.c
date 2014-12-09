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

void	ft2_lstdel_db(t_lst_db **lst)
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
char	*ft_lsttochar(t_lst_db **lst)
{
	char	*str;
	int		size;

	size = 0;
	while ((*lst) && (*lst)->next != NULL)
	{
		size = size + (*lst)->content_size;
		(*lst)->next->prev = *lst;
		*lst = (*lst)->next;
	}
	if ((*lst)->content == NULL || (*lst)->content_size == 0)
		*lst = (*lst)->prev;
	str = ft_strnew(size);
	while (str && (*lst) && (*lst)->content)
	{
		ft_strncat(str, (*lst)->content, (*lst)->content_size);
		*lst = (*lst)->prev;
	}
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	char		*str;
	int			rd;
	t_lst_db	*lst;
	char		*tmp;

	lst = NULL;
	rd = gnl_rest(fd, &lst, NULL);
	if ((str = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	while (rd > 0)
	{
		if (ft_strclen(lst->content, '\n') >= 0)
		{
			tmp = ft_lsttochar(&lst);
			ft2_lstdel_db(&lst);
			return (gnl_act(line, tmp));
		}
		if ((rd = read(fd, str, BUFF_SIZE)) < 0)
			return (-1);
		ft_lstadd_db(&lst, ft_lstnew_db(str, ft_strlen(str)));
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
		if (!ft_strlen(rst))
			rest = NULL;
		else
			rest = ft_lstnew_db(rst, ft_strlen(rst));
		return (1);
	}
	else
	{
		if (rest == NULL)
		{
			tmp = ft_strnew(BUFF_SIZE);
			if ((rd = read(fd, tmp, BUFF_SIZE)) < 0)
				return (-1);
			rest = ft_lstnew_db(tmp, rd);
		}
		ft_lstadd_db(lst, rest);
		return (0);
	}
}

int		gnl_act(char **line, char *str)
{
	int			i;
	char		*rtn;

	i = ft_strclen(str, '\n');
	if (i < 0)
		i = ft_strlen(str);
	if ((rtn = ft_strdup(str)) == NULL)
		return (-1);
	*line = rtn;
	rtn[i] = '\0';
	gnl_rest(0, NULL, str + i + 1);
	ft_strdel(&str);
	return (1);
}
