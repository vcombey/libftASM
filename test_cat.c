#include <stdio.h>
#include <unistd.h>

int main()
{
	int c;
	int ret;
	while ((ret = read(STDIN_FILENO, &c, 1024)) > 0)
	{
		printf("char: '%c'\n%d\n", c, ret);
	}
	printf("%d", ret);
}
