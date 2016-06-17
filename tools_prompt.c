/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:54:32 by adomingu          #+#    #+#             */
/*   Updated: 2016/06/17 18:18:36 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	prompt_quote(t_data *data)
{
	if (data->c == '\'')
		data->prompt = ft_strdup("quote> ");
	else if (data->c == '"')
		data->prompt = ft_strdup("dquote> ");
	else if (data->c == '`')
		data->prompt = ft_strdup("bquote> ");
	else if (data->c == '(')
		data->prompt = ft_strdup("subsh> ");
	else if (data->c == '[')
		data->prompt = ft_strdup("crochet> ");
	else if (data->c == '{')
		data->prompt = ft_strdup("cursh> ");
	else if (data->c == '<')
		data->prompt = ft_strdup("heredoc> ");
	ft_putstr(data->prompt);
}

char  *create_prompt(t_env *env, char *tmp, char *new)
{
  char  *prompt;

  if (ft_strequ(new, ""))
  {
    free(new);
    new = find_arg(env, "PROMPT");
    new = getcwd(NULL, 0);
    if (!new)
    {
      tmp = find_arg(env, "HOME");
      if (ft_strequ(tmp, ""))
      tmp = ft_strjoinaf1(tmp, "/");
      change_arg(env, "PWD", tmp);
      chdir(tmp);
      new = getcwd(NULL, 0);
      free(tmp);
    }
    prompt = ft_strdup("<");
    prompt = ft_strjoinaf12(prompt, new);
    prompt = ft_strjoinaf1(prompt, ">% ");
  }
  else
    prompt = new;
  return (prompt);
}

char	*print_prompt(t_env *env, t_data *data)
{
	char	*tmp;
	char	*prompt;

  tmp = NULL;
  prompt = NULL;
	ft_putstr("\e[38;5;208m");
	if (data->c != '\0')
	{
		prompt_quote(data);
		ft_putstr("\e[39m");
		return (data->prompt);
	}
  prompt = find_arg(env, "PROMPT");
  prompt = create_prompt(env, tmp, prompt);
	ft_putstr(prompt);
	ft_putstr("\e[39m");
	return (prompt);
}
