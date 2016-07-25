/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vid_inv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 21:36:15 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/25 21:38:22 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	vi_char(char c)
{
	exec_tcap("mr");
	ft_putchar(c);
	exec_tcap("me");
}

void	vi_str(char *s)
{
	exec_tcap("mr");
	ft_putstr(s);
	exec_tcap("me");
}

void	vi_str_free(char *s)
{
	exec_tcap("mr");
	ft_putstr(s);
	exec_tcap("me");
	free(s);
}
