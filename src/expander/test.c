// #define _POSIX_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <curses.h>



// int	main() {
	// char const *ret, tty[40];

	// if ((ret = ttyname(STDIN_FILENO)) == NULL)
	// 	perror("ttyname() error");
	// else {
	// 	// strcpy(tty, ret);
	// 	printf("The ttyname associated with my stdin is %s\n", ret);
	// }
	// char cwd[256];

	// if (chdir("/Users") != 0)
	// 	perror("chdir() error()");
	// else
	// {
	// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
	// 		perror("getcwd() error");
	// 	else
	// 		printf("current working directory is: %s\n", cwd);
	// }
// 	char *termtype = getenv ("TERM");
// 	int success;

// 	if (termtype == 0)
// 		fatal ("Specify a terminal type with `setenv TERM <yourtype>'.\n");

// 	success = tgetent (term_buffer, termtype);
// 	if (success < 0)
// 		fatal ("Could not access the termcap data base.\n");
// 	if (success == 0)
// 		fatal ("Terminal type `%s' is not defined.\n", termtype);
// }
// #ifdef unix
// static char term_buffer[2048];
// #else
// #define term_buffer 0
// #endif

// init_terminal_data ()
// {
//   char *termtype = getenv ("TERM");
//   int success;

//   if (termtype == 0)
//     fatal ("Specify a terminal type with `setenv TERM <yourtype>'.\n");

//   success = tgetent (term_buffer, termtype);
//   if (success < 0)
//     fatal ("Could not access the termcap data base.\n");
//   if (success == 0)
//     fatal ("Terminal type `%s' is not defined.\n", termtype);
// }

#include<stdio.h>
#include<unistd.h>
int main()
{
	char cwd[256];

	if (chdir("./") != 0)
	perror("chdir() error()");
	else {
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("curren dir %s\n", cwd);
	}  
}
