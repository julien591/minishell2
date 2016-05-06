##
## Makefile for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2
##
## Made by julien
## Login   <julien@epitech.net>
##
## Started on  Fri May 06 10:55:44 2016 julien
## Last update Fri May 06 10:55:44 2016 julien
##

SRC	= src/builtins.c \
	  src/cd.c \
	  src/chevron_d_left.c \
	  src/chevron_left.c \
	  src/chevron_right.c \
	  src/comma.c \
	  src/env.c \
	  src/execute.c \
	  src/free.c \
	  src/get_functions.c \
	  src/main.c \
	  src/malloc.c \
	  src/parsing_ms2.c \
	  src/pipe.c \
	  src/pipe_init.c \
	  src/read.c \
	  src/setenv_unsetenv.c \
	  src/str_functions.c \
	  src/wordtab.c

CC	= gcc

RM	= rm -rf

INC	= -I./include

CFLAGS	=  -W -Wall -Wextra $(INC)

LDFLAGS	=

NAME	= mysh

OBJ =	$(SRC:.c=.o)


all: $(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
