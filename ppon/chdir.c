// #include <asm-generic/errno-base.h>
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

int	main(void)
{
	char	*cwd;
	char	*nwd;
	char	*tmp_nwd;
	char	*st;
	char	*end;
	int		siz_nwd;

	// get working diretory
	cwd = getcwd(NULL, 0);
	// show working directory
	printf("cwd:%s\n", cwd);

	st = cwd;
	end = st;
	siz_nwd = 0;
	while (*end != '\0')
	{
		// get last sub folder
		if (*end == '/')
			st = end;
		siz_nwd++;
		end++;
	}
	end = st;
	st = cwd;
	// copy new folder
	nwd = malloc(sizeof(char) * siz_nwd);
	if (nwd == NULL)
		printf("found err when cpy path for new working directory\n");
	tmp_nwd = nwd;
	while (st != end)
	{
		*tmp_nwd = *st;
		st++;
		tmp_nwd++;
	}
	*tmp_nwd = 0;

	// // test failed condition
	// tmp_nwd--;
	// *tmp_nwd = 0;

	//show new folder
	printf("new wd:%s\n", nwd);

	//test permission
	if (access(nwd, F_OK | W_OK |R_OK | X_OK) == 0)
		printf("be able to access wd:%s\n", nwd);
	else
		printf("cann't access path %s\n", nwd);

	if (chdir(nwd) == -1)
	{
		free(cwd);
		free(nwd);
		printf("fail to change diretory path\n");
		return (1);
	}
	free(cwd);
	free(nwd);

	cwd = getcwd(NULL, 0);
	printf("Now working directory:%s\n", cwd);
	free(cwd);

	return (0);
}
