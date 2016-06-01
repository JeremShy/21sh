/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:44:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/01 15:28:06 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int is_special(char car)
{
	if (car == '|' || car == '>' || car == '<')
		return(1);
	return(0);
}

int is_quote(char car)
{
	if (car == '\'' || car == '"' || car == '`' ||  car == '(' || car == ')'
		|| car == '[' || car == ']' || car == '{' || car == '}')
		return(car);
	return(0);
}

int	ft_isspace(char car)
{
	if (car == ' ' || car == '\t' || car =='\v' || car =='\f' || car =='\r')
		return (1);
	return (0);
}
