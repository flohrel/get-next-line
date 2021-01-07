#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int		get_next_line(int fd, char **line);

char *file[6] = { "get_next_line.c", "get_next_line_utils.c", "get_next_line.h", };

int	main(void)
{
	int		i;
	int		j;
	int		ret;
	int		fd[6];
	char	*line = NULL;

	i = -1;
	while (++i < 6)
	{
		if ((fd[i] = open(file[i], O_RDONLY)) == -1)
			return (1);
	}
	j = -1;
	while (++j < 10)
	{
		i = -1;
		while (++i < 6)
		{
			if ((ret = get_next_line(fd[i], &line)) == -1)
				return (1);
			printf("%s\n", line);
		}
	}
	free(line);
}
