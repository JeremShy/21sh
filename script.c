#include "libft.h"
#include "script.h"
#include <stdio.h>

t_line *create_line_elem (char *content)
{
	t_line	*elem;

	elem = malloc(sizeof(t_line));
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_line 	*add_line_elem(t_line *list, t_line *elem)
{
	t_line *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
  		list = list->next;
	list->next = elem;
	return (tmp);
}

int 	is_quote_close(char car, char open)
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

int 	is_quote_open(char car)
{
	if (car == '\'' || car == '"' || car == '`' || car == '('
		|| car == '[' || car == '{')
		return (1);
	return (0);
}


int	ft_isspace(char car)
{
	if (car == ' ' || car == '\t' || car == '\v' || car == '\f' || car == '\r')
		return (1);
	return (0);
}

char 	*get_string_malloc(char *str)
{
	size_t	i;
	char		*sub;

	i = 0;
	if (str[i] == '\0' || ft_isspace(str[i]))
	{
		return (NULL);
	}
	if (is_quote_open(str[i]))
	{
		i++;
		while (str[i] != str[0] && str[i])
			i++;
		sub = ft_strsub(str, 1, i - 1);
	}
	else
	{
		while (!(ft_isspace(str[i]) && str[i]))
			i++;
		sub = ft_strsub(str, 0, i);
	}
	return (sub);
}

void get_alias(char *str)
{
  size_t   i;
  char     *arg;

  i = 0;

	if ((arg = get_string_malloc(str)) == NULL)
	{
		ft_putstr("Unvalid alias (usage: alias=\"command\")\n");
		return ;
	}
  // if (str[i] == '\0' || ft_isspace(str[i]))
  // {
  //   ft_putstr("Unvalid alias (usage: alias=\"command\")\n");
  //   return ;
  // }
  // if (is_quote_open(str[i]))
  // {
  //   i++;
  //   while (str[i] != str[0] && str[i])
  //     i++;
  //   arg = ft_strsub(str, 1, i - 1);
  // }
  // else
  // {
  //   while (!(ft_isspace(str[i]) && str[i]))
  //     i++;
  //   arg = ft_strsub(str, 0, i);
  // }
  printf("alias = [%s]\n", arg);
  		// --> ADD ARG !!!!!!!!
}

void str_or_number(char *key, char *var)
{
  size_t  i;

  i = 0;

  if (var[i] == '-' || var[i] == '+')
    i++;
  while (ft_isdigit(var[i]))
    i++;
  if (var[i])
    // ADD VARIABLE STRING
    printf("Variable is a string ! key = [%s] --> [%s]\n", key, var);
  else
    // ADD VARIABLE NUMBER
    printf("Variable is a int ! key = [%s] --> [%d]\n", key, (int)ft_atoi(var));
	// FAIRE LE TEST POUR VOIR SI C'EST TRUE OU FALSE ?
}

int str_or_number_type(char *key, char *var)
{
  size_t  i;

  i = 0;

  if (var[i] == '-' || var[i] == '+')
    i++;
  while (ft_isdigit(var[i]))
    i++;
  if (var[i])
		return (0);
  else
    return (1);
	// FAIRE LE TEST POUR VOIR SI C'EST TRUE OU FALSE ?
}

void get_variable(char *key, char *str)
{
  size_t  i;
  char    *var;

  i = 0;
	if ((var = get_string_malloc(str)) == NULL)
	{
		// ADD THE VALUE NULL
		return ;
	}
  // if (str[i] == '\0' || ft_isspace(str[i]))
  // {
  //   // ADD THE VALUE NULL
  //   //ft_putstr("Unvalid variable (usage: name=value)\n");
  //   return ;
  // }
  // if (is_quote_open(str[i]))
  // {
  //   i++;
  //   while (str[i] != str[0] && str[i])
  //     i++;
  //   var = ft_strsub(str, 1, i - 1);
  // }
  // else
  // {
  //   while (!(ft_isspace(str[i]) && str[i]))
  //     i++;
  //   var = ft_strsub(str, 0, i);
  // }
  printf("variable = [%s]\n", var);
  str_or_number(key, var);
}

int  is_variable(char *str, size_t *i)
{
  size_t  j;

  j = *i;
  while (!(ft_isspace(str[*i]) && str[*i]) && str[*i] != '=')
    (*i)++;
  if (str[*i] == '=')
  {
    (*i)++;
    return (1);
  }
  *i = j;
  return (0);
}

void get_if(char *str)
{
	// char	*arg1;
	// int		value_int;
	// char	*value_str;
	// liste		exist;
	//
	// if ((arg1 = get_string_malloc(str)) == NULL)
	// {
	// 	ft_putstr("42sh: invalid if (usage: if [ value1 == value2 ]\n)");
	// 	return ;
	// }
	// exist = search_key(arg1);
	// if (exist)
	// {
	// 	free(arg1);
	// 	list_script->add_element(exist);
	// }
	// 	}
	// }

}

void analyse_line(char *line)
{
  size_t  i;
  size_t  tmp;

  i = 0;
  printf("----------------------------\n");//STRING ANALYSED --> [%s]\n", line);
  while (ft_isspace(line[i]))
    i++;
  if (!(line[i]) || line[i] == ';' || line[i] == '=' )
    return ;
  printf("ANALYSING LINE ...... [%s]\n", line);
  tmp = i;
  if (ft_strncmp("alias=", line + i, 6) == 0)
  {
    printf("ALIAS DETECTED !\n");
    get_alias(line + i + 6);
    // AJOUTER DANS LISTE CHAINE
  }
  else if (is_variable(line, &i))
  {
    printf("VARIABLE DETECTED !\n");
    get_variable(ft_strsub(line, tmp, i - tmp - 1), line + i);
  }
	else if (ft_strequ("if [ ", line))
	{
		printf("IF DETECTED\n");
		get_if(line + 4);
	}
}

int		is_quote_end2(char *str)
{
	size_t	i;
  char    open;

  i = 0;
  open = '\0';
  while (str[i])
  {
    if (open == '\0')
    {
      if (is_quote_open(str[i]))
      {
        open = str[i];
      }
    }
    else if (is_quote_close(open, str[i]))
    {
      open = '\0';
    }
    i++;
  }
  if (open == '\0')
    return (0);
  else
    return (1);
}

int		read_file(char *file, t_line *)
{
	size_t   file_name_len;
  int      fd;
  char     *str;
  int      first_line;

  printf("%s\n", file);
  file_name_len = ft_strlen(file);
  if (file_name_len < 4)
    return(0); // Si le nom est plus court ou egal a ".sh"
  if (!(fd = open(file, O_RDONLY)) || !(ft_strequ(file + (file_name_len - 3), ".sh")))
  {
    return (0);
  }
  first_line = 1;
  str = NULL;
  while (get_next_line(fd, &str) == 1)
  {
    if (first_line == 1)
    {
      if (!(ft_strequ("#!42sh", str)))
      {
        ft_putstr("42SH: script not made for 42sh\n");
        free(str);
        return (0);
      }
      free(str);
      first_line = 0;
      continue ;
    }
		line = add_line_elem(line, create_line_elem(str)); // On rajoute la ligne dans l'historique.
    free(str);
  }
	if (is_quote_end2(str))
		ft_putstr("String have open quotes non terminated (flemme de faire tous les cas speciaux, il s'agit d'un bonus)\n");
	else
		analyse_line(str);
  if (close(fd) == -1)
  {
    ft_putstr("Fail to close file script\n");
    exit(0);
  }
  return (0);
}

int			main(int ac, char **av, char **env)
{
	t_line	*line;

	*line = NULL;
  read_file("SHELL.sh", line);

  exit(0);
  char    car = 'c';
  char    *str = "Hello !";
  int     n_int = 3;
  size_t  n_size_t = 697;

  printf("sizeof char = %lu /// str = %lu /// n_int = %lu /// n_size_t = %lu\n", sizeof(car), sizeof(str), sizeof(n_int), sizeof(n_size_t));
  return (0);
}
