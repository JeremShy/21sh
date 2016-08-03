SRC_NAME = main.c \
	   env.c \
	   list.c \
	   special_split.c \
	   utils.c \
	   builtins.c \
	   ft_cd.c \
	   list2.c \
	   exec.c \
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
		 fd_functions.c \
		 handle.c \
		 is_parse.c \
		 quote.c \
		 heredoc.c \
		 list_heredoc.c \
		 handle_pipe.c \
		 get_pb.c \
		 signal.c \
		 echo.c \
		 line_2.c \
		 history_builtin.c \
		 history_flag_none.c \
		 history_flag_c.c \
		 history_flag_d.c \
		 history_flag_a.c \
		 history_flag_n.c \
		 history_flag_r.c \
		 history_flag_w.c \
		 history_flag_p.c \
		 history_flag_s.c \
		 vid_inv.c \
		 builtin_env.c

OBJ_PATH = ./obj/
INC_PATH = ./includes

NAME = 21sh
NAMELIB = lib$(NAME).a

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

LFLAGS = -ltermcap

LIB_DIR=./lib
STATIC_LIBS= $(LIB_DIR)/libft.a $(LIB_DIR)/libftprintf.a

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

# parsing:
	# gcc -I includes ft_is_x.c list_parse.c parse_function.c fd_functions.c lib/libft.a parse.c handle.c is_parse.c quote.c -g

all : $(NAME)

$(NAME) : $(OBJ)
	@mkdir -p $(LIB_DIR)
	make -C libsrcs/libft
	make -C libsrcs/ft_printf
	@ar -cr $(NAMELIB) $^
	@ranlib $(NAMELIB)
	$(CC) $(CFLAGS) $(NAMELIB) $(STATIC_LIBS) $(LFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	#@rmdir -p $(OBJ_PATH)
	make -C libsrcs/libft clean
	make -C libsrcs/ft_printf clean

fclean: clean
	rm -fv $(NAME) $(NAMELIB)
	make -C libsrcs/libft fclean
	make -C libsrcs/ft_printf fclean
	#@rmdir lib 2> /dev/null || true

re: fclean all

check: $(NAME)
	python -m unittest discover tests/

.PHONY : all clean fclean re check
