/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi   <jcamhi  @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:56:35 by jcamhi            #+#    #+#             */
/*   Updated: 2016/05/23 14:18:47 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>
#include <stdio.h>

size_t		get_real_len(char const *s)
{
	size_t	len;
	int			i;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\'' && s[i] != '\"')
			len++;
		i++;
	}
	return(len);
}

char	*ft_special_sub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;
	size_t	real_len;

	if (!s)
		return (NULL);
	real_len = get_real_len(s);
	res = (char*)malloc((real_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (s[i] != '\'' && s[i] != '\"')
		{
			res[j] = s[start + (unsigned int)i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

int count_av(char *str)
{
	int	i;
	int	count;
	int	quote;
	int	dquote;

	count = 0;
	i = 0;
	while(str[i] != ' ' && str[i] != '\0')
		i++;
	count++;
	i++; // On deplace l'index a la position suivante pour passer l'espace.
	quote = 0;
	dquote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			dquote = dquote == 0 ? 1 : 0;
		else if (str[i] == '\'')
			quote = quote == 0 ? 1 : 0;
		else if (is_special(str[i]) && !dquote && !quote)
		{
			if (i == 0)
			{
				printf("zsh: parse error near %c\n", str[i]);
				exit(EXIT_FAILURE);
			}
			else
				return (count + 1);
		}
		else if (str[i] == ' ')
			count++;
	}
}

int	main(int ac, char **av)
{
	char	*str;
	char	*cmd;
	char	*args;
	char	**argv;
	int		i;

	if (ac == 1)
	{
		printf("Mec mets un argument, t'es con ou quoi ?\n");
		return (0);
	}
	str = av[1];
	printf("String to analyze : |%s|\n", str);
	i = 0;

	while(str[i] != ' ' && str[i] != '\0')
		i++;
	cmd = ft_special_sub(str, 0, i);
	printf("commande : %s\n", cmd);
	i++; // On deplace l'index a la position suivante pour passer l'espace.
	while(str[i] != '\0')
	{

	}
}
