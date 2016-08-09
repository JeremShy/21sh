#include <sh21.h>

t_hc *create_var_elem (char *content)
{
	t_hc	*elem;

	elem = malloc(sizeof(t_hc));
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
t_hc 	*add_var_elem(t_hc *list, t_hc *elem)
{
	t_hc *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
  		list = list->next;
	list->next = elem;
	return (tmp);
}

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

int			ft_addvar(char **scmd, t_data *data)
{
	if (!scmd[1] || !scmd[2])
  {
    ft_strdup("42sh: you must specify an argument to add a local variable\n", 2);
    return (0);
  }
	if (isset_var(*env, scmd[1]))
		change_var(*env, scmd[1], scmd[2]);
	else
		 data->var = add_var_elem_end(data->var, scmd[1], scmd[2]);
	return (1);
}
