CC = gcc
CFLAGS = -Wall -Werror -Wextra
READLINEFLAG = -lreadline
NAME = code

SRCS = main.c

all : $(NAME)

$(NAME):
	$(CC) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean $(NAME)
