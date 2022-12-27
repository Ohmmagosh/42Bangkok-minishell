/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:34:37 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/27 10:16:11 by psuanpro         ###   ########.fr       */
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
		else if (s[i] == 34)
		{
			while (s[++i] != 34)
				;
			ret++;
			i++;
		}
		else if (s[i] == 39)
		{
			while (s[++i] != 39)
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
			else if (ft_isspace(s[i + 1]))
				ret++ ;
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
			else if (ischardigit(s[i]))
			{
				while (!ft_isspace(s[i]) && !ismeta(s[i]))
					i++;
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
	// printf("s -> %s\n", s);
	while (ft_isspace(s[i]))
	{
		// printf("s[i] -> %c\n", s[i]);
		i++;
	}
	// printf("s -> %s\n", s);
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			// printf("%shello%s\n", "\e[42m", "\e[0m");
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
	printf("len %d\n", len);
	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = get_word(&s[word], next_word(&s[word]));
		printf("word -> %d\n", word);
		word += next_word(&s[word]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	main(void)
{
	char **ret;
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

	printf("--------------------------\n\n");
	// free(ret);
	// s = "$pwd";
	s = "$pwd | $(pwd)| ${pwd}";
	// s = "echo -n -la";
	ret = lexer_split(s);
	for (int i = 0; ret[i]; i++)
		printf("ret[%d] ->|%s|\n", i, ret[i]);
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