# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 16:17:38 by psuanpro          #+#    #+#              #
#    Updated: 2022/12/16 19:33:16 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c \
	$(LEXER) \
	$(PARSER) \
	$(BUILDIN) \
	$(EXECUTE)

LEXER = src/lexer/lexer.c \
		src/lexer/lexer_split.c \
		src/lexer/lexer_split_utils.c \

PARSER = src/parser/parser.c

BUILDIN = src/buildin/ft_echo.c

EXECUTE = src/execute/execute.c

LIBFT = ./libft/libft.a
LIBFTDIR = libft
RDLIB = -L/usr/local/opt/readline/lib/
RDIN = -I/usr/local/opt/readline/include/
RDFLAG = -lreadline

OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

BRED =\033[1;31m
BGRN =\033[1;32m
BYEL =\033[1;33m
RES = \033[0m

COMPILE = echo "$(BGRN)Minishell compiled....$(RES)"
CLEAN = echo "$(BYEL)Minishell clean....$(RES)"
FCLEAN = echo "$(BRED)Minishell fclean....$(RES)"

.c.o:
	@$(CC) $(CLAFGS) $(RDIN) -c $< -o $@

all:$(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(RDFLAG) $(RDLIB) $(OBJS) $(LIBFT) -o $@
	@$(COMPILE)


clean:
	@make -C $(LIBFTDIR) clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C $(LIBFTDIR) fclean
	@rm -rf $(NAME)
	@$(FCLEAN)

re: fclean all

.PHONY: all clean fclean re
