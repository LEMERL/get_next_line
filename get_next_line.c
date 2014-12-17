/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 12:43:49 by mgrimald          #+#    #+#             */
/*   Updated: 2014/12/17 14:37:25 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_lstdellone_db(t_lst_db **alst)
{
	t_lst_db		*temp;

	temp = NULL;
	if (alst && *alst)
	{
		if ((*alst)->prev)
		{
			(*alst)->prev->next = (*alst)->next;
			temp = (*alst)->prev;
		}
		if ((*alst)->next)
		{
			(*alst)->next->prev = (*alst)->prev;
			temp = (*alst)->next;
		}
		(*alst)->content_size = 0;
		free(*alst);
		*alst = temp;
	}
}

static t_lst_db	*gnl_recup_rest(int fd, t_lst_db **rest)
{
	t_lst_db		*tmp;
	t_lst_db		*ptr;

	ptr = *rest;
	while (rest && *rest && (*rest)->prev)
		(*rest) = (*rest)->prev;
	while (rest && *rest)
	{
		if ((*rest)->content_size == (unsigned int)fd)
		{
			tmp = (*rest)->content;
			ft_lstdellone_db(rest);
			return (tmp);
		}
		(*rest) = (*rest)->next;
	}
	*rest = ptr;
	return (NULL);
}

static int		gnl_rest(int fd, t_lst_db **lst, char *rst)
{
	static t_lst_db	*rest = NULL;
	t_lst_db		*temp;
	t_lst_db		*ini;
	char			*tmp;
	int				rd;

	rd = 0;
	if (rest == NULL)
		rest = ft_lstnew_db(NULL, 0);
	if (rst != NULL && (temp = ft_lstnew_db(NULL, 0)))
	{
		ini = ft_lstnew_db(rst, ft_strlen(rst));
		temp->content = ini;
		temp->content_size = fd;
		ft_lstadd_db(&rest, temp);
		return (1);
	}
	if (!(temp = gnl_recup_rest(fd, &rest)) && (tmp = ft_strnew(BUFF_SIZE)))
	{
		if ((rd = read(fd, tmp, BUFF_SIZE)) < 0)
			return (-1);
		temp = ft_lstnew_db(tmp, rd);
		ft_strdel(&tmp);
	}
	ft_lstadd_db(lst, temp);
	return (1);
}

static int		gnl_act(char **line, char *str, int fd)
{
	int				i;
	char			*rtn;

	i = ft_strclen(str, '\n');
	if (i < 0)
		i = ft_strlen(str);
	str[i] = '\0';
	if ((rtn = ft_strdup(str)) == NULL)
		return (-1);
	*line = rtn;
	gnl_rest(fd, NULL, str + i + 1);
	ft_strdel(&str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*str;
	int				rd;
	t_lst_db		**lst;
	t_lst_db		*ini;
	char			*tmp;

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
			return (gnl_act(line, tmp, fd));
		}
		if ((rd = read(fd, str, BUFF_SIZE)) < 0)
			return (-1);
		ft_lstadd_db(lst, ft_lstnew_db(str, ft_strlen(str)));
	}
	return (0);
}
