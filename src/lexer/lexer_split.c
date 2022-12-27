/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:34:37 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/27 11:38:02 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ismeta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\"' || c == '\'' || c == ')' || c == '}')
		return (1);
	return (0);
}

int	ischardigit(char c)
{
	if (ft_isalnum(c) || c == '-')
		return (1);
	return (0);
}

char	*get_word(char *s, int n)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (NULL);
	while (s[i] && i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	count_word_mini(char *s)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			if (ischardigit(s[i + 1]))
				ret++ ;
			else if (ismeta(s[i + 1]))
				ret++ ;
		}
		else if (s[i] == '\"')
		{
			while (s[++i] != '\"')
				;
			ret++;
			i++;
		}
		else if (s[i] == '\'')
		{
			while (s[++i] != '\'')
				;
			i++;
			ret++;
		}
		else if (ismeta(s[i]))
		{
			if (ischardigit(s[i + 1]))
				ret++ ;
			else if (ismeta(s[i + 1]))
			{
				i += 2;
				ret++ ;
			}
			else if (s[i + 1] == '\0')
				ret++;
			else if (s[i + 1] == '$')
				ret++;
		}
		else if (ischardigit(s[i]))
		{
			if (ismeta(s[i + 1]))
				ret++ ;
			else if (s[i + 1] == '\0')
				ret++;
		}
		else if (s[i] == '$')
		{
			i++;
			if (s[i] == '(')
			{
				while (s[++i] != ')')
					;
				ret++;
			}
			else if (s[i] == '{')
			{
				while (s[++i] != '}')
					;
				ret++;
			}
		}
		i++;
	}
	return (ret);
}

int	next_word(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
	{
		i++;
	}
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			if (ischardigit(s[i + 1]))
				return (i + 1);
			else if (ismeta(s[i + 1]))
				return (i + 1);
		}
		else if (s[i] == '\"')
		{
			while (s[++i] != '\"')
				;
			return (i + 1);
		}
		else if (s[i] == '\'')
		{
			while (s[++i] != '\'')
				;
			return (i + 1);
		}
		else if (ismeta(s[i]))
		{
			if (ischardigit(s[i + 1]) || s[i + 1] == '$')
				return (i + 1);
			else if (ft_isspace(s[i + 1]))
				return (i + 1);
		}
		else if (ischardigit(s[i]))
		{
			if (ismeta(s[i + 1]))
				return (i + 1);
		}
		else if (s[i] == '$')
		{
			if (s[i + 1] == '(')
			{
				while (s[++i] != ')')
					;
				return (i + 1);
			}
			else if (s[i + 1] == '{')
			{
				while (s[++i] != '}')
					;
				return (i + 1);
			}
			else if (ischardigit(s[i]))
			{
				while (s[++i] && !ischardigit(s[i]) || !ft_isspace(s[i]))
					;
				return (i);
			}
		}
		i++;
	}
	return (i);
}

char	**lexer_split(char *s)
{
	char	**ret;
	int		len;
	int		i;
	int		word;

	i = 0;
	word = 0;
	len = count_word_mini(s);
	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = get_word(&s[word], next_word(&s[word]));
		word += next_word(&s[word]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	main(void)
{
	char **ret;
	//				1    2 3 4          5        6 7   8  9    10 11 12 13 14  15 16 17 181920  21       22     23 24 25  26      
	char	*s = "touch ABC|echo \" \'hello\' \" > ABC | echo he\'ll\'o >> ABC | cat ABC |ls| echo \" hel|lo \" |$pwd |${pwd}";
	// ret = lexer_split(s);
	// for (int i = 0; ret[i]; i++)
	// 	printf("ret[%d] -> %s\n", i, ret[i]);

	// printf("--------------------------\n\n");
	// free(ret);
	// s = "touch ABC|echo \" \'hello\' \" > ABC | $(hello)";
	// ret = lexer_split(s);
	// for (int i = 0; ret[i]; i++)
	// 	printf("ret[%d] -> %s\n", i, ret[i]);

	// s = "echo \" \'hello\' \" > ABC";
	for (int j =0; s[j]; j++) {
		printf("s[%d] -> %c\n", j, s[j]);
	}
	printf("--------------------------\n\n");
	// free(ret);
	// s = "$pwd";
	// s = "$pwd | $(pwd)| ${pwd}";
	// s = "echo -n -la";
	ret = lexer_split(s);
	for (int i = 0; ret[i]; i++)
		printf("ret[%d] ---- %s ----\n", i, ret[i]);
	// char	*s = "echo hello|touch waord|";
	// char	*s = "echo he\'ll\'o >> ABC";


	// int	i = 0;
	// int	len = 0;
	// while (s[i])
	// {
	// 	sleep(1);
	// 	printf("%s%s%s\n", GRNHB, &s[i], RES);
	// 	// sleep(2);
	// 	i += next_word(&s[i]);
	// 	len++;
	// 	printf("i %d\n", i);
	// }
	// printf("len = %d\n", len);
	// printf("count %d\n", count_word_mini(s3));
	// printf("ret %d\n", count_word_mini(s));
	// printf("ret %d\n", count_word_mini(s2));
	return (0);
}