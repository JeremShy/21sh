#include <sh21.h>

int			is_physical(char *str)
{
	if (ft_strcmp("-P", str) == 0)
		return (1);
	return (0);
}

int			is_logical(char *str)
{
	if (ft_strcmp("-L", str) == 0)
		return (1);
	return (0);
}

int			is_minus(char *str)
{
	if (ft_strcmp("-", str) == 0)
		return (1);
	return (0);
}

int			is_legal_options(char **str, t_cmd *cmd, t_data *data)
{
	int		ret;

	ret = operate_legal_opts(str, cmd, data);
	if (ret == 0)
	{
		putstr_builtin(cmd, "cd: usage: cd [-L OR -P] [dir]\n", 2);
		data->cd_ret = 1;
		return (0);
	}
	if (ret == -1)
	{
		data->cd_ret = 1;
		return (0);
	}
	return (1);
}
