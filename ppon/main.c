#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

// #include <readline/readline.h>
// #include <readline/history.h>

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;

	if (dest == NULL && src == NULL)
		return (dest);
	tmp_d = (unsigned char *)dest;
	tmp_s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		tmp_d[i] = tmp_s[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*join;

	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	join = malloc(s1len + s2len + 1);
	if (join != NULL)
	{
		ft_memcpy(join, s1, s1len);
		ft_memcpy(join + s1len, s2, s2len);
		join[s1len + s2len] = 0;
	}
	return (join);
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
// when send env in form $(env_name)
// user need to cut $ by themself
// env need to be in form (env_name)
// in order to use this function
// return "node" if env exist
// return "NULL" if env don't exist
t_list	*ft_findnodeenv(t_list **lstenv, char *env)
{
	char	*envname;
	char	*tmpenv;
	t_list	*tlstenv;

	// printf("search env:%s\n", env);
	tlstenv = *lstenv;
	while (tlstenv != NULL)
	{
		envname = &env[0];
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

// arg need to "(envname)=(value)"
void	ft_export(t_list **lstenv, char *arg)
{
	t_list	*tlstenv;
	char	*envend;
	char	*envst;
	char	*envname;
	char	*tmpenvname;

	printf("arg:%s\n", arg);
	envend = arg;
	while (*envend != '=')
		envend++;
	envname = malloc((envend - arg) + 1);
	tmpenvname = envname;
	envst = arg;
	while (envst != envend)
	{
		*tmpenvname = *envst;
		tmpenvname++;
		envst++;
	}
	*tmpenvname = '\0';
	printf("arg cut:%s\n", envname);

	tlstenv = ft_findnodeenv(lstenv, envname);
	if (tlstenv == NULL)
		ft_lstadd_back(lstenv, ft_lstnew(ft_strdup(arg)));
	else
	{
		printf("show env:%s\n", (char *)tlstenv->content);
		free(tlstenv->content);
		tlstenv->content = ft_strdup(arg);
	}

	free(envname);
}

// arg must be (envname)
void	ft_unset(t_list **lstenv, char *arg)
{
	t_list	*tlstenv;
	t_list	*unsetenv;

	printf("arg:%s\n", arg);
	tlstenv = *lstenv;
	if (tlstenv != NULL)
	{
		unsetenv = ft_findnodeenv(lstenv, arg);
		printf("content node:%s\n", (char *)unsetenv->content);
		if (unsetenv != NULL)
		{
			if (unsetenv == tlstenv)
			{
				*lstenv = unsetenv->next;
				free(unsetenv->content);
				// unsetenv->next = NULL;
				free(unsetenv);
			}
			else
			{
				while (tlstenv->next != unsetenv)
					tlstenv = tlstenv->next;
				printf("contest pre:%s\n", (char *)tlstenv->content);
				printf("contest node unset:%s\n", (char *)tlstenv->next->content);
				tlstenv->next = tlstenv->next->next;
				printf("address %p\n", tlstenv->next);
				printf("content in unset:%s\n", (char *)unsetenv->content);
				free(unsetenv->content);
				// unsetenv->next = NULL;
				free(unsetenv);
			}
		}
	}
}

// arg must be $(envname)
void	ft_echo(t_list **lstenv, char *arg, char *opt)
{
	t_list	*tlstenv;
	size_t	siz_arg;
	char	*env;

	if (arg != NULL)
	{
		siz_arg = ft_strlen(arg);
		if (arg[0] == '$' && siz_arg > 1)
		{
			tlstenv = ft_findnodeenv(lstenv, &arg[1]);
			if (tlstenv != NULL)
			{
				env = (char *)tlstenv->content;
				while (*env != '=')
					env++;
				env++;
				while (*env != '\0')
				{
					// printf("%s", env);
					write(1, env, 1);
					env++;
				}
			}
		}
		else
		{
			// printf("%s", arg);
			while (*arg != '\0')
			{
				write(1, arg, 1);
				arg++;
			}
		}
		if (opt == NULL)
			write(1, "\n", 1);
	}
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("directory:%s\n", cwd);
	free(cwd);
}

void	ft_uppwdenv(t_list **lstenv, char *path)
{
	t_list	*tlstenv;
	char	*tpath;
	char	*tpwd;
	char	*tmp;

	printf("update $PWD\n");
	tlstenv = ft_findnodeenv(lstenv, "PWD");
	tpath = ft_strdup(path);
	tpwd = ft_strdup(tlstenv->content);
	free(tlstenv->content);
	tmp = tpwd;
	while (*tmp != '=')
		tmp++;
	*(++tmp) = '\0';
	printf("tpwd:%s\n", tpwd);
	tmp = ft_strjoin(tpwd, tpath);
	free(tpath);
	free(tpwd);
	tlstenv->content = tmp;
	printf("env:%s\n", (char *)tlstenv->content);
}

// arg is path(full path or relative path)
void	ft_cd(t_list **lstenv, char *arg)
{
	char	*tch0;

	// printf("arg:%s\n", arg);

	int	res;
	res = chdir(arg);
	printf("res chdir:%d\n", res);
	// printf("pwd:%s\n", getcwd(NULL, 0));
	if (res != 0)
		printf("Cannot access file or directory\n");
	else
	{
		tch0 = getcwd(NULL, 0);
		ft_uppwdenv(lstenv, tch0);
		free(tch0);
	}

	// // full path
	// // if (ft_chk_perm(arg) != 0)
	// int	res_per = ft_chk_perm(arg);
	// printf("permission of arg:%d\n", res_per);
	// if (res != 0)
	// {
	// 	printf("full path\n");
	// 	chdir(arg);
	// 	ft_uppwdenv(lstenv, arg);
	// }
	// // relative path
	// else
	// {
	// 	printf("relative path\n");
	// 	tch0 = getcwd(NULL, 0);
	// 	printf("tpwd:%s\n", tch0);
	// 	tch1 = ft_strjoin(tch0, "/");
	// 	printf("aft join:%s\n", tch1);
	// 	free(tch0);
	// 	tch0 = ft_strjoin(tch1, arg);
	// 	free(tch1);
	// 	printf("full path:%s\n", tch0);
	// 	printf("permission full path:%d\n", ft_chk_perm(tch0));
	// 	// chdir
	// }
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

	// test pwd
	printf("test pwd\n");
	ft_pwd();

	// test cd
	printf("test cd\n");
	char	a[100];
	printf("input path:");
	scanf("%s", &a[0]);
	fflush(stdin);
	ft_cd(&ownenv, &a[0]);

	// test search env
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
	t_list	*nodeenv = ft_findnodeenv(&ownenv, &c[1]);
	if (nodeenv == NULL)
		printf("Not found node env\n");
	else
		printf("content in node %s\n", (char *)nodeenv->content);

	// test export env
	printf("export env:");
	char	d[100];
	scanf("%s", &d[0]);
	ft_export(&ownenv, &d[0]);

	printf("show export env\n");
	tmpenv = ownenv;
	while (tmpenv != NULL)
	{
		printf("env:%s\n", (char *)tmpenv->content);
		tmpenv = tmpenv->next;
	}
	printf("end show export env\n");

	// test unset env
	printf("test unset\n");
	printf("unset env:");
	char	e[100];
	scanf("%s", &e[0]);
	ft_unset(&ownenv, &e[0]);
	printf("show unset env\n");
	tmpenv = ownenv;
	while (tmpenv != NULL)
	{
		printf("env:%s\n", (char *)tmpenv->content);
		tmpenv = tmpenv->next;
	}
	printf("end show unset env\n");

	// test echo
	printf("echo:");
	char	f[100];
	scanf("%s", &f[0]);
	ft_echo(&ownenv, &f[0], NULL);

	ft_lstclr(&ownenv);

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
