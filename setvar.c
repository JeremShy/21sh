#include <sh21.h>

// t_var *create_var_elem (char *content)
// {
// 	t_var	*elem;
//
// 	elem = malloc(sizeof(t_var));
// 	elem->content = content;
// 	elem->next = NULL;
// 	return (elem);
// }
// t_var 	*add_var_elem(t_var *list, t_var *elem)
// {
// 	t_var *tmp;
//
// 	tmp = list;
// 	if (list == NULL)
// 		return (elem);
// 	while (list->next != NULL)
//   		list = list->next;
// 	list->next = elem;
// 	return (tmp);
// }

int				isset_var(t_var *list, char *name)
{
	while (list)
	{
		if (ft_strequ(name, list->name))
			return (1);
		list = list->next;
	}
	return (0);
}

void			change_var(t_var *list, char *name, char *new_arg)
{
	if (!list)
		return ;
	while (list)
	{
		if (ft_strequ(list->name, name))
		{
			free(list->arg);
			list->arg = ft_strdup(new_arg);
		}
		list = list->next;
	}
}

static t_var	*create_var_elem(char *name, char *arg)
{
	t_var	*ret;

	ret = malloc(sizeof(t_list));
	ret->name = ft_strdup(name);
	ret->arg = ft_strdup(arg);
	ret->next = NULL;
	return (ret);
}

t_var			*add_var_elem_end(t_var *list, char *name, char *arg)
{
	t_var	*tmp;

	tmp = list;
	if (!list)
		return (create_var_elem(name, arg));
	while (list->next)
		list = list->next;
	list->next = create_var_elem(name, arg);
	return (tmp);
}

int			ft_setvar(char **scmd, t_data *data)
{
	if (!scmd[1] || !scmd[2])
  {
    ft_putstr_fd("42sh: invalid argument [arg1 arg2]\n", 2);
    return (0);
  }
	if (isset_var(data->var, scmd[1]))
		change_var(data->var, scmd[1], scmd[2]);
	else
		 data->var = add_var_elem_end(data->var, scmd[1], scmd[2]);
	return (1);
}
