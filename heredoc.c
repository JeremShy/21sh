#include <sh21.h>

int	is_key(t_data *data)
{
	if (ft_strequ(data->cmd, data->key_here))
		return (1);
	return (0);
}
