# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psuanpro <Marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 23:10:55 by psuanpro          #+#    #+#              #
#    Updated: 2022/12/16 17:12:06 by psuanpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRCS	= ft_isalnum.c \
	  ft_isspace.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_strlen.c \
	  ft_calloc.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strncmp.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_printf.c \
	  ft_printf_untils_c.c \
	  ft_printf_untils_n.c \
	  ft_printf_check.c \
	  get_next_line_utils.c \
	  get_next_line.c \
	  ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

# BONUS_SRCS	= $(SRCS) \
# 		  ft_lstnew.c \
# 		  ft_lstadd_front.c \
# 		  ft_lstsize.c \
# 		  ft_lstlast.c \
# 		  ft_lstadd_back.c \
# 		  ft_lstdelone.c \
# 		  ft_lstclear.c \
# 		  ft_lstiter.c \
# 		  ft_lstmap.c

LIBC	= ar -rcs
CC	= gcc -Wall -Werror -Wextra -std=c99
RM	= rm -rf

BRED =\033[1;31m
BGRN =\033[1;32m
BYEL =\033[1;33m
RES = \033[0m

COMPILE = echo "$(BGRN)Libft compiled....$(RES)"
CLEAN = echo "$(BYEL)Libft clean....$(RES)"
FCLEAN = echo "$(BRED)Libft fclean....$(RES)"


$(NAME): $(SRCS)
	@$(CC) -c $(SRCS)
	@$(LIBC) $(NAME) *.o
	@$(COMPILE)

all: $(NAME)

# bonus: $(BONUS_SRCS)
# 	@$(CC) -c $(BONUS_SRCS)
# 	@$(LIBC) $(NAME) *.o

clean:
	@$(RM) *.o

fclean: clean
	@$(RM) $(NAME)
	@$(FCLEAN)

re: fclean all

.PHONY: all bonus clean fclean re
