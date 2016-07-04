/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 22:10:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/27 22:21:55 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int verif_empty_quote(char *str, size_t *i) // ne supprime pas les quotes, si pas ok, renvoi un caractere apres la quote qui close
{
	size_t tmp;

	tmp = *i + 1;
	if (!str[tmp] || ft_isspace2(str[tmp]))
	{
		// printf("J'AIME LE KAKA AUX AMANDES GRILLEES\n");
		return (1);
	}
	while (!is_quote_close(str[*i], str[tmp]) && str[tmp])
	{
		if (!is_quote(str[tmp]) && !ft_isspace2(str[tmp]))
			return(1);
		tmp++;
	}
	//  printf("tmp = %zu and current char = [%c]\n", tmp, str[tmp]);
	if (str[tmp])
		*i = tmp + 1;
	return (0);
}

void	get_pos_after_quote(size_t *i, char *str)
{
	char open;

	open = str[*i];
	while (is_quote_close(open, str[*i + 1]) == 0 && str[*i + 1])
		(*i)++;
	if (str[*i])
		(*i)++;
	}

char *skip_quotes_nb_arg(char *str, size_t *i, t_cmd *cmd)
{
	size_t		start;

	if (!verif_empty_quote(str, i))
	{
		return (NULL);
	}
 	start = *i;
	while(str[*i] && !ft_isspace2(str[*i]) && !is_sep(i, str, 0, cmd))
	{
		if (is_redir(i, str, 0, cmd) && ft_isdigit(str[*i]))
		{
			// printf("CHAR ACTUEL : [%c] avec i = %zu (after %c)\n", str[*i], *i, str[*i + 1]);
			break ;
		}
		if (is_quote_open(str[*i]))
		{
			get_pos_after_quote(i, str);
		}
		(*i)++;
	}
	if (start != *i)
		return ("KAKA");//(ft_strsub(str, start, *i - start));
	return(NULL);
}

char *skip_quotes(char *str, size_t *i, t_cmd *cmd)
{
	size_t		start;

	if (is_quote_open(str[*i]) && !verif_empty_quote(str, i))
		return (NULL);

 	start = *i;
	// printf("glblblbl %s\n", str + *i);
	while(str[*i] && !ft_isspace2(str[*i]) && !is_sep(i, str, 0, cmd))
	{
		if ((is_redir(i, str, 0, cmd) || is_aggr(i, str, 0)) && ft_isdigit(str[*i]))
		{
			printf("CHAR ACTUEL : [%c] avec i = %zu (after %c)\n", str[*i], *i, str[*i + 1]);
			(*i)++;
			break ;
		}
		if (is_quote_open(str[*i]))
		{
			join_inside_quote(i, str);
		}

		(*i)++;
	}
	if (start != *i)
	//{
		// printf("popo\n");
		return(ft_strsub(str, start, *i - start));
	// }
	return(NULL);
}
