
#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	plus_i2(int *i)
{
	(*i)++;
	printf("i2 = %d\n", (*i));
}

void	plus_i(int *i)
{
	(*i)++;
	printf("i1 = %d\n", (*i));
	plus_i2(i);
}

int	main(void)
{
	int	i = 0;

	while (i < 100)
	{
		plus_i(&i);
	}
}
