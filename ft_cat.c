#include <fcntl.h>
void	ft_cat(int fd);
int main(int ac, char **av) {

	ft_cat(0);
	ft_cat(open(__FILE__, O_RDONLY));
	ft_cat(-42);
	(void)ac;
	return 0;

}