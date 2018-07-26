#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
int	ft_isalpha(int);
int	ft_isdigit(int);
int	ft_isprint(int);
int	ft_isalnum(int);
int	ft_isalnum(int);
int	ft_isascii(int);
int	ft_toupper(int);
int	ft_tolower(int);
int	ft_id(int);
int	ft_puts(const char *s);

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t len);
size_t	ft_strlen(const char *s);

void	test_ft_is(int (*ft_is) (int), int (*is) (int))
{
	for (int i = 0; i < 255; i++)
	{
		//printf("%d\n", i);
		assert(ft_is(i) == is(i));
	}
	/*
	 * assert(ft_is(INT_MIN) == is(INT_MIN));
	 * assert(ft_is(INT_MAX) == is(INT_MAX));
	 * assert(ft_is('a' - 1) == is('a' - 1));
	 * assert(ft_is('a') == is('a'));
	 * assert(ft_is('z') == is('z'));
	 * assert(ft_is('z' + 1) == is('z' + 1));
	 * assert(ft_is('A' - 1) == is('A' - 1));
	 * assert(ft_is('A') == is('A'));
	 * assert(ft_is('Z') == is('Z'));
	 * assert(ft_is('Z' + 1) == is('Z' + 1));
	 * assert(ft_is('0' - 1) == is('0' - 1));
	 * assert(ft_is('0') == is('0'));
	 * assert(ft_is('9') == is('9'));
	 * assert(ft_is('9' + 1) == is('9' + 1));
	 */
}

int main() {
	test_ft_is(ft_isalpha, isalpha);
	test_ft_is(ft_isdigit, isdigit);
	test_ft_is(ft_isalnum, isalnum);
	test_ft_is(ft_isascii, isascii);
	test_ft_is(ft_isprint, isprint);
	test_ft_is(ft_toupper, toupper);
	test_ft_is(ft_tolower, tolower);
	/*
	 * printf("%d\n", ft_isalpha('a' - 1));
	 * printf("%d\n", ft_isalpha('a'));
	 * printf("%d\n", ft_isalpha('z'));
	 * printf("%d\n", ft_isalpha('z' + 1));
	 * printf("is alpha A: %d\n", ft_isalpha('A'));
	 * printf("%d\n", ft_isalpha('Z'));
	 * printf("%d\n", ft_id('0'));
	 * printf("%d\n", ft_id('9'));
	 * printf("%d\n", ft_isdigit('0'));
	 * printf("%d\n", ft_isdigit('9'));
	 * printf("%d\n", ft_isdigit('9' + 1));
	 * printf("%d\n", ft_isalnum('A'));
	 * printf("%d\n", ft_isalnum('8'));
	 * printf("%d\n", ft_isalnum('z' + 1));
	 * 
	 * printf("%d\n", ft_id('A'));
	 * printf("%c\n", ft_toupper('a'));
	 */
	char *abc = strdup("abcdef");
	ft_puts("abcdef");
	printf("%s\n", abc);
	ft_memset(abc, 'z', 5);
	ft_memset(abc, 0, 0);
	assert(abc[0] == 'z');
	printf("%s\n", abc);
	//printf("%d\n", ft_puts("abcdef"));
	ft_bzero(abc, 5);
	assert(memcmp(abc, "\0\0\0\0\0f", 6) == 0);
	printf("%c\n", *abc);
	printf("%p\n", abc);
	assert(memcmp(memset(strdup("abcd"), 'A', 5), ft_memset(strdup("abcd"), 'A', 5), 5) == 0);
	printf("%zu\n", ft_strlen(abc));
	printf("%zu\n", ft_strlen("l"));
	printf("%zu\n", ft_strlen("la"));
	printf("%zu\n", ft_strlen("lal"));
	//char *s1 = strdup("abc");
	//printf("%s\n", ft_strcat(s1, "def"));
}
