#include <fcntl.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"
#include <stdlib.h>

int		main()
{
	char	*s;
	char	*t;
	char	*str;
	int		i;
	int		j;
	int		k;
	int		file = open("text.txt", O_RDONLY);
	int		file_2 = open("text_2.txt", O_RDONLY);
	int		file_3 = open("text_3.txt", O_RDONLY);
	i = 42;
	j = 42;
	k = 42;

	while (i > 0 || j > 0 || k > 0)
	{
		str = NULL;
		k = get_next_line(file_3, &str);
		if (k > 0)
		{
			ft_putendl(str);
			free(str);
		}
		t = NULL;
		j = get_next_line(file_2, &t);
		if (j > 0)
		{
			ft_putendl(t);
			free(t);
		}
		s = NULL;
		i = get_next_line(file, &s);
		if (i > 0)
		{
			ft_putendl(s);
			free(s);
		}
	}
	close(file);
	close(file_2);
	close(file_3);
	return (i);
}
