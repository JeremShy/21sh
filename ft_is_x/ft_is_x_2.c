#include <sh21.h>

static int	pipe_error_print(void)
{
	ft_putstr_fd("42sh: parse error near '|' or '&'\n", 2);
	return (1);
}

static void	is_pipe_error_default_else(size_t *i,
	int *first_char, int *last_spe_char)
{
	(*i)++;
	*first_char = 0;
	*last_spe_char = 0;
}

static void	jump_space(char *str, size_t *i)
{
	while (ft_isspace2(str[*i]))
		(*i)++;
}

static void	is_pipe_error_end_of_if(size_t *i, int *last_spe_char)
{
	(*i)++;
	*last_spe_char = 1;
}

int			is_pipe_error(char *s, size_t i, int first_char, int last_spe_char)
{
	while (s[i])
	{
		jump_space(s, &i);
		if (!s[i])
			break ;
		else if (is_aggr(&i, s, 1))
		{
		}
		else if (!is_escaped_char(s, i) && ((s[i] == '&' && s[i + 1] != '&')
		|| ft_strnequ(s + i, "&&", 2) || s[i] == '|'
		|| ft_strnequ(s + i, "||", 2)))
		{
			if (first_char || (s[i + 1] && s[i + 2] &&
				is_wrong_pipe(s, i + 2)))
				return (pipe_error_print());
			else if (ft_strnequ(s + i, "&&", 2) || ft_strnequ(s + i, "||", 2))
				i++;
			is_pipe_error_end_of_if(&i, &last_spe_char);
		}
		else
			is_pipe_error_default_else(&i, &first_char, &last_spe_char);
	}
	if (last_spe_char)
		return (pipe_error_print());
	return (0);
}
