/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 22:10:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 00:02:11 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int verif_empty_quote(char *str, size_t *i) // ne supprime pas les quotes, si pas ok, renvoi un caractere apres la quote qui close
{
	size_t tmp;

	tmp = *i + 1;
	if (!str[tmp] || ft_isspace2(str[tmp]))
	{
		printf("J'AIME LE KAKA AUX AMANDES GRILLEES\n");
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

	// printf("str = [%c] with i = %zu /// str = [%s]\n", str[*i], *i, str);
	if (!verif_empty_quote(str, i))
	{
		printf("KAKA\n");
		return (NULL);
	}
 	start = *i;
	printf("---------str[%c] /// *i = %zu -----------\n", str[*i], *i);
	while(str[*i] && !ft_isspace2(str[*i]) && !is_redir(i, str, 0, cmd) && !is_aggr(i, str, 0) && !is_sep(i, str, 0))
	{
		// printf("char actuel = [%c]\n", str[*i]);
		if (is_quote_open(str[*i]))
		{
			get_pos_after_quote(i, str);
				// printf(" ---------  str = [%c] with i = %zu /// str = [%s]\n", str[*i], *i, str);
		}
		(*i)++;
		// printf("char actuel = [%c]\n", str[*i]);
	}
	// printf("-------END-------- char actuel = [%c]\n", str[*i]);
	//printf("END OF WORD WITH i = %zu\n", *i);
	printf("----- i = %zu\n", *i);
	if (start != *i)
		return ("KAKA");//(ft_strsub(str, start, *i - start));
	printf("JE SUIS NULL\n");
	return(NULL);
}

char *skip_quotes(char *str, size_t *i, t_cmd *cmd)
{
	size_t		start;

	// printf("str = [%c] with i = %zu /// str = [%s]\n", str[*i], *i, str);
	if (!verif_empty_quote(str, i))
		return (NULL);
 	start = *i;
	// printf("str[%c]\n", str[*i]);
	while(str[*i] && !ft_isspace2(str[*i]) && !is_redir(i, str, 0, cmd) && !is_aggr(i, str, 0) && !is_sep(i, str, 0))
	{
		// printf("char actuel = [%c]\n", str[*i]);
		if (is_quote_open(str[*i]))
		{
			join_inside_quote(i, str);
				// printf(" ---------  str = [%c] with i = %zu /// str = [%s]\n", str[*i], *i, str);
		}
		(*i)++;
		// printf("char actuel = [%c]\n", str[*i]);
	}
	// printf("-------END-------- char actuel = [%c]\n", str[*i]);
	//printf("END OF WORD WITH i = %zu\n", *i);
	if (start != *i)
		return(ft_strsub(str, start, *i - start));
	return(NULL);
}
