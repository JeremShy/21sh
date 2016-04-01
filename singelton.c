/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singelton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:33:37 by jcamhi            #+#    #+#             */
/*   Updated: 2016/04/01 19:44:51 by jcamhi           ###   ########.fr       */
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
