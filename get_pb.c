/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:07 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	do_get_pb(t_data *data)
{
	char *pb;

	pb = get_pb();
	data->real_len_cmd += ft_strlen(pb);
	data->index += ft_strlen(pb);
	ft_putstr(pb);
	data->cmd = ft_strjoinaf12(data->cmd, pb);
}

char	*get_pb(void)
{
	int		tab[2];
	pipe	(tab);
	char	**av;

	av = malloc(2 * sizeof(char*));
	av[0] = "./pbpaste";
	av[1] = NULL;
	char **env;
	env = malloc(sizeof(char*));
	env[0] = NULL;
	int pid = fork();
	if (pid != 0)
		wait(NULL);
	else
	{
		close(1);
		dup(tab[1]);
		execve("/usr/bin/pbpaste", av, env);
	}
	close(tab[1]);
	char *str = malloc(1000);
	int n = read(tab[0], str, 999);
	str[n] = '\0';
	free(av[1]);
	free(av);
	free(env);
	return (str);
}
