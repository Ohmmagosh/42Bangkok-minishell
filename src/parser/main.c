#include <stdio.h>
int	main(void)
{
	// char	*s = "hello";
	// char	*v = s;
	char	**s ;
	s[0] = "hello";
	s[1] = "world";
	s[2] = NULL;
	for (int i = 0; s[i]; i++) {
		printf("s[i] -> %s\n", s[i]);
	}	// printf("s -> %s\n", s);
	// printf("v -> %s\n", v);
	return (0);
}