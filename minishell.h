/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:17:43 by psuanpro          #+#    #+#             */
/*   Updated: 2022/12/08 23:30:43 by psuanpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "src/lexer/lexer.h"
# include "src/parser/parser.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
// # include <readline/replaceline.h>

typedef struct s_program
{
	char	*hello;
}				t_pro;

#endif