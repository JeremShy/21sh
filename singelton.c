/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singelton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:15 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

t_termios	*singleton_termios(t_termios *termios, int i)
{
	static t_termios *singleton = NULL;

	if (i)
		singleton = termios;
	return (singleton);
}

t_data		*singleton_data(t_data *termios, int i)
{
	static t_data *singleton = NULL;

	if (i)
		singleton = termios;
	return (singleton);
}
