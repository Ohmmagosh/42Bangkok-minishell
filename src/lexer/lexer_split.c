/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:34:37 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/20 00:49:09 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

int	ismeta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == 34 || c == 39 || c == 36)
		return (1);
	return (0);
}

int	ischardigit(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// int	len_word(char *s)
// {
// 	int	ret;

// 	ret = 0;
// 	while (s[ret])
// 	{
// 		if (s[])
// 		ret++;
// 	}
// 	return (ret);
// }

// char	*get_word(char *s, int n)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = (char *)malloc(sizeof(char) * (n + 1));
// 	if (!ret)
// 		return (NULL);
// 	while (s[i] && i < n)
// 	{
// 		ret[i] = s[i];
// 		i++;
// 	}
// 	ret[i] = '\0';
// 	return (ret);
// }

int	count_word_mini(char *s)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s[i])
	{
		printf("%s%s%s\n", YELHB, &s[i], RES);
		if (ft_isspace(s[i]))
		{
			if (ischardigit(s[i + 1]) || ismeta(s[i + 1]))
			{
				ret++;
				printf("%s c -> %c ret -> %d%s\n",GRNHB, s[i], ret, RES);
			}
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] != 39)
				i++;
			ret++;
			printf("%s c -> %c ret -> %d%s\n", GRNHB, s[i], ret, RES);
		}
		else if (s[i] == 34)
		{
			i++;
			while (s[i] != 34)
				i++;
			ret++;
			printf("%s c -> %c ret -> %d%s\n", GRNHB, s[i], ret, RES);
		}
		else if (s[i] == 40)
		{
			i++;
			while (s[i] != 41)
				i++;
			ret++;
			printf("%s c -> %c ret -> %d%s\n", GRNHB, s[i], ret, RES);
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
		i++;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			if (ischardigit(s[i + 1]))
				return (i + 1);
			else if (ismeta(s[i + 1]))
				return (i + 1);
		}
		else if (s[i] == 34)
		{
			i++;
			while (s[i] != 34)
				i++;
			return (i + 1);
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] != 39)
				i++;
			return (i + 1);
		}
		else if (ismeta(s[i]))
		{
			if (ischardigit(s[i + 1]))
				return (i + 1);
			else if (ft_isspace(s[i + 1]))
				return (i + 1);
		}
		else if (ischardigit(s[i]))
		{
			if (ismeta(s[i + 1]))
				return (i + 1);
		}
		i++;
	}
	return (i);
}

// char	**lexer_split(char *s)
// {
// 	char	**ret;
// 	int		len;
// 	int		i;
// 	int		word;

// 	i = 0;
// 	word = 0;
// 	len = count_word_mini(s);
// 	if (!s)
// 		return (NULL);
// 	ret = (char **)malloc(sizeof(char *) * (len + 1));
// 	if (!ret)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		ret[i] = get_word(&s[word], next_word(&s[word]));
// 		word += next_word(&s[word]);
// 		i++;
// 	}
// 	ret[i] = NULL;
// 	return (ret);
// }

int	main(void)
{
	char	*s = "touch ABC|echo \" \'hello\' \" > ABC | exho he\'ll\'o >> ABC | cat ABC |ls| echo \" hel|lo \"";
	// char	*s2 = "echo $()";

	int	i = 0;
	while (s[i])
	{
		printf("%s%s%s\n", GRNHB, &s[i], RES);
		sleep(2);
		i += next_word(&s[i]);
		printf("i %d\n", i);
	}
	// printf("ret %d\n", count_word_mini(s));
	// printf("ret %d\n", count_word_mini(s2));
	return (0);
}