#include <fcntl.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"
#include <stdlib.h>

int		main()
{
	char	*str;
	int		i;
	int		file = open("text.txt", O_RDONLY);
	i = 42;

	while (i > 0)
	{
		str = NULL;
		i = get_next_line(file, &str);
		if (i > 0)
		{
			ft_putendl(str);
			free(str);
		}
		else
			ft_putnbr(i);
	}
	close(file);
	return (i);
}
