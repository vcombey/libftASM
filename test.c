#include <stdio.h>
int main() {
	printf("%d\n", ft_isalpha('a' - 1));
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha('z'));
	printf("%d\n", ft_isalpha('z' + 1));
	printf("is alpha A: %d\n", ft_isalpha('A'));
	printf("%d\n", ft_isalpha('Z'));
	printf("%d\n", ft_id('0'));
	printf("%d\n", ft_id('9'));
	printf("%d\n", ft_isdigit('0'));
	printf("%d\n", ft_isdigit('9'));
	printf("%d\n", ft_isdigit('9' + 1));
	printf("%d\n", ft_isalnum('A'));
	printf("%d\n", ft_isalnum('8'));
	printf("%d\n", ft_isalnum('z' + 1));

	printf("%d\n", ft_id('A'));
	printf("%d\n", ft_id('Z'));
}
