#include <sh21.h>

int 	is_quote_true_open(char car, char *str, int prec)
{
  prec -= 1;
  if (prec >= 0 && str[prec] != '\\')
  {
  	if (car == '\'' || car == '"' || car == '`' || car == '('
  		|| car == '[' || car == '{')
  		return (1);
  }
	return (0);
}

int 	is_quote_true_close(char car, char open, char *str, int  prec)
{
  prec -= 1;
  if (prec >= 0 && str[prec] != '\\')
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
  }
	return (0);
}

// char  *subs_subs(t_data *data, char *str)
// {
//
// }

// char  next_true_char_noquote(char *str, char *open_quote, size_t *i)
// {
//   true_char = '\0';
//   return (true_char);
// }
//
// char  next_true_char_quote(char *str, char *open_quote, size_t *i)
// {
//   true_char = '\0';
//   return (true_char);
// }
//
// char  next_true_char_dquote(char *str, char *open_quote, size_t *i)
// {
//   true_char = '\0';
//   return (true_char);
// }

// char  next_true_char(char *str, char open_quote)
// {
//   char    true_char;
//   size_t  index;
//
//   true_char = '\0';
//   index = 0;
//   while (str[index])
//   {
//     if (str[index] == '\\')
//     {
//       if (str[index + 1] == '\0')
//         return (true_char);
//       else if ()
//       index += 2;
//     }
//   }
//   return (true_char);
// }

char *delete_var(char *str, size_t index, size_t length, char *arg)
{
  char *new_str;

  printf("IN DELETE VAR :\n");
  if (index > 0)
    new_str = ft_strsub(str, 0, index - 1);
  else
    new_str = ft_strdup("");
  printf("sub = [%s]\n", new_str);
  printf("After var --> [%s]\n", str + length);
  new_str = ft_strjoinaf1(new_str, str + length);
  free(str);
  free(arg);
  return(new_str);
}

char *delete_var_and_replace(char *str, size_t index, size_t length, char *arg)
{
  char *new_str;

  if (index > 0)
    new_str = ft_strsub(str, 0, index - 1);
  else
    new_str = ft_strdup("");
  new_str = ft_strjoinaf12(new_str, arg);
  new_str = ft_strjoinaf1(new_str, str + length);
  free(str);
  return (new_str);
}

void   is_var_and_replace(t_data *data, char *str, size_t *index)
{
  size_t  length;
  char    *arg;
  char    tmp_char;

  if ((*index == 0 || str[*index - 1] != '\\') && str[*index] == '$')
  {
    length = *index + 1;
    while (ft_isalnum(str[length]))
      length++;
    tmp_char = str[length];
    str[length] = '\0';
    arg = find_arg(data->env, str + *index + 1); // METTRE find_env_var
    printf("ARG = [%s]\n", arg);
    str[length] = tmp_char;
    if (length - (*index + 1) == 0)
    {
      free(arg);
      return ;
    }
    if (ft_strequ(arg, ""))
    {
      str = delete_var(str, *index + 1, length, arg);
      printf("IN VAR REPLACE --> str = [%s]\n", str);
    }
    else
    {
      str = delete_var_and_replace(str, *index, length, arg);
    }
    (*index)--;
  }
}

char   *find_subs_in_parsing(t_data *data, char *str, size_t length)
{
  t_history   *list;
  char        *arg;
  char        *pattern;
  int         len;

  if (data->history == NULL)
    return (NULL);
  list = data->history;
  arg = NULL;
  length -= 1;
  pattern = ft_strsub(str, 0, length);
  len = (int)ft_strlen(pattern);
  while (list)
  {
    if (ft_strnequ(pattern, list->line, len))
    {
      free(pattern);
      return (ft_strdup(list->line));
    }
    list = list->prec;
  }
  free(pattern);
  return (arg);
}

void delete_subs_and_replace(char *str, size_t index, size_t length, char *arg)
{
  char *new_str;

  new_str = ft_strsub(str, 0, index);
  new_str = ft_strjoinaf12(new_str, arg);
  new_str = ft_strjoinaf1(new_str, str + length);
  free(str);
  str = new_str;
}

int   is_subs_and_replace(t_data *data, char *str, size_t *index, int flag)
{
  size_t  length;
  char    *arg;
  // int     line_number;
  int     flag_special;

  length = *index;
  flag_special = 0;
  data->flag_enter = 1;
  if ((*index == 0 || str[*index - 1] != '\\') && str[*index] == '!')
  {
    if (str[length] == '!')
    {
      if (data->history != NULL)
        arg = ft_strdup(data->history->line);
      else
        return (0);
      length++;
      flag_special = 1; // Flag pour dire "!!"
    }
    else if (ft_isdigit(str[length]))
    {
      while (ft_isdigit(str[length]))
        length++;
      // line_number = ft_atoi(str + *index + 1);
      if ((arg = history_subsitution_nb_arg_ps(data, str + *index + 1)) == NULL)
        return (0);
      flag_special = 2; //Flag pour dire "!n"
    }
    else
    {
      if (flag == 0)
      {
        while (ft_isspace2(str[length]) == 0 && str[length])
          length++;
      }
      else if (flag == 1)
      {
        while (ft_isspace2(str[length]) == 0 && str[length] != '"' && str[length])
          length++;
      }
      if (length - (*index + 1) == 0)
      {
        ft_putstr_fd("42sh: incorrect pattern for '!'\n", 2);
        return (0);
      }
      if ((arg = find_subs_in_parsing(data, str + *index + 1, length)) == NULL)
        return (0);
    }
    delete_subs_and_replace(str, *index, length, arg);
    (*index)--;
    data->flag_enter = 0;
  }
  return (1); // NE PAS OUBLIER DE REMETTRE LE BON INDEX
}

int   true_var_and_subs(t_data *data, char *str)
{
  // char    *new_str;
  size_t  index;
  char    open_quote;
  size_t  tmp_index; // flag qui sert a ne passer qu'une fois dans is_var et is_subs si un des deux est ok + reanalyser le premier caractere de la chaine obtenue
  size_t  first_true_char;

  // old_str = ft_strdup(*str);
  index = 0;
  open_quote = '\0';
  while (str[index])
  {
    while (ft_isspace2(str[index]))
			index++;
    first_true_char = 0;
    while (ft_isspace2(str[index]) == 0 && str[index])
    {
      tmp_index = index;
      if (open_quote != '\0' && is_quote_true_open(str[index], str, index))
      {
        open_quote = str[index];
      }
      else if (open_quote && is_quote_true_close(str[index], open_quote, str, index))
      {
        open_quote = '\0';
      }
      else if (open_quote == '\0')
      {
        if (is_subs_and_replace(data, str, &index, 0) == 0)
          return (0);
        if (data->flag_enter)
          is_var_and_replace(data, str, &index);
      }
      else if (open_quote == '"')
      {
        if (is_subs_and_replace(data, str, &index, 1) == 0)
          return (0);
        if (data->flag_enter)
          is_var_and_replace(data, str, &index);
      }
      index++;
    }
  }
  return (1);
}
