/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:27:24 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/19 00:15:54 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	chk_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		
	}
	return (i);
}

char	*expander(char *s)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = NULL;
	i = 0;
	tmp = ft_calloc(1, 1);
	while (s[i])
	{
		if (s[i] == '\"')
		{

		}
		else if (s[i] == '\'')
		{
		}
		else if (ft_isalnum(s[i]))
		{
		}
		i++;
	}
	return (ret);
}

int	main(void)
{
	char	*ret[] = {"\"hello\"", "\"he'll'o\"", "\"e\"\"c\"\"h\"\"o\"", "he'll'o", NULL };

	for (int i = 0;ret[i];i++)
	{
		ret[i] = expander(ret[i]);
	}

}

// "\"e\"\"c\"\"h\"\"o\""