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
size_t	ft_strlen(const char *s);

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

int	test_ft_is_alpha()
{
	return (test_ft_is(ft_isalpha, isalpha));
}

t_unit_test	*load_ft_is_alpha_test()
{
	t_unit_test	*testlist;

	testlist = NULL;
	printf("is_alpha:\n");
	load_test(&testlist, "test_all_char", &test_ft_is_alpha);
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
	count += launch_test_suite(load_ft_is_alpha_test);
	printf("%zu / 1 suite tests passed\n", count);

}
