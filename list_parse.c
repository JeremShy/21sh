/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:12:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/08 22:43:07 by jcamhi           ###   ########.fr       */
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

void	join_inside_quote(size_t *i, char *str)
{
	size_t	tmp;
	char	open;

	open = str[*i];
	// printf("open : %c\n", open);
	while (is_quote_close(open, str[*i + 1]) == 0 && str[*i + 1])
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	tmp = *i;
	while (str[tmp + 2])
	{
		str[tmp] = str[tmp + 2];
		tmp++;
	}
	str[tmp] = '\0';
	// printf("str : =%s=\n", str);
	if (*i == 0 || is_quote_open(str[0]))
		return ;
	(*i)--;
}

// void replace_backslash(char *str, size_t *i)
// {
// 	size_t tmp;
//
// 	if (!(str[i] == '\\'))
// 		return ;
// 	tmp = *i;
// 	while (str[tmp])
// 	{
// 		str[tmp] = str[tmp + 1];
// 		tmp++;
// 	}
// }

char	**split_cmd(char *str, int count, int *sep)
{
	char		**av;
	size_t		i;
	size_t		n_av;
	size_t		tmp;
	int			quote;
	size_t 		start;
	// int			backslash;

	// printf("count : %d\n", count);
	av = (char**)malloc((count + 1) * sizeof(char*));
	if (!av)
		exit(0);
	// printf("on recoit : %s\n", str);
	i = 0;
	n_av = 0;
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		if (str[i] != '\0')
		{
			tmp = i;
			start = i;
			while (!ft_isspace2(str[i]) && str[i] != '\0')
			{
				// replace_backslash(str, &i);
				// if (str[i] == '\\')
				// 	backslash = 1;
				quote = 0;
				if (is_quote_open(str[i]))
				{
					// printf("avant : %zu\n", i);
					join_inside_quote(&i, str);
					// printf("apres : %zu\n", i);
					//if (!str[i])
					//break ;
					if (i == tmp)
						i--;
					// if (isspace(str[i + 1]) || str[i + 1] == '\0')
					quote = 1;
				}
				// if (i + 1 == tmp)
				// 	i++;
				if (is_special(str + i, quote) == 1)
				{
					av[n_av] = ft_strsub(str, start, i - start);
					n_av++;
					*sep = def_sep(str + i);
					av[count] = NULL;
					return (av);
				}
				// if (i == tmp)
				// 	i--;
				i++;
			}
			if (ft_isspace2(str[i]) || str[i] == '\0')
 			{
				av[n_av] = ft_strsub(str, start, i - start);
				n_av++;
			}
		}
	}
	av[count] = NULL;
	*sep = 0;
	return (av);
}

void		print_list(t_cmd *lst)
{
	size_t	i;
	char		**av;
	size_t	j;

	i = 0;
	while (lst != NULL)
	{
		printf("list number : %zu\n", i);
		av = lst->av;
		j = 0;
		while (av[j])
		{
			printf("av[%zu] : #%s#\n", j, av[j]);
			j++;
		}
		printf("sep : %c\n", lst->sep);
		i++;
		lst = lst->next;
		printf("\n");
	}
}

t_cmd	*create_cmd_elem(char *str, int count)
{
	t_cmd		*elem;
	int			sep;

	sep = 0;
	elem = (t_cmd*)malloc(sizeof(t_cmd));
	// printf("str: %s\n", str);
	elem->av = split_cmd(str, count, &sep);
	elem->next = NULL;
	// printf("sep : %c\n", (char)sep);
	elem->sep= sep;
	free(str);
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem)
{
	t_cmd *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (tmp);
}
