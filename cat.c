# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <fcntl.h>

void ft_cat(int fd);

int		main(int ac, char **av)
{
	if (ac == 2) {
		int fd = open(av[1], O_RDONLY);
		ft_cat(fd);
	}
	else
		ft_cat(0);
	return 0;
}