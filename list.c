/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:59:10 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/31 18:47:05 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

static t_env	*create_elem(char *name, char *arg)
{
	t_env	*ret;

	ret = malloc(sizeof(t_list));
	ret->name = ft_strdup(name);
	if (!arg)
		ret->arg = ft_strdup("");
	else
		ret->arg = ft_strdup(arg);
	ret->next = NULL;
	return (ret);
}

t_env			*add_elem_end(t_env *list, char *name, char *arg)
{
	t_env	*tmp;

	tmp = list;
	if (!list)
		return (create_elem(name, arg));
	while (list->next)
		list = list->next;
	list->next = create_elem(name, arg);
	return (tmp);
}

void			change_arg(t_env *list, char *name, char *new_arg)
{
	if (!list)
		return ;
	while (list)
	{
		if (ft_strequ(list->name, name))
		{
			free(list->arg);
			if (!new_arg)
				list->arg = ft_strdup("");
			else
				list->arg = ft_strdup(new_arg);
			break;
		}
		list = list->next;
	}
}

int				isset_arg(t_env *list, char *name)
{
	while (list)
	{
		if (ft_strequ(name, list->name))
			return (1);
		list = list->next;
	}
	return (0);
}

char			*find_arg(t_env *list, char *name)
{
	if (!list)
		return (ft_strdup(""));
	while (list)
	{
		if (ft_strequ(list->name, name))
			return (ft_strdup(list->arg));
		list = list->next;
	}
	return (ft_strdup(""));
}
