/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:38:44 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/27 18:54:59 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

t_termios	*init_term(t_env *env)
{
	t_termios	term;
	t_termios	*ret;
	char		*name_term;

	ret = (t_termios*)malloc(sizeof(t_termios));
	tcgetattr(0, &term);
	tcgetattr(0, ret);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (NULL);
	name_term = find_arg(env, "TERM");
	if (ft_strequ(name_term, ""))
	{
		free(name_term);
		return (NULL);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (NULL);
	return (ret);
}

int		my_putchar(int c)
{
	static int  fd = 0;

	if (!fd)
		fd = open("/dev/tty", O_RDWR);
	if (!isatty(fd))
	{
		ft_printf("/dev/tty is not a valid tty.\n");
		exit(EXIT_FAILURE);
	}
	if (c == -1)
	{
		close(fd);
		return (c);
	}
	write(fd, &c, 1);
	return (c);
}

void exec_tcap(char *tcap)
{
	tputs(tgetstr(tcap, NULL), 1, my_putchar);
}

void invert_term(void)
{
	t_termios	*tmp;
	t_termios	*current;

	current = malloc(sizeof(t_termios));
	tmp = singleton_termios(NULL, 0);
	tcgetattr(0, current);
	tcsetattr(0, TCSADRAIN, tmp);
	free(tmp);
	singleton_termios(current, 1);
}
