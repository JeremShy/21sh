/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:34:18 by jcamhi            #+#    #+#             */
/*   Updated: 2015/12/17 18:09:07 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_list	*ft_lstdict(t_list *lst, const int n)
{
	while (lst)
	{
		if (lst->content_size == (size_t)n)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static	char	*handle_first_buff(t_list *prec)
{
	int		i;
	char	*ret;

	i = 0;
	if (!prec->content)
		return (NULL);
	while (((char*)prec->content)[i] != '\n' &&
			((char*)prec->content)[i] != '\0')
		i++;
	if (((char*)prec->content)[i] == '\n')
	{
		if (i == 0)
		{
			ret = ft_strdup((char*)prec->content + 1);
			prec->content = (void*)ft_strdup(ret);
			ret = ft_memalloc(1);
		}
		else
		{
			ret = ft_strsub((char*)prec->content, 0, i);
			prec->content = (void*)((char*)prec->content + i + 1);
		}
		return (ret);
	}
	return (NULL);
}

static int		handle_buffer(t_list *prec, char **ret, int fd, int *r)
{
	int		i;
	char	buff[BUFF_SIZE + 1];

	i = -1;
	while ((*r = read(fd, buff, BUFF_SIZE)) && *r != -1)
	{
		i = 0;
		buff[*r] = '\0';
		while (buff[i] != '\0')
		{
			if (buff[i] == '\n')
			{
				buff[i] = '\0';
				*ret = ft_strjoin(*ret, buff);
				prec->content = (void*)ft_strdup(buff + i + 1);
				return (1);
			}
			i++;
		}
		*ret = ft_strjoin(*ret, buff);
	}
	if (i == -1 || *r == -1)
		return (-1);
	return (0);
}

static	char	*read_one_line(t_list *prec, int const fd, int *r)
{
	int		i;
	char	*ret;

	if ((ret = handle_first_buff(prec)))
		return (ret);
	ret = ft_strjoin("", (char*)prec->content);
	i = handle_buffer(prec, &ret, fd, r);
	if (*r == -1)
		return (NULL);
	if (i == 1)
		return (ret);
	if (i != -1)
	{
		prec->content = "";
		return (ret);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*maillon;
	int				r;

	maillon = NULL;
	if (fd < 0 || !line)
		return (-1);
	if (list == NULL)
		list = ft_lstnew("", fd);
	maillon = ft_lstdict(list, fd);
	if (!maillon)
	{
		maillon = ft_lstnew("", fd);
		ft_lstadd(&list, maillon);
	}
	*line = read_one_line(maillon, fd, &r);
	if (r == -1)
		return (-1);
	if (*line == NULL)
		return (0);
	return (1);
}
