/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:34:37 by psuanpro          #+#    #+#             */
/*   Updated: 2023/01/07 21:47:57 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



// int	main(void)
// {
// 	char *s = "$(hello)";
// 	char **ret;

// 	ret = lexer_split(s);

// 	for (int i = 0; ret[i]; i++)
// 		printf("ret[i] -> %s\n", ret[i]);
	
// 	printf("%s--------------------%s\n", "\e[42m", "\e[0m");
// 	s = "$HELLO";
// 	ret = lexer_split(s);

// 	for (int i = 0; ret[i]; i++)
// 		printf("ret[i] -> %s\n", ret[i]);
// 	printf("%s--------------------%s\n", "\e[42m", "\e[0m");
// 	s = "${HELLO}";
// 	ret = lexer_split(s);

// 	for (int i = 0; ret[i]; i++)
// 		printf("ret[i] -> %s\n", ret[i]);
// 	return (0);
// }
// char	*s = "touch ABC|echo \" \'hello\' \" > ABC | echo he\'ll\'o >> ABC | cat ABC |ls| echo \" hel|lo \"";