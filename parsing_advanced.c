#include <sh21.h>

int   is_escaped_char(char *str, int index)
{
  int ret;

  ret = 0;
  index--;
  while (index >= 0 && str[index] == '\\')
    {
    ret++;
    index--;
  }
  return (ret % 2);
}

int 	is_quote_true_open(char car, char *str, int prec)
{
  if (!is_escaped_char(str, prec))
  {
  	if (car == '\'' || car == '"' || car == '`' || car == '('
  		|| car == '[' || car == '{')
  		return (1);
  }
	return (0);
}

int 	is_quote_true_close(char car, char open, char *str, int  prec)
{
  if (!is_escaped_char(str, prec))
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

int  delete_var(char **str, size_t index, size_t length, char *arg)
{
  char *new_str;

  printf("IN DELETE VAR :\n");
  if (index > 0)
    new_str = ft_strsub(*str, 0, index - 1);
  else
    new_str = ft_strdup("");
  printf("sub = [%s]\n", new_str);
  printf("After var --> [%s]\n", (*str) + length);
  new_str = ft_strjoinaf1(new_str, (*str) + length);
  free(*str);
  free(arg);
  *str = new_str;
  return (1);
}

char  *arg_add_backslash(char *arg)
{
  size_t  count;
  int     i;
  char    *ret;
  int     j;

  i = 0;
  count = 0;
  while (arg[i])
  {
    if (is_quote(arg[i]) || arg[i] == '$' || arg[i] == '!' || arg[i] == '\\')
      count++;
    count++;
    i++;
  }
  ret = malloc(sizeof(char) * (count + 1));
  i = 0;
  j = 0;
  while (arg[i])
  {
    if (is_quote(arg[i]) || arg[i] == '$' || arg[i] == '!' || arg[i] == '\\')
    {
      ret[j] = '\\';
      j++;
    }
    ret[j] = arg[i];
    j++;
    i++;
  }
  free(arg);
  ret[j] = '\0';
  return (ret);
}

int   delete_var_and_replace(char **str, size_t index, size_t length, char *arg)
{
  char     *new_str;
  size_t   real_length;

  if (index > 0)
    new_str = ft_strsub(*str, 0, index);
  else
    new_str = ft_strdup("");
  printf("arg = [%s] // *str = [%s]\n", arg, *str);
  arg = arg_add_backslash(arg);
  real_length = ft_strlen(arg);
  new_str = ft_strjoinaf12(new_str, arg);
  new_str = ft_strjoinaf1(new_str, (*str) + length);
  free(*str);
  *str = new_str;
  return(real_length);
}

void   is_var_and_replace(t_data *data, char **str, size_t *index)
{
  size_t  length;
  char    *arg;
  char    tmp_char;
  size_t  real_length; // Length de la variable ajouté avec ou non backslash

  if (!is_escaped_char(*str, *index) && (*str)[*index] == '$')
  {
    length = *index + 1;
    while (ft_isalnum((*str)[length]))
      length++;
    tmp_char = (*str)[length];
    (*str)[length] = '\0';
    arg = find_arg(data->env, *str + *index + 1); // METTRE find_env_var
    printf("ARG = [%s]\n", arg);
    (*str)[length] = tmp_char;
    if (length - (*index + 1) == 0)
    {
      free(arg);
      return ;
    }
    if (ft_strequ(arg, ""))
    {
      real_length = delete_var(str, *index + 1, length, arg);
      printf("str = [%s]\n", *str);
    }
    else
    {
      real_length = delete_var_and_replace(str, *index, length, arg);
      printf("str = [%s]\n", *str);
    }
    *index = length - (*index + 1);
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
  // length -= 1;
  pattern = ft_strsub(str, 0, length);
  // printf("pattern : [%s]\n", pattern);
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

void delete_subs_and_replace(char **str, size_t index, size_t length, char *arg)
{
  char *new_str;

  // printf("str [%s] - str[index] : %c - length : %zu - arg : [%s]\n", (*str), (*str)[index], length, arg);
  if (index > 0)
    new_str = ft_strsub(*str, 0, index);
  else
    new_str = ft_strdup("");
  // printf("arg = [%s] // *str = [%s]\n", arg, *str + length);
  new_str = ft_strjoinaf12(new_str, arg);
  new_str = ft_strjoinaf1(new_str, *str + length);
  free(*str);
  *str = new_str;
  // printf("NEW STRING = [%s]\n", *str);
}

int   is_subs_and_replace(t_data *data, char **str, size_t *index, int flag)
{
  size_t  length;
  char    *arg;
  // int     line_number;
  int     flag_special;

  length = *index + 1;
  flag_special = 0;
  data->flag_enter = 1;
  if (!is_escaped_char(*str, *index) && (*str)[*index] == '!')
  {
    if ((*str)[length] == '!')
    {
      if (data->history != NULL)
        arg = ft_strdup(data->history->line);
      else
        return (0);
      length++;
      flag_special = 1; // Flag pour dire "!!"
    }
    else if (ft_isdigit((*str)[length]))
    {
      while (ft_isdigit((*str)[length]))
        length++;
      // line_number = ft_atoi(str + *index + 1);
      if ((arg = history_subsitution_nb_arg_ps(data, *str + *index + 1)) == NULL) // On récupere la ligne correspondant au n et si pas valide, return NULL
        return (0);
      flag_special = 2; //Flag pour dire "!n"
    }
    else
    {
      if (flag == 0) // Yapadkot
      {
        while (ft_isspace2((*str)[length]) == 0 && (*str)[length])
          length++;
      }
      else if (flag == 1)
      {
        while (ft_isspace2((*str)[length]) == 0 && (*str)[length] != '"' && (*str)[length]) // Yadékot
          length++;
      }
      if (length - (*index + 1) == 0)
      {
        ft_putstr_fd("42sh: incorrect pattern for '!'\n", 2);
        return (0);
      }
      if ((arg = find_subs_in_parsing(data, *str + *index + 1, length - (*index + 1))) == NULL)
        return (0);
    }
    delete_subs_and_replace(str, *index, length, arg);
    (*index)--;
    data->flag_enter = 0;
  }
  return (1); // NE PAS OUBLIER DE REMETTRE LE BON INDEX
}

int   true_var_and_subs(t_data *data, char **str)
{
  // char    *new_str;
  size_t  index;
  char    open_quote;
  size_t  tmp_index; // flag qui sert a ne passer qu'une fois dans is_var et is_subs si un des deux est ok + reanalyser le premier caractere de la chaine obtenue
  size_t  first_true_char;

  // old_str = ft_strdup(*str);
  index = 0;
  open_quote = '\0';
  while ((*str)[index])
  {
    while (ft_isspace2((*str)[index]))
			index++;
    first_true_char = 0;
    while (!ft_isspace2((*str)[index]) && (*str)[index])
    {
      tmp_index = index;
      if (open_quote == '\0' && is_quote_true_open((*str)[index], *str, index)) // Si on tombe sur une quote pas echappée
      {
        open_quote = (*str)[index];
      }
      else if (open_quote != '\0' && is_quote_true_close((*str)[index], open_quote, *str, index)) // Si on tombe sur une fermeture pas echappée
      {
        open_quote = '\0';
      }
      else if (open_quote == '\0') // Variables hors d'une quote
      {
        if (is_subs_and_replace(data, str, &index, 0) == 0)
          return (0);
        if (data->flag_enter) // sert a ne pas entrer dans is_var si on est entré dans is_subs
          is_var_and_replace(data, str, &index);
      }
      else if (open_quote == '"') // Variables dans une quote
      {
        if (is_subs_and_replace(data, str, &index, 1) == 0)
          return (0);
        if (data->flag_enter) // sert a ne pas entrer dans is_var si on est entré dans is_subs
          is_var_and_replace(data, str, &index);
      }
      index++;
    }
  }
  return (1);
}
