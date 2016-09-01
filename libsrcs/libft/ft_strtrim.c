/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	int	i;
	int	len;
	int	stay;

	if (!s)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
		i++;
	stay = i;
	i = (int)ft_strlen(s) - 1;
	while ((s[i - len] == '\n' || s[i - len] == ' ' || s[i - len] == '\t' ||
				s[i - len] == '\0') && (i - len > 0))
		len++;
	if (i == len)
		return (ft_strdup(""));
	return (ft_strsub(s, stay, i - stay - len + 1));
}
