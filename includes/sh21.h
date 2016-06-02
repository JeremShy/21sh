/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:31:08 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/02 14:50:24 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H
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
# undef tab

typedef struct dirent		t_dirent;
typedef struct termios	t_termios;

typedef struct	s_env {
	char			*name;
	char			*arg;
	struct s_env	*next;
}				t_env;

typedef struct s_data {
	int				curs_x;
	int				curs_y;
	char			*prompt;
	int				len_prompt;
	char			*cmd;
	char			c;
	int				index;
	int				real_len_cmd;
	int				dquote;
	int				quote;
	int				acc;
	int				cro;
	int				par;
}				t_data;

typedef	struct	s_cmd {
	char **av;
}								t_cmd;

t_env				*ft_parse_env(char **env);
t_env				*add_elem_end(t_env *list, char *name, char *arg);
char				**ft_special_split(char const *s);
int					is_builtin(char *cmd);
int					exec_builtin(char **scmd, t_env **env);
void				change_arg(t_env *list, char *name, char *new_arg);
char				*find_arg(t_env *list, char *name);
int					ft_cd(char **scmd, t_env *env);
int					isset_arg(t_env *list, char *name);
void				delete_elem(t_env **list, char *name);
void				delete_list(t_env *list);
int					exec_file(char **scmd, t_env *list);
char				**make_env_char(t_env *list);
int					ft_source(char **scmd, t_env **env);
void				exec_cmd(char *cmd, t_env **env);
void				handle_line(char *line, t_env **env);
void				free_char_tab(char **tab);
t_termios		*singleton_termios(t_termios *termios, int i);
t_termios		*init_term(void);
void				boucle(t_env *env, t_data *data);
int					my_putchar(int c);
void				exec_tcap(char *tcap);
char				*insert_char(char *str, int index, char c);
char				*delete_char(char *str, int index);
char				*print_prompt(t_env *env, t_data *data);
void				move_left(t_data *data);
void				move_right(t_data *data);

int 				is_special(char car);
int 				is_quote(char car);
int 				is_quote_open(char car);
int 				is_quote_close(char car, char open);
int					is_quote_end(t_data *data);
int					ft_isspace2(char car);
void				prompt_quote(t_data *data);
#endif
