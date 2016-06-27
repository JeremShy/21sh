/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 16:17:58 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/27 19:01:32 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_aggr(size_t *i, char *str, int jump)
{
	size_t tmp;

	tmp = *i;
	if (str[*i] == '>' && str[*i + 1] == '&' && (ft_isdigit(str[*i + 2]) || str[*i + 2] == '-')) // Il faut que ca commence par un <, suivi de..
	{
		(*i) += 2;
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump) // Si on a passé un en troisieme parametre, on fait bouger i.
			*i = tmp;
		return (1);
	}
	else if (ft_isdigit(str[*i]) && str[*i + 1] == '>' && str[*i + 2] == '&' && (ft_isdigit(str[*i + 3]) || str[*i + 3] == '-')) // Ou alors ca peut commencer par un nombre..
	{
		(*i) += 3;
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump)
			*i = tmp;
		return (1);
	}
	return (0);
}

char	*is_redir(size_t *i, char *str, int jump, t_cmd	*cmd)
{
	size_t	tmp;
	char		*quote;

	tmp = *i;
	if ((str[tmp] == '<' && str[tmp + 1] == '<') || (str[tmp] == '>' && str[tmp + 1] == '>')) // Il faut commence par deux chevrons...
		tmp += 2;
	else if (str[tmp] == '<' || str[tmp] == '>') // ... ou par un seul...
		tmp++;
	else if (ft_isdigit(str[*i])) // ... ou par un chiffre
	{
		// if (ft_isdigit(str[*i + 1]))
		// 	return (NULL);
		if ((str[tmp + 1] == '>' && str[tmp + 2] == '>'))
			tmp += 3;
		else if (str[tmp + 1] == '>')
			tmp += 2;
	}
	if (tmp != *i) // Si tmp a bougé du fait des opérations précédentes.
	{
		while (ft_isspace2(str[tmp])) // On saute les espaces
			tmp++;
		if (is_empty(str, &tmp)) // Si la chaine est vide, on parse error (ls <           			)
		{
			cmd->p_error = 1;
			return (NULL);
		}
		quote = skip_quotes(str, &tmp, cmd); // On enleve les quotes.
		if (!quote)
			quote = ft_strdup("");
		if (jump)
			*i = tmp;
		return (quote); // On se barre à la fin.
	}
	return (NULL);
}

int		is_sep(size_t *i, char *str, int jump, t_cmd *cmd)
{
	size_t	ret;

	ret = *i;
	if (str[*i] == ';') // Si c'est un ;, un | ou un &&, on augmente ret.
		ret++;
	else if (str[*i] == '|')
		ret++;
	else if (ft_strnstr(str + *i, "&&", 2))
		ret += 2;
	else
		return (0);
	if (cmd)
		cmd->sep = def_sep(str + *i); // On mets le bon sep.
	if (jump) // Si le troisieme parametre est a un, on saute le sep.
		*i = ret;
	printf("on renvoit 1\n");
	return (1);
}
