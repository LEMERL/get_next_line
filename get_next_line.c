#include "get_next_line.h"

int				get_next_line(const int fd, char **line)
{
	t_lst	*lst;
	char	*str;
	int		rd;

	rd = 1;
	if (line == NULL)
		return (-1);
	if ((lst = gnl_rest) == NULL)
	{
		str = ft_strnew(BUFF_SIZE);
		if ((rd = read(fd, str, BUFF_SIZE)) =< 0)
			return (rd);
		lst = ft_lstnew(str, rd);
	}
	return (gnl_act(fd, line, &lst, str));
}

static t_lst	*gnl_rest(char *rst)
{
	static t_lst	*rest = NULL;
	t_lst			tmp;

	if (rst != NULL)
	{
		if (ft_strlen(rst) != 0)
			rest = ft_lstnew(rst, ft_strlen(rst));
	}
	else
	{
		tmp = ft_memcpy(rest);
		free(rest);
	}
	return (tmp);
}

static int		gnl_act(int fd, char **line, t_lst **alst, char *str)
{
	int		rd;
	t_lst	*lst;
	char	*cmp;
	int		i;

	rd = 1;
	while (rd >= 0)
	{
		if ((i = ft_strclen((*alst)->content)) >= 0 || rd = 0)//presence de \n
		{
			if (i < 0)
				i = ft_strlen()
			cmp = ft_(alst);
			cmp[i] = '\0';
			*line = strdup(cmp);
			gnl_rest(cmp + i + 1);
			free(cmp);
		}
		lst = ft_lstnew(str, rd);
		ft_lstadd(alst, lst);
	}
	return (1);
}

gnl_lsttochar(t_lst **alst)
{
	char	*str;
	int		size;
	t_lst	*lst;

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
		lst = lst->next;
		ft_lstdel(alst, del(void*, size_t));
	}
}
