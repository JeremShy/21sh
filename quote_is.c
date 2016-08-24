#include <sh21.h>

int			is_quote(char car)
{
	if (car == '\'' || car == '"' || car == '`' || car == '(' || car == ')'
			|| car == '[' || car == ']' || car == '{' || car == '}')
		return (1);
	return (0);
}

int			is_quote_open(char car)
{
	if (car == '\'' || car == '"' || car == '`' || car == '('
			|| car == '[' || car == '{')
		return (1);
	return (0);
}

int			is_quote_close(char car, char open)
{
	if (car == '\'' && open == '\'')
		return (1);
	else if (car == '"' && open == '"')
		return (1);
	else if (car == '`' && open == '`')
		return (1);
	else if (car == '(' && open == ')')
		return (1);
	else if (car == '[' && open == ']')
		return (1);
	else if (car == '{' && open == '}')
		return (1);
	return (0);
}
