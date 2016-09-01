/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:30:26 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 17:30:33 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			is_quote(char car)
{
	if (car == '\'' || car == '"' || car == '`' || car == '(' || car == ')'
			|| car == '[' || car == ']' || car == '{' || car == '}')
		return (1);
	return (0);
}

int			is_quote_open(char car)
{
	if (car == '\'' || car == '"' || car == '`' || car == '('
			|| car == '[' || car == '{')
		return (1);
	return (0);
}

int			is_quote_close(char car, char open)
{
	if (car == '\'' && open == '\'')
		return (1);
	else if (car == '"' && open == '"')
		return (1);
	else if (car == '`' && open == '`')
		return (1);
	else if (car == '(' && open == ')')
		return (1);
	else if (car == '[' && open == ']')
		return (1);
	else if (car == '{' && open == '}')
		return (1);
	return (0);
}
