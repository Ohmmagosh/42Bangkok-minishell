# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 16:17:38 by psuanpro          #+#    #+#              #
#    Updated: 2022/12/09 00:25:27 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c 

RLDIR = /usr/local/opt/readline
LIBFT = ./libft 
INCLUDE = -Llibft -L$(RLDIR) -lreadline -I$(RLDIR)
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

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)
	@$(COMPILE)

all: $(NAME)

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)
	@$(FCLEAN)

re: fclean all

.PHONY: all clean fclean re
