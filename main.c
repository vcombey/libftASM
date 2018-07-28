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
size_t ft_strlen(const char *s);

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

int				launch_tests(t_unit_test **testlist)
{
	int				count;
	t_unit_test		*tmp;

	count = 0;
	tmp = *testlist;
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

int	test_strdup()
{
	char *s1 = strdup("abc");
	printf("%s\n", strcat(s1, "defasdffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));
	return (0);
}

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

t_unit_test	*load_strdup()
{
	t_unit_test	*testlist = NULL;

	load_test(&testlist, "strdup", &test_strdup);
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
			printf("ptr: %p\n", tested_str);\
			printf("ft_strlen: %zu, strlen: %zu", ft_strlen(tested_str), strlen(tested_str)); \
			if (ft_strlen(tested_str) != strlen(tested_str))\
				return 1;\
			return 0;\
        }

mt_test_strlen(test_strlen_1, "chat");
mt_test_strlen(test_strlen_2, "");
mt_test_strlen(test_strlen_3, "aaa\0aaa");

#define mt_test_strlen_unalign(test_name, offset) \
        int test_name() \
        {\
			char *abc = strdup("abcdef");\
			char *tested_str = abc + offset;\
			printf("ptr: %p\n", tested_str);\
			printf("ft_strlen: %zu, strlen: %zu", ft_strlen(tested_str), strlen(tested_str)); \
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
			char *abc = strdup("abcdefghijklmnopqrstuvwxyz");\
			char *tested_str = abc + offset;\
			printf("ptr: %p\n", tested_str);\
			printf("ft_strlen: %zu, strlen: %zu", ft_strlen(tested_str), strlen(tested_str)); \
			if (ft_strlen(tested_str) != strlen(tested_str))\
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

int	launch_test_suite(t_unit_test	*(*loader)(void))
{
	t_unit_test	*testlist;
	int			valid_test;
	int			test_len;

	testlist = loader();
	test_len = ft_unit_lst_len(testlist);
	valid_test = launch_tests(&testlist);
	printf("%d / %d tests checked\n\n", valid_test, test_len);
	return (valid_test == test_len);
}

int		main(void)
{
	size_t count;

	count = 0;
	printf("---\n\n************************************\n**        libftASM test        **\n************************************\n");
	//count += launch_test_suite(load_strdup);
	//count += launch_test_suite(load_isalpha);
	//count += launch_test_suite(load_isdigit);
	//count += launch_test_suite(load_isalnum);
	//count += launch_test_suite(load_isascii);
	//count += launch_test_suite(load_isprint);
	//count += launch_test_suite(load_toupper);
	//count += launch_test_suite(load_tolower);
	//count += launch_test_suite(load_memset);
	count += launch_test_suite(load_strlen);
	//test_10_million_chars_string();
	test_strlen_unalign_1();
}
