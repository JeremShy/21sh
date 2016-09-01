/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 01:00:03 by adomingu          #+#    #+#             */
/*   Updated: 2015/08/25 01:00:07 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_clear_str(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strtrim(str);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
				i++;
			ret[j] = ' ';
			j++;
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	ft_strdel(&str);
	return (ret);
}
