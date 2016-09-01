/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:53:01 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/10 22:49:02 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		start;
	int		end;

	if (s == NULL)
		return (NULL);
	end = ft_strlen(s) - 1;
	start = 0;
	while ((s[start] == ' ' || s[start] == '\n' ||\
			s[start] == '\t') && s[start] != '\0')
		start++;
	if (s[start] == '\0')
		return (ft_strdup(""));
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	end++;
	return (ft_strsub(s, start, end - start));
}
