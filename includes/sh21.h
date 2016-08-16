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
# include <sys/time.h>
# define	NONE (char)0
# define	POINT_VIRGULE ';'
# define	ETET (char)1
# define	OUOU (char)2
# define	ERR_GETOLDWD "Error: Get OLDPWD\n"
# define	ERR_GETCWD "Error: Get PWD\n"
# define	BUF_CWD 1024
# define	BUF_CWD_MAX BUF_CWD * 1024
# define	BUF_CWD_ERR "Error in Get CWD\n"


# undef tab

typedef struct dirent		t_dirent;
typedef struct termios	t_termios;

typedef struct	s_env {
	char					*name;
	char					*arg;
	struct s_env	*next;
}								t_env;

typedef struct	s_var {
	char					*name;
	char					*arg;
	struct s_var	*next;
}								t_var;

typedef struct		s_fd {
	int					fd;
	struct s_fd	*next;
}								t_fd;

typedef	struct		s_cmd {
	char					**av;
//	int						ac;
	int						sep;
	struct s_cmd	*next;
	char					*cmd_path;
	int						is_valid;
	t_fd					*fd_in;		//0
	t_fd					*fd_out;	//1
	t_fd					*fd_err;	//2
	int						p_error;
	int						error;
	int						ret;
}								t_cmd;

typedef struct	s_history {
	char							*line;
	int								time;
	int								get_from_file;
	struct s_history	*next;
	struct s_history	*prec;

}								t_history;

typedef struct	s_hc {
	struct s_hc	*next;
	char				*content;
}								t_hc;

typedef struct	s_auto {
	char 					*str;
	struct s_auto	*next;
}								t_auto;

typedef struct	s_data {
	int				curs_x; //emplacement du cuurseur en x (absolu)
	int				curs_y; // emplacement curseur y (relatif)
	char			*prompt; //prompt
	int				len_prompt; //longueur prompt
	char			*cmd; //commande en cours
	char			*ancienne_cmd; //truc de heredoc (ca marche)
	char			c; //caractere si on est dans une quote ou autre
	int				index; //la ou on ecrit
	int				old_index; //Ancien index
	int				quote_old_index;
	int				real_len_cmd; //longueur reelle de la commande
	t_history	*history; //Dernier element historique
	t_history	*history_en_cours; //Emplacement en cours dans l;historique
	int				history_fd;
	int				history_flag[8];
	char			*nouveau; //Chais pu
	char 			*key_here; //Cle du heredoc
	size_t		end_hd; //fin du heredoc
	t_hc			*heredocs; //Liste avec les heredocs par ordre d'apparition
	char			*first; // Key pour la recherche vers le haut
	int				first_search; // Permet d'eviter le soucis quand on appuie plusieurs fois sur haut et que ca se chevauche.
	t_env			*env; // l'env.
	t_var			*var;
	int				win_y; //Taille en y de la fenetre
	int				win_x; // Taille en x de la fenetre
	int				after_prompt; // Position curseur apres prompt
	int				in_env_i;
	char			*cmd_tmp; // comme ancienne_cmd, permet de conserver une ligne ou plusieurs de la commande lors des quotes ou heredoc
	int				quote_or_hd; // definir si on est dans une quote ou hd
	int				first_line_of_hd; // pour eviter que l'on se retrouve avec le \n du strjoin
	char			*heredocs_tmp; // Pour se souvenir des heredocs. (La pince téton ?)
	char			*command_save; // Pour se souvenir dans la commande quand on arrive dans des heredocs.
	int				index_min_win;
	int				mode_copy; // À 1 si on est en mode de surlignement, à 0 sinon.
	int				index_min_copy; // premier index surligne
	int				index_max_copy; // dernier index surligne
	char			*clipboard; // presse papier
	int				flag_enter; // dans le parsing, pour savoir si on est entré dans une fonction
	t_auto		*list_auto; // autocompletion
	char			*cmd_before_auto; //commande avant autocompletion.
	int				index_before_auto; // index avant autocompletion
	int				index_in_word_before_auto; // Index dans le mot avant l'autocompletion (pour ls pou<tab>, ca va etre 3 par exemple);
	char			*absolute_cmd_before_auto; //Veritable cmd au cas ou l'index n'est pas au bout;
}				t_data;

t_env				*ft_parse_env(char **env);
t_env				*add_elem_end(t_env *list, char *name, char *arg);
char				**ft_special_split(char const *s);
int					is_builtin(char *cmd);
int					exec_builtin(t_cmd *cmd, t_env **env, t_data *data);
void				change_arg(t_env *list, char *name, char *new_arg);
char				*find_arg(t_env *list, char *name);
int					ft_cd(char **scmd, t_env *env, t_data *data);
int					isset_arg(t_env *list, char *name);
void				delete_elem(t_env **list, char *name);
void				delete_list(t_env *list);
int					exec_file(t_cmd *cmd, t_env *list, int in_env_i, t_data *data);
char				**make_env_char(t_env *list);
int					ft_source(char **scmd, t_env **env);
void				exec_cmd(t_env **env, t_cmd *command, t_data *data);
void				handle_line(char *line, t_env **env);
void				free_char_tab(char **tab);
t_termios		*singleton_termios(t_termios *termios, int i);
t_termios		*init_term(t_data *data);
void				boucle(t_env *env, t_data *data);
int					my_putchar(int c);
void				exec_tcap(char *tcap);
char				*insert_char(char *str, int index, char c);
char				*delete_char(char *str, int index);
char				*print_prompt(t_env *env, t_data *data);
void				move_left(t_data *data);
void				move_left_simple(t_data *data);
void				move_right(t_data *data);
void				move_right_simple(t_data *data);
int 				is_special(char *str, int quote);
int 				is_quote(char car);
int 				is_quote_open(char car);
int 				is_quote_close(char car, char open);
int					is_quote_end(t_data *data);
int					ft_isspace2(char car);
void				prompt_quote(t_data *data);
t_history		*add_history_elem(t_history *list, t_history *elem);
t_history		*create_history_elem(char *content);
t_cmd				*create_cmd_elem(char *str, int count, t_hc **heredocs);
t_cmd				*add_cmd_elem(t_cmd *list, t_cmd *elem);
char*				pos_quote_end(char en_cours, char *str);
void				print_list(t_cmd *lst);
t_cmd				*parse(char	*str, t_hc *heredocs, t_env **env, t_data *data);
void				join_inside_quote(size_t *i, char **str);
int					is_aggr(size_t *i, char *str, int jump);
char				*is_redir(size_t *i, char *str, int jump, t_cmd *cmd);
char				*skip_quotes(char **str, size_t *i, t_cmd *cmd);
int					is_sep(size_t *i, char *str, int jump, t_cmd *cmd);
t_fd				*add_fd_elem(t_fd *list, t_fd *elem);
t_fd				*create_fd(int fd);
int					split_cmd(int count, char **str, t_cmd *cmd, t_hc **heredocs);
char				*skip_quotes_nb_arg(char *str, size_t *i, t_cmd *cmd);
int					is_empty(char *str, size_t *i);
char				*handle_redir(size_t *i, char **str, int jump, t_cmd *cmd, t_hc **heredocs);
t_fd				*copy_list_fd(t_fd *list);
t_fd				*copy_fd(t_fd *list);
int					handle_aggr(size_t *i, char *str, int jump, t_cmd *cmd);
void 				print_fd_list(t_cmd *list);
void 				print_fd(t_fd *list);
int					def_sep(char *str);
int					is_key(t_data *data);
t_hc				*create_hc_elem(char *content);
t_hc				*add_hc_elem(t_hc *list, t_hc *elem);
void				display_heredoc (t_hc *elem);
void				free_heredoc(t_hc *list);
char				*find_exec(char *scmd, t_data *data);
int					fork_pipes(t_cmd *cmd, t_env *env, t_data *data);
int					spawn_proc (t_cmd *cmd, t_env *env, t_data *data);
char				*get_pb(void);
int					is_empty_border(char *str, size_t beg, size_t end);
int					is_parse_error(char *str);
void				get_pos_after_quote(size_t *i, char *str);
void				close_fd_cmd(t_cmd *cmd);
void				close_fd(t_fd *fd);
void				multi_redir_cmd_out(t_cmd	*cmd);
void				sigint(int sig);
t_data			*singleton_data(t_data *termios, int i);
void				invert_term(void);
void				sigwinch(int sig);
void				get_winsize(t_data *data);
int					get_actual_line(t_data *data);
int					get_actual_cursor(t_data *data);
int					get_prompt_line(t_data *data);
int					can_move_down(t_data *data);
int					can_move_up(t_data	*data);
int					get_line_max(t_data *data);
void				move_r2l(t_data *data);
void				insert_mode(t_data *data, char c);
int					get_actual_cursor(t_data *data);
void				delete_mode(t_data *data);
int					ft_echo(char **scmd, t_cmd *cmd);
void				get_index_min_win(t_data *data);
int					get_actual_cursor_2(t_data *data);
void				page_up(t_data *data);
void				page_down(t_data *data);
void				vi_char(char c);
void				vi_str(char *s);
void				vi_str_free(char *s);
void				move_left_without_mod(t_data *data);
void				move_right_without_mod(t_data *data);
void				move_r2l(t_data *data);
void				move_l2r(t_data *data);
void				previous_word(t_data *data);
void				next_word(t_data *data);
void				init_history(t_data *data);
int					ft_history(char **scmd, t_data *data, t_cmd *cmd);
void				init_flag(t_data *data);
int					get_history_command_part(char *line);
int					get_history_path(t_data *data, char **path);
int					get_history_fd(t_data *data);
int					history_flag_none(t_data *data, char **scmd, t_cmd *cmd);
int					history_flag_c(t_data *data);
int					history_flag_d(t_data *data, char **scmd, t_cmd *cmd);
int					get_history_path_anrw(t_data *data, char **path, char *scmd);
int					history_flag_a(t_data *data, char *scmd);
int					history_flag_w(t_data *data, char *scmd);
int					history_flag_r(t_data *data, char *scmd, t_cmd *cmd);
int					history_flag_n(t_data *data, char *scmd, t_cmd *cmd);
void				delete_last_history(t_data *data);
char  			*get_history_substutition(t_data *data, char *scmd);
int					history_flag_p(char **scmd, t_cmd *cmd);
int					history_flag_s(t_data *data, char **scmd);
char				*history_subsitution_nb_arg(t_data *data, char *command);
int					is_substitution(char *str, size_t *i, t_cmd *cmd, t_data *data);
void				history_exit(t_data *data);
void				ft_autocomplete(t_data *data);
int					env_tmp_exec(t_env **env, t_data *data, char **scmd, t_cmd *cmd);
int					print_env(t_env *env, t_cmd *cmd);
int   			true_var_and_subs(t_data *data, char **str);
int					ft_setvar(char **scmd, t_data *data, t_cmd *cmd);
char				*find_var_env(t_data *data, char *name);
int  			 	is_escaped_char(char *str, int index);
int					is_pipe_e_parse_error(char *str);
void				putstr_builtin(t_cmd *cmd, char *str, int fd);
void				putendl_builtin(t_cmd *cmd, char *str, int fd);
void				putchar_builtin(t_cmd *cmd, char car, int fd);
void				putnbr_builtin(t_cmd *cmd, int nb, int fd);

int cd(char **cmd, t_data *data);

#endif
