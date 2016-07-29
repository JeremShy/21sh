
#ifndef SCRIPT_H
# define SCRIPT_H
# include <ft_printf.h>
# include <libft.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <term.h>
# include <sys/ioctl.h>
# include <curses.h>

typedef struct dirent		t_dirent;
typedef struct termios	t_termios;

typedef struct	s_line {
	char			    *str;
	struct s_line	*next;
}				        t_line;
