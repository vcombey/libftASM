#include <stdio.h>
int main() {
	printf("%d\n", ft_isalpha('a' - 1));
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha('z'));
	printf("%d\n", ft_isalpha('z' + 1));
	printf("%d\n", ft_isalpha('A'));
	printf("%d\n", ft_isalpha('Z'));
}
