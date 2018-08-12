/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 13:03:44 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/12 20:53:08 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

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
int	ft_memcmp(const void *a, const void *b, size_t n);
int	ft_strcmp(const char *a, const char *b);
int	ft_strequ(const char *a, const char *b);
void ft_strcld(const char *a);
int	ft_puts(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
char	*ft_strcpy(char *restrict dst, const char *restrict src);
char *ft_strdup(const char *s1);
char *ft_strcat(char *restrict s1, const char *restrict s2);
char *ft_memchr(const void *s1, int c, size_t n);
char *ft_strchr(const char *s1, int c);
size_t ft_strlen(const char *s);
void ft_cat(int fd);

typedef struct			s_unit_test
{
	char				*name;
	int					(*f) (void);
	struct s_unit_test	*next;
}						t_unit_test;


int		ft_unit_lst_len(t_unit_test *lst)
{
	return ((lst == NULL) ? 0 : 1 + ft_unit_lst_len(lst->next));
}

t_unit_test		*unit_test_new(char *name, int (*f)(void))
{
	t_unit_test	*new;

	if (!(new = (t_unit_test*)malloc(sizeof(t_unit_test))))
		return (NULL);
	new->name = name;
	new->f = f;
	return (new);
}

void			load_test(t_unit_test **testlist, char *name, int (*f)(void))
{
	t_unit_test	*new;

	new = unit_test_new(name, f);
	new->next = *testlist;
	*testlist = new;
}

int				print_result(pid_t father)
{
	if (WIFEXITED(father))
	{
		if (father == 0)
		{
			printf("\033[32m[OK]\033[0m\n");
			return (1);
		}
		else if (father == 256)
			printf("\033[31m[KO]\033[0m\n");
	}
	if (WIFSIGNALED(father))
	{
		if (WTERMSIG(father) == SIGALRM)
			printf("\033[31m[TIME]\033[0m\n");
		if (WTERMSIG(father) == SIGSEGV)
			printf("\033[31m[SIGV]\033[0m\n");
		if (WTERMSIG(father) == SIGBUS)
			printf("\033[31m[BUSE]\033[0m\n");
		if (WTERMSIG(father) == SIGABRT)
			printf("\033[31m[SIGA]\033[0m\n");
		if (WTERMSIG(father) == SIGFPE)
			printf("\033[31m[FPTE]\033[0m\n");
	}
	return (0);
}

int				exec_test(int (*f) (void))
{
	pid_t	father;

	father = fork();
	if (father == 0)
	{
		alarm(10);
		if (f() == 0)
			exit(0);
		exit(1);
	}
	if (father > 0)
		wait(&father);
	return (print_result(father));
}

int				launch_tests(t_unit_test **testlist, char *test_name)
{
	int				count;
	t_unit_test		*tmp;

	count = 0;
	tmp = *testlist;
	printf("TEST: %s\n", test_name);
	while (tmp)
	{
		printf("    > %s : ", tmp->name);
		count += exec_test(tmp->f);
		tmp = tmp->next;
	}
	return (count);
}

int	test_ft_is(int (*ft_is) (int), int (*is) (int))
{
	for (int i = 0; i < 255; i++)
	{
		if (!(ft_is(i) == is(i)))
			return (-1);
	}
	return (0);
}

#define mt_test_is(test_name) \
	int test_ ##test_name() { \
		return (test_ft_is(ft_ ##test_name, test_name)); \
	}

mt_test_is(isalpha)
mt_test_is(isalnum)
mt_test_is(isascii)
mt_test_is(isprint)
mt_test_is(toupper)
mt_test_is(isdigit)
mt_test_is(tolower)

t_unit_test	*load_isalpha()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "isalpha", &test_isalpha);
	return (testlist);
}

t_unit_test	*load_isdigit()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "isdigit", &test_isdigit);
	return (testlist);
}
t_unit_test	*load_isalnum()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "isalnum", &test_isalnum);
	return (testlist);
}

t_unit_test	*load_isascii()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "isascii", &test_isascii);
	return (testlist);
}

t_unit_test	*load_isprint()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "isprint", &test_isprint);
	return (testlist);
}

t_unit_test	*load_toupper()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "toupper", &test_toupper);
	return (testlist);
}

t_unit_test	*load_tolower()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "tolower", &test_tolower);
	return (testlist);
}

int		test_memset()
{
	return (memcmp(ft_memset(strdup("abcd"), 'z', 5), memset(strdup("abcd"), 'z', 5), 5));
}

int		test_memset_2()
{
	return (memcmp(ft_memset(strdup("abcd"), 0, 0), memset(strdup("abcd"), 0, 0), 5));
}

int		test_memset_3()
{
		char    b1[100], b2[100];

	ft_memset(b1, 42, 100);
	memset(b2, 42, 100);
	if (memset(b1, 99, 0) != ft_memset(b1, 99, 0))
		return 1;
	if (memcmp(b1, b2, 100) != 0)
		return 1;
	b1[0] = 1;
	ft_memset(b1, 0, 0);
	if (b1[0] != 1)
		return 1;
	return 0;
}

t_unit_test	*load_memset()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "memset_1", &test_memset);
	load_test(&testlist, "memset_2", &test_memset_2);
	load_test(&testlist, "memset_3", &test_memset_3);
	return (testlist);
}

#define mt_test_strlen(test_name, tested_str) \
        int test_name() \
        {\
			if (ft_strlen(tested_str) != strlen(tested_str))\
				return 1;\
			return 0;\
        }

mt_test_strlen(test_strlen_1, "chat");
mt_test_strlen(test_strlen_2, "");
mt_test_strlen(test_strlen_3, "aaa\0aaa");

			/*
			 * printf("ptr: %p\n", tested_str);\
			 * printf("ft_strlen: %zu, strlen: %zu", ft_strlen(tested_str), strlen(tested_str)); \
			 */
#define mt_test_strlen_unalign(test_name, offset) \
        int test_name() \
        {\
			char *abc = strdup("abcdef");\
			char *tested_str = abc + offset;\
			if (ft_strlen(tested_str) != strlen(tested_str))\
				return 1;\
			return 0;\
        }
mt_test_strlen_unalign(test_strlen_unalign_1, 1);
mt_test_strlen_unalign(test_strlen_unalign_2, 2);
mt_test_strlen_unalign(test_strlen_unalign_3, 3);
mt_test_strlen_unalign(test_strlen_unalign_4, 4);
mt_test_strlen_unalign(test_strlen_unalign_5, 5);
mt_test_strlen_unalign(test_strlen_unalign_6, 6);

#define mt_test_strlen_unalign_long(test_name, offset) \
        int test_name() \
        {\
			char *abc = strdup("\x1\x1\x1\x1\x1\x1\x1\x1\x1");\
			char *tested_str = abc + offset;\
			size_t len = ft_strlen(tested_str);\
			if (len != strlen(tested_str))\
				return 1;\
			return 0;\
        }
mt_test_strlen_unalign_long(test_strlen_unalign_long_1, 1);
mt_test_strlen_unalign_long(test_strlen_unalign_long_2, 2);
mt_test_strlen_unalign_long(test_strlen_unalign_long_3, 3);
mt_test_strlen_unalign_long(test_strlen_unalign_long_4, 4);
mt_test_strlen_unalign_long(test_strlen_unalign_long_5, 5);
mt_test_strlen_unalign_long(test_strlen_unalign_long_6, 6);

static int test_10_million_chars_string()
{
        int test_len = 10 * 10;
        char str[test_len];
		size_t len;

        memset(str, 'a', test_len);
        str[test_len - 1] = '\0';
		if ((len = ft_strlen(str)) != strlen(str))
		{
			printf("ft_strlen: %zu, strlen: %zu", len, strlen(str));
			return 1;
		}
		return 0;
}

static int test_memcpy()
{
	char	b1[100], b2[100];

	memset(b1, 33, 100);
	memset(b2, 63, 100);

	ft_memcpy(b1, b2, 100);
	if (!(memcmp(b1, b2, 100) == 0))
		return 1;
	if (!(ft_memcpy(b1, b2, 0) == b1))
		return 1;
	return 0;
}

t_unit_test	*load_memcpy()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "test_memcpy", &test_memcpy);
	return (testlist);
}

t_unit_test	*load_strlen()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "test_10_million_chars_string", &test_10_million_chars_string);
	load_test(&testlist, "test_1", test_strlen_1);
	load_test(&testlist, "test_2", &test_strlen_2);
	load_test(&testlist, "test_3", &test_strlen_3);
	load_test(&testlist, "test_strlen_unalign_1", &test_strlen_unalign_1);
	load_test(&testlist, "test_strlen_unalign_2", &test_strlen_unalign_2);
	load_test(&testlist, "test_strlen_unalign_3", &test_strlen_unalign_3);
	load_test(&testlist, "test_strlen_unalign_4", &test_strlen_unalign_4);
	load_test(&testlist, "test_strlen_unalign_5", &test_strlen_unalign_5);
	load_test(&testlist, "test_strlen_unalign_6", &test_strlen_unalign_6);
	load_test(&testlist, "test_strlen_unalign_long_1", &test_strlen_unalign_long_1);
	load_test(&testlist, "test_strlen_unalign_long_2", &test_strlen_unalign_long_2);
	load_test(&testlist, "test_strlen_unalign_long_3", &test_strlen_unalign_long_3);
	load_test(&testlist, "test_strlen_unalign_long_4", &test_strlen_unalign_long_4);
	load_test(&testlist, "test_strlen_unalign_long_5", &test_strlen_unalign_long_5);
	load_test(&testlist, "test_strlen_unalign_long_6", &test_strlen_unalign_long_6);
	return (testlist);
}

static int test_strcat()
{
	char	buf[9] = "";

//	printf("str: |%s|, ptr: %p\n", buf, buf);
	bzero(buf, 9);
	//ft_strcat(buf, "");
//	printf("str: |%s|\n", buf);
	ft_strcat(buf, "Bon");
//	printf("str: |%s|\n", buf);
	ft_strcat(buf, "j");
//	printf("str: |%s|\n", buf);
	ft_strcat(buf, "our.");
//	printf("str: |%s|\n", buf);
	ft_strcat(buf, "");
	printf("str: |%s|\n", buf);
	if (strcmp(buf, "Bonjour.") != 0)
		return 1;
	if (buf != ft_strcat(buf, ""))
		return 1;
	return 0;
}

t_unit_test	*load_strcat()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "test_strcat", &test_strcat);
	return (testlist);
}

static int test_strdup_1()
{
	if(strcmp(ft_strdup("aaaaa"), "aaaaa") != 0)
		return 1;
	return 0;
}

static int test_strdup_2()
{
	if(strcmp(ft_strdup(""), "") != 0)
		return 1;
	return 0;
}

static int test_strdup_3()
{
	char *s1;
	char *s2;

	s1 = "aaa";
	s2 = ft_strdup(s1);
	if(s1 == s2)
		return 1;
	return 0;
}
t_unit_test	*load_strdup()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "strdup_1", &test_strdup_1);
	load_test(&testlist, "strdup_2", &test_strdup_2);
	load_test(&testlist, "strdup_3", &test_strdup_3);
	return (testlist);
}

#define mt_test_memchr(test_name, tested_str, c, n)	\
        int test_name() \
        {\
			if (ft_memchr(tested_str, c, n) != memchr(tested_str, c, n))	\
				return 1;\
			return 0;\
        }

mt_test_memchr(test_memchr_1, "abcd", 'a', 1);
mt_test_memchr(test_memchr_2, "abcd", 'a', 0);
mt_test_memchr(test_memchr_3, "abcd", 'e', 5);
mt_test_memchr(test_memchr_4, "abcd", 'd', 4);

t_unit_test	*load_memchr()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "first_char", &test_memchr_1);
	load_test(&testlist, "n_zero", &test_memchr_2);
	load_test(&testlist, "not_found", &test_memchr_3);
	load_test(&testlist, "last_char", &test_memchr_4);
	return (testlist);
}


#define mt_test_strchr(test_name, tested_str, c)	\
        int test_name() \
        {\
			if (ft_strchr(tested_str, c) != strchr(tested_str, c))	\
				return 1;\
			return 0;\
        }

mt_test_strchr(test_strchr_1, "abcd", 'a');
mt_test_strchr(test_strchr_2, "abcd", 'a');
mt_test_strchr(test_strchr_3, "abcd", 'e');
mt_test_strchr(test_strchr_4, "abcd", 'd');

t_unit_test	*load_strchr()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "first_char", &test_strchr_1);
	load_test(&testlist, "n_zero", &test_strchr_2);
	load_test(&testlist, "not_found", &test_strchr_3);
	load_test(&testlist, "last_char", &test_strchr_4);
	return (testlist);
}
static int test_only_bzero_first_x_chars()
{
	char	control[] = "123456789";
	char	subject[] = "123456789";

	bzero(control, 3);
	ft_bzero(subject, 3);
	return memcmp(subject, control, 10);
}

static int test_zero_case()
{
	char	control[] = "123456789";
	char	subject[] = "123456789";

	bzero(control, 0);
	ft_bzero(subject, 0);
	return memcmp(subject, control, 10);
}


static int simple_string()
{
	char	control[10];
	char	subject[] = "123456789";

	bzero(control, 10);
	ft_bzero(subject, 10);
	if (memcmp(control, subject, 10) != 0)
		return 1;
	subject[0] = 'a';
	ft_bzero(subject, 0);
	return (subject[0] != 'a');
}

t_unit_test	*load_bzero()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "test_only_bzero_first_x_chars", &test_only_bzero_first_x_chars);
	load_test(&testlist, "test_zero_case", &test_zero_case);
	load_test(&testlist, "simple_string", &simple_string);
	return (testlist);
}

#define mt_test_memcmp(test_name, a, b, c)		\
        int test_name() \
        {\
			if (ft_memcmp(a, b, c) != memcmp(a, b, c))	\
				return 1;\
			return 0;\
        }

mt_test_memcmp(test_memcmp_1, "chat", "dsads", 0);
mt_test_memcmp(test_memcmp_2, "\x1", "\0", 1);
mt_test_memcmp(test_memcmp_3, "12345a", "12345b", 6);
mt_test_memcmp(test_memcmp_4, "12345a", "12345b", 5);
mt_test_memcmp(test_memcmp_5, "12a456", "12b456", 5);

int test_memcmp_6() 
{
	unsigned char s1[2] = "\0";
	unsigned char s2[2] = "\0";
	s1[0] = 200;
	if (ft_memcmp(s1, s2, 1) != memcmp(s1, s2,1))	
		return 1;
	return 0;
}

t_unit_test	*load_memcmp()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "cmp_0_char", &test_memcmp_1);
	load_test(&testlist, "cmp_unsigned", &test_memcmp_2);
	load_test(&testlist, "simple_string", &test_memcmp_3);
	load_test(&testlist, "simple_string_equal", &test_memcmp_4);
	load_test(&testlist, "simple_non_equal", &test_memcmp_5);
	load_test(&testlist, "unsigned_char", &test_memcmp_6);
	return (testlist);
}

#define mt_test_strcmp(test_name, a, b)			\
	int test_name()								\
	{											\
		if (ft_strcmp(a, b) != strcmp(a, b))	\
			return 1;							\
		return 0;								\
	}

mt_test_strcmp(test_strcmp_2, "\x1", "\0");
mt_test_strcmp(test_strcmp_3, "123456", "123456");
mt_test_strcmp(test_strcmp_4, "12345a", "12345b");
mt_test_strcmp(test_strcmp_5, "12a456", "12b456");

t_unit_test	*load_strcmp()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "cmp_unsigned", &test_strcmp_2);
	load_test(&testlist, "simple_string", &test_strcmp_3);
	load_test(&testlist, "simple_string_equal", &test_strcmp_4);
	load_test(&testlist, "simple_non_equal", &test_strcmp_5);
	return (testlist);
}

#define mt_test_strequ(test_name, a, b)			\
	int test_name()								\
	{											\
		if (strcmp(a, b) != 0 && ft_strequ(a, b) == 1)	\
			return (1); \
		if (strcmp(a, b) == 0 && ft_strequ(a, b) != 1)	\
			return (1); \
		return 0;								\
	}

mt_test_strequ(test_strequ_2, "\x1", "\0");
mt_test_strequ(test_strequ_3, "123456", "123456");
mt_test_strequ(test_strequ_4, "12345a", "12345b");
mt_test_strequ(test_strequ_5, "12a456", "12b456");

t_unit_test	*load_strequ()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "cmp_unsigned", &test_strequ_2);
	load_test(&testlist, "simple_string", &test_strequ_3);
	load_test(&testlist, "simple_string_equal", &test_strequ_4);
	load_test(&testlist, "simple_non_equal", &test_strequ_5);
	return (testlist);
}

int test_strcld()								
{											
	char *s1 = "\0\0\0\0\0\0";
	char s2[6] = "123456";
	ft_strcld(s2);
	if (memcmp(s1, s2, 6) != 0)
		return (1); 
	return 0;								
}

t_unit_test	*load_strcld()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "simple_test", &test_strcld);
	return (testlist);
}

static int test_strcpy()
{
	char	b1[100], b2[100];

	memset(b1, 33, 99);
	memset(b2, 63, 99);
	b1[99] = 0;
	b2[99] = 0;
	ft_strcpy(b1, b2);
	if (!(memcmp(b1, b2, 100) == 0))
		return 1;
	if (!(ft_strcpy(b1, b2) == b1))
		return 1;
	return 0;
}

t_unit_test	*load_strcpy()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "test_strcpy", &test_strcpy);
	return (testlist);
}

int	launch_test_suite(t_unit_test	*(*loader)(void), char *test_name)
{
	t_unit_test	*testlist;
	int			valid_test;
	int			test_len;

	testlist = loader();
	test_len = ft_unit_lst_len(testlist);
	valid_test = launch_tests(&testlist, test_name);
	printf("%d / %d tests checked\n-----------------------\n\n", valid_test, test_len);
	return (valid_test == test_len);
}

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	size_t count;

	count = 0;
	printf("---\n\n************************************\n**        libftASM test        **\n************************************\n");
	count += launch_test_suite(load_bzero,    "bzero");
	count += launch_test_suite(load_isalpha,  "isalpha");
	count += launch_test_suite(load_isdigit,  "isdigit");
	count += launch_test_suite(load_isalnum,  "isalnum");
	count += launch_test_suite(load_isascii,  "isascii");
	count += launch_test_suite(load_isprint,  "isprint");
	count += launch_test_suite(load_toupper,  "toupper");
	count += launch_test_suite(load_tolower,  "tolower");
	count += launch_test_suite(load_memset,   "memset");
	count += launch_test_suite(load_strlen,   "strlen");
	count += launch_test_suite(load_memcpy,   "memcpy");
	count += launch_test_suite(load_strcat,   "strcat");
	count += launch_test_suite(load_strdup,   "strdup");
	count += launch_test_suite(load_memchr,    "memchr");
	count += launch_test_suite(load_memcmp,    "memcmp");
	count += launch_test_suite(load_strcmp,    "strcmp");
	count += launch_test_suite(load_strchr,    "strchr");
	count += launch_test_suite(load_strequ,    "strequ");
	count += launch_test_suite(load_strcld,    "strcld");
	count += launch_test_suite(load_strcpy,    "strcpy");
	//	test_memcmp_6();
	//test_strequ_3();
	if (ac == 2) {
		ft_cat(0);
		ft_cat(open(__FILE__, O_RDONLY));
		ft_cat(open(av[0], O_RDONLY));
		ft_cat(-42);
		ft_puts("bonjour bonjour");
		ft_puts("");
	}
	return 0;
}
