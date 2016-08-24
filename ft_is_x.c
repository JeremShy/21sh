#include <sh21.h>

int		is_empty_border(char *str, size_t beg, size_t end)
{
	size_t i;

	// printf("coord : %zu et %zu. Chaine : [%s]\n", beg, end, str);
	i = beg;
	while(str[i] != '\0' && i <= end)
	{
		if (!ft_isspace2(str[i]))
			return(0);
		i++;
	}
	return (1);
}

int		there_is_a_pipe_or_an_et_that_is_not_supposed_to_be(char *str, int index)
{
	while (str[index] && ft_isspace2(str[index]))
		index++;
	if (str[index] == '|' || str[index] == '&')
		return (1);
	return (0);
}

int		is_pipe_e_parse_error(char *str)
{
	size_t	i;
	int			first_char;
	int			last_spe_char;

	i = 0;
	first_char = 1;
	last_spe_char = 0;
	while (str[i])
	{
		// printf("str[i] : %c\n", str[i]);
		while (ft_isspace2(str[i]))
			i++;
		if (!str[i])
			continue ;
		else if (is_aggr(&i, str, 1))
		{
			// printf("Just do it !\n");
		}
		else if (!is_escaped_char(str, i) && ((str[i] == '&' && str[i + 1] != '&') || ft_strnequ(str + i, "&&", 2) || str[i] == '|' || ft_strnequ(str + i, "||", 2)))
		{
			if (first_char || (str[i + 1] && str[i + 2] &&
				there_is_a_pipe_or_an_et_that_is_not_supposed_to_be(str, i + 2)))
			{
				ft_putstr_fd("42sh: parse error near '|' or '&'\n", 2);
				return (1);
			}
			else if (ft_strnequ(str + i, "&&", 2) || ft_strnequ(str + i, "||", 2))
				i++;
			i++;
			last_spe_char = 1;
		}
		else
		{
			i++;
			first_char = 0;
			last_spe_char = 0;
		}
	}
	if (last_spe_char)
	{
		ft_putstr_fd("42sh: parse error near '|' or '&'\n", 2);
		return (1);
	}
	return (0);
	// 	if ((first_char || last_char) && (ft_strnequ(str + i, "& ", 2) || ft_strnequ(str + i, "&&", 2) || str[i] = '|')
	// 	{
	// 		ft_putstr_fd("42sh: parse error near '|' or '&'\n", 2);
	// 		return (1);
	// 	}
	// 		if (str[])
	// 		i += 2;
	// 		while (ft_isspace2(str[i]))
	// 			i++;
	// 		if (!str[i] || first_char)
	// 		{
	// 			ft_putstr_fd("42sh: parse error near '&'\n", 2);
	// 			return (1);
	// 		}
	// 		first_char = 0;
	// 	}
	// 	i++;
	// }
	// return (0);
}

int	is_parse_error(char *str)
{
	size_t i;
	int			there_is_a_pipe;
	int			flag;

	i = 0;
	// printf("ON ENVOIE [%s]\n", str);
	there_is_a_pipe = 0;
	while (str[i])
	{
		flag = 0;
		while (ft_isspace2(str[i]))
		{
			flag = 1;
			i++;
		}
		if (((str[i] == '|' || str[i] == '&') && flag) || (str[i] == '\0' && there_is_a_pipe))
		{
			ft_putstr("121sh: parse error near '| or '&'\n");
			// printf("str[i] = %c\n\n", str[i]);
			return (1);
 		}
		if (str[i] == '|')
		{
			i++;
			while (ft_isspace2(str[i]))
				i++;
			if (str[i] == '|' || !str[i])
			{
				ft_putstr("521sh: parse error near '|'\n");
				return (1);
			}
		}
		while (str[i] != '|' && str[i] != '\0')
		{
			if (is_quote_open(str[i]))
				get_pos_after_quote(&i, str);
			else
				i++;
		}
		there_is_a_pipe = 1;
		if (str[i])
			i++;
	}
	// if (is_eeerror(str))
	// 	return (1);
	return (0);
}

int		is_empty(char *str, size_t *i)
{
	size_t tmp;

	tmp = *i;
	while(str[tmp] != '\0')
	{
		if(!ft_isspace2(str[tmp]))
			return(0);
		tmp++;
	}
	return(1);
}

int is_special(char *str, int quote)
{
	if (quote == 1)
		str++;
	if (ft_strnstr(str, ">>", 2) || ft_strnstr(str, "<<", 2) || ft_strnstr(str, "&&", 2) || ft_strnstr(str, "2>", 2) || ft_strnstr(str, "2>>", 3) || str[0] == '|' || str[0] == '>' || str[0] == '<' || str[0] == ';')
		return (1);
	return (0);
}

int	ft_isspace2(char car)
{
	if (car == ' ' || car == '\t' || car == '\v' || car == '\f' || car == '\r')
		return (1);
	return (0);
}
