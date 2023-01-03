# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 16:17:38 by psuanpro          #+#    #+#              #
#    Updated: 2023/01/03 15:10:29 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

UNAME = $(shell uname -s)
ARCH = $(shell arch)

ifeq ($(UNAME), Darwin)
	ifeq ($(ARCH), arm64)
		RDLIB			=	-L${HOMEBREW_PREFIX}/opt/readline/lib
		RDIN			=	-I${HOMEBREW_PREFIX}/opt/readline/include
	else ifeq ($(ARCH), i386)
		RDLIB			=	-L/usr/local/opt/readline/lib
		RDIN			=	-I/usr/local/opt/readline/include
	endif
endif

SRC = main.c \
	$(LEXER) \
	$(PARSER) \
	$(BUILDIN) \
	$(EXECUTE) \
	$(EXPANDER)

LEXER = src/lexer/lexer.c \
		src/lexer/lexer_split.c \
		src/lexer/lexer_split_utils.c \

PARSER = src/parser/parser.c

EXPANDER = src/expander/expander.c

BUILDIN = src/buildin/ft_echo.c

EXECUTE = src/execute/execute.c

LIBFT = ./libft/libft.a
LIBFTDIR = libft
# RDLIB = -L/usr/local/opt/readline/lib/
# RDIN = -I/usr/local/opt/readline/include/
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
