/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:12:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/03 21:09:19 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		def_sep(char *str)
{
	if (ft_strnstr(str, ">>", 2))
		return (DCHEV_DROITE);
	else if (ft_strnstr(str, "<<", 2))
		return (DCHEV_GAUCHE);
	else if (ft_strnstr(str, "&&", 2))
		return (ETET);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == '>')
		return (str[0]);
	else if (str[0] == '<')
		return (str[0]);
	else if (str[0] == ';')
		return(str[0]);
	return (0);
}

// static int	special_copy(char **dst, char *str)
// {
// 	int		i;
// 	char	*suite;

// 	*dst = ft_strdup("");
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (is_quote_open(str[i]))
// 		{
// 			suite = pos_quote_end(str[i], str + i);
// 			*dst = ft_strjoinaf12(*dst, ft_strsub(str, i + 1, suite - (str + i) - 1));
// 			i = suite - str + 1;
// 		}
// 		else
// 		{
// 			*dst = ft_strjoinaf12(*dst, ft_strsub(str, i + 1, 1));
// 			i++;
// 		}
// 	}
// }

void	join_inside_quote(size_t *i, char *str)
{
	size_t	tmp;
	char	open;

	open = str[*i];
	while (is_quote_close(str[*i + 1], open) == 0)
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	// (*i)++;
	tmp = *i;
	//printf("CAR EN COURS = [%c]\n", str[*i]);
	while (str[tmp + 2])
	{
		str[tmp] = str[tmp + 2];
		tmp++; 
	}
	str[tmp] = '\0';
	if (*i == 0)
		return ;
	(*i)--;
	//printf("CAR AT THE END = [%c]\n", str[*i]);
}

char	**split_cmd(char *str, size_t count, int *sep)
{
	char		**av;
	size_t		i;
	size_t		n_av;
	size_t		tmp;
	char		*suite;
	int			quote;
	size_t		tmp2;
	size_t 		start;

	av = malloc(count * sizeof(char*));
	i = 0;
	n_av = 0;
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		printf("JE SUIS ICI /// i = %zu /// str[i] = [%c]\n", i, str[i]);
		if (str[i] != '\0')
		{
			tmp = i;
//			quote = 0;
			start = i;
			printf("CARACTERE EN COURS : avant = [%c] /// actuel = [%c] /// apres = [%c]\n", str[i - 1], str[i], str[i + 1]);
			while (!ft_isspace2(str[i]) && str[i] != '\0')
			{
				if (is_special(str + i) == 1)
				{
					*sep = def_sep(str + i);
					av[n_av] = NULL;
					return (av);
				}
//				printf("KAKA\n");
				// printf("1 str[i] : %c\n", str[i]);
				if (is_quote_open(str[i]))
				{
					//printf("A KE KOUKOU JE SUIS ICI\n");
					join_inside_quote(&i, str);
					//printf("str = [%s]\n", str);
					// if (quote != 0)
					// 	free(av[n_av]);
					//av[n_av] = ft_strdup(str);
					// suite = pos_quote_end(str[i], str + i + 1);
					// i = suite - str + 1;
					quote = 1;
					printf("CARACTERE EN COURS : avant = [%c] /// actuel = [%c] /// apres = [%c]\n", str[i - 1], str[i], str[i + 1]);
				}
				// printf("2 str[i] : %c\n", str[i]);
				// if (!is_special(str + i))
				// 	i++;
				// printf("4 str[i] : %c\n", str[i]);
				printf("i = %zu /// str[i] = [%c]\n", i, str[i]);
				i++;
			}
			if (ft_isspace2(str[i]) || str[i] == '\0' || is_special(str + i))
			{
				av[n_av] = ft_strsub(str, start, i - start);
				printf("RESULTAT DU SUB : [%s]\n", av[n_av]);
				n_av++;
				// printf("3 str[i] : %c\n", str[i]);
				// if (!quote)
				// {
				// 	av[n_av] = (char*)malloc((i - tmp + 1) * sizeof(char));
				// 	ft_strncpy(av[n_av], str + tmp, i - tmp);
				// }
				// else
				// {
				// 	av[n_av] = (char*)malloc((i - tmp - 1) * sizeof(char));
				// 	ft_strncpy(av[n_av], str + tmp + 1, i - tmp - 2);
				// }
				// special_copy(&(av[n_av]), str + tmp, i - tmp - 2);
				
				// if (!quote)
				// {
				// 	av[n_av] = (char*)malloc((i - tmp + 1) * sizeof(char));
				// 	ft_strncpy(av[n_av], str + tmp, i - tmp);		
				// }
				//printf("av[%zu] = %s\n", n_av, av[n_av]);
			}
		}
	}
	av[n_av] = NULL;
	*sep = 0;
	return (av);
}

t_cmd	*create_cmd_elem(char *str, size_t count)
{
	t_cmd		*elem;
	int			sep;

	sep = 0;
	elem = (t_cmd*)malloc(sizeof(t_cmd));
	printf("str: %s\n", str);
	elem->av = split_cmd(str, count, &sep);
	elem->next = NULL;
	printf("sep : %c\n", (char)sep);
	elem->caractere = sep;
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem)
{
	if (list == NULL)
		return (elem);
	list->next = elem;
	return (elem);
}
