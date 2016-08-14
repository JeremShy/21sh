#include <sh21.h>

int			ft_export(char **scmd, t_env **env)
{
	char *arg;

	if (!scmd[1])
		return (0);
	arg = scmd[2];
	if (!arg)
		arg = ft_strdup("");
	if (isset_arg(*env, scmd[1]))
		change_arg(*env, scmd[1], arg);
	else
		*env = add_elem_end(*env, scmd[1], arg);
	return (1);
}
