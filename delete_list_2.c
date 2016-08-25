#include <sh21.h>

void	delete_list_env(t_env *list)
{
	t_env *tmp;

	while (list)
	{
		tmp = list->next;
		free(list->name);
		free(list->arg);
		free(list);
		list = tmp;
	}
}

void	delete_list_var(t_var *list)
{
	t_var *tmp;

	while (list)
	{
		tmp = list->next;
		free(list->name);
		free(list->arg);
		free(list);
		list = tmp;
	}
}

void	delete_list_env_and_var(t_data *data)
{
	delete_list_env(data->env);
	delete_list_var(data->var);
}
