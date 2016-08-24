#include <sh21.h>

// int	ft_source(char **scmd, t_env **env)
// {
// 	int		fd;
// 	char	*cmd;
//
// 	if (scmd[1] == '\0')
// 		return (0);
// 	fd = open(scmd[1], O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	while (get_next_line(fd, &cmd))
// 		exec_cmd(cmd, env);
// 	return (1);
// }
