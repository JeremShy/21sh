#include <sh21.h>

t_auto *create_auto_elem (char *content)
{
	t_auto 	*elem;

	elem = malloc(sizeof(t_auto));
	elem->str = content;
	elem->next = NULL;
	return (elem);
}

t_auto 	*add_auto_elem(t_auto *list, t_auto *elem)
{
	t_auto *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (tmp);
}

static void    	init_autocomplete(t_data *data, char **split, char *str_to_equ, char *prefix) // Prends data, un tableau ave les dossiers a parcourir, et le debut de truc a complete, et le prefixe
{
	int    		i;
	DIR    		*directory;
	t_dirent       	*truc;

	i = 0;
	// printf("split[0] = [%s] /// prefix = [%s] // str to equ = [%s]\n", split[0], prefix, str_to_equ);
	while (split[i])
	{
		directory = opendir(split[i]);
		while (directory && (truc = readdir(directory)))
		{
			if (ft_strnequ(truc->d_name, str_to_equ, ft_strlen(str_to_equ)) && !ft_strequ(truc->d_name, ".") && !ft_strequ(truc->d_name, ".."))
			{
				data->list_auto = add_auto_elem(data->list_auto, create_auto_elem(ft_strjoinaf2(prefix, ft_strdup(truc->d_name))));
				// printf("adding : [%s]\n", truc->d_name);
			}
		}
		if (directory)
			closedir(directory);
		i++;
	}
	free(str_to_equ);
	free(prefix);
}


void   	jump_all_quote_for_arg(char *str, size_t *i)
{
	char   		open_quote;
	size_t 	begin_quote;

	// printf("FIRST CHAR = '%c'\n", str[*i]);
	while (ft_isspace2(str[*i]) == 0 && str[*i] && !is_sep(i, str, 0, NULL))
	{
		if (is_quote_open(str[*i]))
		{
			open_quote = str[*i];
			get_pos_after_quote(i, str);
			begin_quote = *i;
			// printf("char after quote = [%c]\n", str[*i]);
			(*i)++;
			// printf("car = '%c'\n", str[*i]);
		}
		else
			(*i)++;
	}
	// printf("END CHAR = '%c'\n", str[*i - 1]);
}

int    		is_empty_border_in_actual_cmd(char *str, size_t i)
{
	// if (!str[i] && i > 0)
	while (i > 0 && !is_sep(&i, str, 1, NULL))
		i--;
	while (ft_isspace2(str[i]))
		i++;
	if (!str[i] || is_sep(&i, str, 0, NULL))
		return (1);
	return (0);
}

void ft_autocomplete(t_data *data)
{
}
