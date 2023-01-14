#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*cwd;
	cwd = getcwd(NULL, 0);
	printf("directory:%s\n", cwd);
	free(cwd);
	return (0);
}
