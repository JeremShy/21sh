/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:11:48 by adomingu          #+#    #+#             */
/*   Updated: 2015/10/06 07:55:39 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_getlen(int *len, int n)
{
	if (n > 0)
		*len = 0;
	else if (n <= 0)
		*len = 1;
	while (n != 0)
	{
		n /= 10;
		(*len)++;
	}
}

void	ft_putnbr_str(char *ret, int len, int n)
{
	if (n < 0)
	{
		n *= -1;
		ret[0] = '-';
	}
	if (n == 0)
		ret[0] = '0';
	while (n != 0)
	{
		len--;
		ret[len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_getlen(&len, n);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret != NULL)
	{
		ft_putnbr_str(ret, len, n);
		ret[len] = '\0';
	}
	return (ret);
}
