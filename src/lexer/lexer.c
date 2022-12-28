/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:13 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/28 09:09:23 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer(t_pro *p)
{
	p->lex.trim = ft_strtrim(p->lex.cmd, " ");
	free(p->lex.cmd);
	p->lex.split = lexer_split(p->lex.trim);
	free(p->lex.trim);
}
