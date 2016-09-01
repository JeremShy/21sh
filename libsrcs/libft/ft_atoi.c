/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:20:47 by adomingu          #+#    #+#             */
/*   Updated: 2015/09/23 05:01:31 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_invalid(t_data r, int sign)
{
	int		cond1;
	int		cond2;
	int		cond3;

	cond1 = r.result != r.resultll && r.result * sign != r.resultll * sign;
	cond2 = r.result != r.resultl && r.result * sign != r.resultl * sign;
	cond3 = r.result != r.resulti && r.result * sign != r.resulti * sign;
	return (cond1 && cond2 && cond3);
}

static void	ft_loop(t_data *r, const char *str, size_t i)
{
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r->result = r->result * 10 + str[i] - '0';
		r->resultl = r->resultl * 10 + str[i] - '0';
		r->resultll = r->resultll * 10 + str[i] - '0';
		r->resulti = r->resulti * 10 + str[i] - '0';
		i++;
	}
}

int			ft_atoi(const char *str)
{
	t_data	r;
	int		sign;
	size_t	i;

	i = 0;
	r.result = 0;
	r.resultl = 0;
	r.resultll = 0;
	r.resulti = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	ft_loop(&r, str, i);
	if (ft_invalid(r, sign))
	{
		if (sign < 0)
			return (0);
		return (-sign);
	}
	return (r.resulti * sign);
}
