#include <fcntl.h>
#include "get_next_line.h"

int		get_next_line(int fd, char **line);

char *file = "test1";

int	main(void)
{
	int		i;
	int		fd;
	char	*line = NULL;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	i = -1;
	while (++i < 100)
	{
		if (get_next_line(fd, &line) == -1)
			return (1);
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
}
