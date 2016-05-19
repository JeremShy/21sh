/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:16:56 by jcamhi            #+#    #+#             */
/*   Updated: 2016/05/19 20:00:26 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char *insert_char(char *str, int index, char c)
{
	char *ret;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_strncpy(ret, str, index);
	ret[index] = c;
	ft_strcpy(ret + index + 1, str + index);
	free(str);
	return (ret);
}
