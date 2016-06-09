# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/08 11:49:18 by jcamhi            #+#    #+#              #
#    Updated: 2016/06/09 21:35:18 by jcamhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
	   env.c \
	   list.c \
	   special_split.c \
	   utils.c \
	   builtins.c \
	   ft_cd.c \
	   list2.c \
	   exec.c \
	   ft_source.c \
	   singelton.c \
	   term.c \
	   boucle.c \
		 ft_string.c \
		 line.c \
		 ft_is_x.c \
		 history.c\
		 list_parse.c \
		 parse.c \
		 parse_function.c \
		 fd_functions.c

OBJ_PATH = ./obj/
INC_PATH = ./includes

NAME = 21sh

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

LFLAGS = -ltermcap -Llib/ -lft -lftprintf

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

parsing:
	gcc -I includes ft_is_x.c list_parse.c parse_function.c fd_functions.c lib/libft.a parse.c

all : $(NAME)

$(NAME) : $(OBJ)
#	@mkdir ./lib 2> /dev/null || true
#	make -C libsrcs/libft
#	make -C libsrcs/ft_printf
	$(CC) $(CFLAGS) $(LFLAGS) $(INC) -o $@ $^

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	/bin/rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
#	make -C libsrcs/libft clean
#	make -C libsrcs/ft_printf clean

fclean: clean
	rm -fv $(NAME)
#	make -C libsrcs/libft fclean
#	make -C libsrcs/ft_printf fclean
#	@rmdir lib 2> /dev/null || true

re: fclean all

.PHONY : all clean fclean re
