# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psrikamo <psrikamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 16:17:38 by psuanpro          #+#    #+#              #
#    Updated: 2023/02/08 02:16:52 by psrikamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	RDLIB			=
	RDIN			=
else ifeq ($(UNAME),Darwin)
	RDLIB			=	-L/usr/local/opt/readline/lib
	RDIN			=	-I/usr/local/opt/readline/include
endif

SRC = main.c \
	$(LEXER) \
	$(PARSER) \
	$(BUILDIN) \
	$(EXECUTE) \
	$(EXPANDER)

LEXER = src/lexer/lexer.c

PARSER = src/parser/parser.c

EXPANDER = src/expander/expander.c \
			src/expander/expander_utils0.c \
			src/expander/expander_utils1.c \
			src/expander/expander_utils2.c \
			src/expander/expander_utils3.c \
			src/expander/expander_utils4.c \

BUILDIN = src/buildin/ft_echo.c \
			src/buildin/ft_env.c \
			src/buildin/ft_env_utils.c \
			src/buildin/ft_export.c \
			src/buildin/ft_unset.c \
			src/buildin/ft_cd.c \
			src/buildin/ft_cd_utils.c \
			src/buildin/ft_exit.c \
			src/buildin/ft_exit_utils.c \
			src/buildin/ft_pwd.c

EXECUTE = src/execute/execute.c

LIBFT = ./libft/libft.a
LIBFTDIR = libft
RDFLAG = -lreadline

OBJS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

BRED =\033[1;31m
BGRN =\033[1;32m
BYEL =\033[1;33m
RES = \033[0m

COMPILE = echo "$(BGRN)Minishell compiled....$(RES)"
CLEAN = echo "$(BYEL)Minishell clean....$(RES)"
FCLEAN = echo "$(BRED)Minishell fclean....$(RES)"

.c.o:
	@$(CC) -g $(CLAFGS) $(RDIN) -c $< -o $@

all:$(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	@$(CC) -g $(CFLAGS) $(RDLIB) $(OBJS) $(LIBFT) -o $@ $(RDFLAG)
	@$(COMPILE)

v:all
	@./minishell

clean:
	@make -C $(LIBFTDIR) clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C $(LIBFTDIR) fclean
	@rm -rf $(NAME)
	@$(FCLEAN)

re: fclean all

.PHONY: all clean fclean re
