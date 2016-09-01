/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 22:57:07 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		compte(unsigned long nbr, int base)
{
	int ret;

	ret = 0;
	while (nbr != 0)
	{
		nbr /= base;
		ret++;
	}
	return (ret);
}

char			*ft_itoa_base_ll(long long nbr, int base)
{
	char		*retour;
	int			nb;
	int			i;
	char		tab[17];

	if (nbr == 0)
		return (ft_alloc_str("0"));
	if (nbr < -9223372036854775807)
		return (ft_alloc_str("-9223372036854775808"));
	ft_strcpy(tab, "0123456789abcdef");
	i = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? nbr * -1 : nbr;
	nb = compte(nbr, base);
	nb += i;
	retour = mallocp(nb + 1);
	retour[0] = (i == 1 ? '-' : retour[0]);
	i = 1;
	while (nbr != 0)
	{
		retour[nb - i] = tab[nbr % base];
		nbr /= base;
		i++;
	}
	retour[nb] = '\0';
	return (retour);
}