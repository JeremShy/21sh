/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:52:24 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 23:04:14 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_count_char(char *s, char c, int *size)
{
	int		i;

	if (!s)
	{
		*size = 0;
		return ;
	}
	*size = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			*size = *size + 1;
			while (s[i] == c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
}

static char	**ft_alloc_string_tab(int size)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * size + 1);
	i = 0;
	if (ret != NULL)
	{
		while (i <= size)
		{
			ret[i] = NULL;
			i++;
		}
	}
	return (ret);
}

static int	ft_get_block_end(char *s, int i, char c)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	ft_add_string_to_tab(char *s, int i, int j, char **ret)
{
	int		pos;

	pos = 0;
	while (ret[pos] != NULL)
		pos++;
	ret[pos] = ft_strsub(s, i, j - i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		size;
	int		i;
	int		j;

	ft_count_char((char *)s, c, &size);
	ret = ft_alloc_string_tab(size);
	if (s && ret != NULL)
	{
		i = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != '\0')
		{
			j = ft_get_block_end((char *)s, i, c);
			ft_add_string_to_tab((char *)s, i, j, ret);
			while (s[j] == c && s[j] != '\0')
				j++;
			i = j;
		}
	}
	return (ret);
}
