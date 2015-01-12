#include "get_next_line.h"

static t_list	*gnl_rest(char *rst)
{
	static t_list	*rest = NULL;
	t_list			*tmp;

	if (rst != NULL)
	{
		if (ft_strlen(rst) != 0)
			rest = ft_lstnew(rst, ft_strlen(rst));
		else
			rest = NULL;
	}
	else if (rest)
	{
		tmp = ft_memdup(rest, sizeof(t_list));
		free(rest);
		rest = NULL;
	}
	else
		tmp = NULL;
	return (tmp);
}

static char		*gnl_lsttochar(t_list **alst)
{
	char	*str;
	int		size;
	t_list	*lst;

	size = 0;
	lst = *alst;
	while (lst)
	{
		size = size + lst->content_size;
		lst = lst->next;
	}
	lst = *alst;
	str = ft_strnew(size);
	while (lst)
	{
		size = size - lst->content_size;
		ft_memcpy(str + size, lst->content, lst->content_size);
		ft_lstdelone(&lst, del);
	}
	return (str);
}

static int		gnl_act(int fd, char **line, t_list **alst, char *str)
{
	int		rd;
	int		i;

	rd = 1;
	str = ft_strnew(BUFF_SIZE);
	while (rd >= 0)
	{
		if ((i = ft_strclen((*alst)->content, '\n')) >= 0 || rd == 0)
		{
			if (i >= 0)
			{
				gnl_rest((*alst)->content + i + 1);
				((char*)(*alst)->content)[i] = '\0';
				(*alst)->content_size = i;
			}
			*line = gnl_lsttochar(alst);
			free(str);
			return (1);
		}
		if ((rd = read(fd, str, BUFF_SIZE)) < 0)
			return (rd);
		ft_lstadd(alst, ft_lstnew(str, rd));
	}
	return (-1);
}

int				get_next_line(const int fd, char **line)
{
	t_list	*lst;
	char	*str;
	int		rd;

	rd = 1;
	if (line == NULL)
		return (-1);
	if ((lst = gnl_rest(NULL)) == NULL)
	{
	str = ft_strnew(BUFF_SIZE);
		if ((rd = read(fd, str, BUFF_SIZE)) <= 0)
			return (rd);
		lst = ft_lstnew(str, rd);
			free(str);
	}
	return (gnl_act(fd, line, &lst, str));
}
