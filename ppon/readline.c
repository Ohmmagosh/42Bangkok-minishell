#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include <readline/readline.h>
#include <readline/history.h>

// int	main(int argc, char argv[])
int	main(void)
{
	char	*cmd = readline("minishell> ");
	printf("%s", cmd);
	free(cmd);
	return (0);
}
