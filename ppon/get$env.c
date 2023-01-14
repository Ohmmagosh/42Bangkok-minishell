#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_list
{
	int				ind;
	void			*content;
	struct s_list	*next;
}	t_list;



t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (ptr != NULL)
	{
		ptr->content = content;
		ptr->next = (t_list *) NULL;
		return (ptr);
	}
	else
		return ((t_list *) NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *newnode)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = newnode;
	}
	else
		*lst = newnode;
}

void	ft_lstclr(t_list **lst)
{
	t_list	*tmplst0;
	t_list	*tmplst1;

	tmplst0 = *lst;
	while (tmplst0 != NULL)
	{
		free(tmplst0->content);
		tmplst1 = tmplst0->next;
		free(tmplst0);
		tmplst0 = tmplst1;
	}
	*lst = NULL;
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str != NULL)
	{
		while (*str != '\0')
		{
			i++;
			str++;
		}
	}
	return (i);
}

// need to free src aft used
// return addr if sucess
// return NULL if fail
char	*ft_strdup(char *src)
{
	size_t	i;
	char	*dst;
	char	*tmpdst;

	i = ft_strlen(src);
	dst = malloc((sizeof(char) * i) + 1);
	tmpdst = dst;
	if  (dst != NULL)
	{
		while (*src != '\0')
		{
			*dst = *src;
			src++;
			dst++;
		}
		*dst = '\0';
	}
	return (tmpdst);
}

// return
// bit 0 = execute
// bit 1 = write
// bit 2 = read
// bit 3 = file exist
char	ft_chk_perm(char *path)
{
	char	permission;

	permission = 0;
	if (access(path, F_OK) == 0)
		permission = (permission | (1 << 3));
	if (access(path, R_OK) == 0)
		permission = (permission | (1 << 2));
	if (access(path, W_OK) == 0)
		permission = (permission | (1 << 1));
	if (access(path, X_OK) == 0)
		permission = (permission | 1);
	// printf("permission:%d\n", (int)permission);
	return (permission);
}

void	ft_cpyenv(t_list **envlst, char **envp)
{
	char	*temenv;
	t_list	*tmplstenv;
	t_list	*lstenv;

	lstenv = NULL;
	while (*envp != NULL)
	{
		temenv = ft_strdup(*envp);
		if (temenv == NULL)
		{
			printf("cannot cpy %s\n", *envp);
			break;
		}
		tmplstenv = ft_lstnew(temenv);
		if (tmplstenv == NULL)
		{
			printf("cannot create node\n");
			break;
		}
		ft_lstadd_back(&lstenv,tmplstenv);
		envp++;
	}
	*envlst = lstenv;
}

// chk for $(name)
// env need to be in form $(env_name)
// return "node" if env exist
// return "NULL" if env don't exist
t_list	*ft_findnodeenv(t_list **lstenv, char *env)
{
	char	*envname;
	char	*tmpenv;
	t_list	*tlstenv;

	printf("search env:%s\n", env);
	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		envname = &env[1];
		tmpenv = (char *)tlstenv->content;
		while (*envname != '\0')
		{
			if (*envname != *tmpenv)
				break;
			envname++;
			tmpenv++;
		}
		if ((*envname == '\0') && (*tmpenv == '='))
			return (tlstenv);
		tlstenv = tlstenv->next;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**tmpenvp;
	t_list	*ownenv;

	// tmpenvp = envp;
	// while (*tmpenvp != NULL)
	// {
	// 	printf("%s\n", *tmpenvp);
	// 	tmpenvp++;
	// }

	// start copy own env
	printf("\nstart store own env\n");
	ft_cpyenv(&ownenv, envp);
	printf("show cpy env\n");
	t_list	*tmpenv = ownenv;
	while (tmpenv != NULL)
	{
		printf("env:%s\n", (char *)tmpenv->content);
		tmpenv = tmpenv->next;
	}
	printf("end show cpy env\n");

	printf("get env:");
	char	c[100];
	scanf("%s", &c[0]);
	char	*p;
	int		i = 0;
	p = &c[0];
	printf("env = %s\n", c);
	// while (p[i] != '\0')
	// {
	// 	printf("%c\n", p[i]);
	// 	i++;
	// }
	t_list	*nodeenv = ft_findnodeenv(&ownenv, &c[0]);
	if (nodeenv == NULL)
		printf("Not found node env\n");
	else
		printf("content in node %s\n", (char *)nodeenv->content);

	return (0);

	// int	fd[2];

	// if (pipe(fd) == -1)
	// {
	// 	printf("An error occured with opening the pipe\n");
	// 	return (1);
	// }
	// int	id = fork();
	// if (id == 0)
	// {
	// 	close(fd[0]);
	// 	int	x;
	// 	printf("input a number: ");
	// 	scanf("%d", &x);
	// 	write(fd[1], &x, sizeof(int));
	// 	close(fd[1]);
	// }
	// else {
	// 	close(fd[1]);
	// 	int	y;
	// 	y = 0;
	// 	printf("y bef:%d\n", y);
	// 	read(fd[0], &y, sizeof(int));
	// 	close(fd[0]);
	// 	printf("got from child process:%d\n", y);
	// }
	// return (0);
}
