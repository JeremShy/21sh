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

// void	get_pos_after_quote_auto(size_t *i, char *str)
// {
// 	char open;
//
// 	open = str[*i];
// 	while (str[*i + 1] && !(is_quote_close(open, str[*i + 1]) && !is_escaped_char(str, *i + 1)))
// 		(*i)++;
// 	if (str[*i])
// 		(*i)++;
// }


void   	jump_all_quote_for_arg(char *str, size_t *i)
{
	// char   		open_quote;
	// size_t 	begin_quote;

	// printf("FIRST CHAR = '%c'\n", str[*i]);
	while (str[*i] && !ft_isspace2(str[*i]) && !is_sep(i, str, 0, NULL))
	{
		if (is_quote_open(str[*i]))
		{
			// open_quote = str[*i];
			get_pos_after_quote(i, str);
			if (str[*i])
				(*i)++;
			// begin_quote = *i;
			// printf("char after quote = [%c]\n", str[*i]);
			// printf("car = '%c'\n", str[*i]);
		}
		else
			(*i)++;
	}
	// printf("END CHAR = '%c' && index = %zu\n", str[*i - 1], *i);
}

char   	*find_ptr(char *cmd)
{
	size_t 	i;

	i = ft_strlen(cmd);
	if (i)
		i--;
	// printf("Un : [%s]\n", cmd + i);
	while (i > 0 && !ft_isspace2(cmd[i]) && !is_sep(&i, cmd, 0, NULL))
		i--;
	// printf("cmd[i]: %c - i : %zu\n", cmd[i], i);
	// printf("Deux : [%s]\n", cmd + i);
	if (!ft_isspace2(cmd[i]) && i == 0)
	{
		// DO NOTHING
	}
	else if (!is_sep(&i, cmd, 1, NULL) && !is_sep(&i, cmd, 0, NULL) && cmd[i] && cmd[i + 1])
		i++;
	while (is_sep(&i, cmd, 1, NULL))
		i++;
	if (cmd[i] == ' ')
	{
		// printf("DUP DE \" \"\n");
		return (cmd + ft_strlen(cmd));
	}
	// printf("Trois : [%s]\n", cmd + i);
	// printf("le pointeur est sur [%c] - %zu\n", (cmd + i)[0] , i);
	return (cmd + i);
}

static int     	is_auto_arg(char *cmd, char **ptr) // Note : ptr est la chaine apres l'espace.
{
	size_t 	i;
	int    			first_word;

	i = 0;
	first_word = 1;
	while (ft_isspace2(cmd[i]))
		i++;
	while (cmd[i])
	{
		while (ft_isspace2(cmd[i]))
		{
			first_word = 0;
			i++;
		}
		if (is_sep(&i, cmd, 1, NULL))
		{
			first_word = 1;
			while (ft_isspace2(cmd[i]))
				i++;
		}
		else if (cmd[i])
		{
			jump_all_quote_for_arg(cmd, &i);
		}
	}
	*ptr = ft_strdup(find_ptr(cmd));
	// if (ft_strequ(*ptr, ""))
	//     	*ptr = NULL;
	// else
	// *ptr = ft_strdup(*ptr);
	// printf("i = %zu [%c] // *ptr = [%s]\n", i, cmd[i], *ptr);
	// printf("ON RENVOIT %d DANS TON RETURN\n", first_word);
	return (!first_word);
}

int    		is_empty_border_between_cmd(char *str)
{
	size_t 	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_isspace2(str[i]))
			i++;
		if (str[i] && !is_sep(&i, str, 0, NULL))
				return (1);
		while (!is_sep(&i, str, 1, NULL))
		{
			while (ft_isspace2(str[i]))
				i++;
			if (is_sep(&i, str, 0, NULL))
				continue ;
			jump_all_quote_for_arg(str, &i);
		}
		if (str[i])
			return (0);
	}
	return (0);
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
	char   	*path;
	char   	**split;
	char   	*ptr;
	char   	*prefix;
	char   	*ptr_for_chr;
	int    		index_to_go;
	char   	*tmp;

	if (!data->list_auto)
	{
		data->absolute_index_before_move = data->index;
		while (data->cmd[data->index] && data->cmd[data->index] != ' ')
		{
			move_right_without_mod(data);
		}
		data->index_before_move = data->index;
		data->absolute_cmd_before_auto = data->cmd;
		data->cmd = ft_strsub(data->cmd, 0, data->index);
		data->absolute_cmd_before_cmd_before_move = ft_strdup(data->cmd);
		if (is_auto_arg(data->cmd, &ptr))
		{
			// printf("premier\n");
			data->index_in_word_before_auto = ft_strlen(ptr);
			split = malloc(sizeof(char*) * 2);
			if ((ptr_for_chr = ft_strrchr(ptr, '/')))  // FICHIER AVEC SLASH
			{
				split[0] = ft_strsub(ptr, 0, ptr_for_chr - ptr + 1);
				prefix = ft_strdup(split[0]);
				tmp = ft_strdup(ptr_for_chr + 1);
				free(ptr);
				// ptr = ft_strdup(ptr_for_chr + 1);
				ptr = tmp;
			}
			else
			{
				// printf("deuxieme\n"); // FICHIER SANS SLASH
				prefix = ft_strdup("");
				split[0] = ft_strdup("./");
			}
			split[1] = NULL;
		}
		else if ((ptr = ft_strrchr(find_ptr(data->cmd), '/')))
		{
			// printf("troisieme\n"); // LA COMMANDE AVEC SLASH
			split = malloc(sizeof(char*) * 2);
			split[0] = ft_strsub(data->cmd, 0, ptr - data->cmd + 1);
			split[1] = NULL;
			// printf("[%s]\n", split[0]);
			// printf("ptr : %s\n", ptr);s
			ptr = ft_strdup(ptr + 1);
			prefix = ft_strdup(split[0]);
			data->index_in_word_before_auto = data->index;
		}
		else
		{
			// printf("quatrieme\n"); // LA COMMANDE SANS SLASH
			path = find_var_env(data, "PATH", data->env);
			if (ft_strequ(path, ""))
			{
				free(path);
				return ;
			}
			split = ft_strsplit(path, ':');
			// ptr = ft_strdup(data->cmd);
			if (find_ptr(data->cmd) > 0)
				ptr = ft_strdup(find_ptr(data->cmd));
			else
				ptr = ft_strdup(data->cmd);
			prefix = ft_strdup("");
			free(path);
			// data->index_in_word_before_auto = data->index;
			if (find_ptr(data->cmd) > 0)
				data->index_in_word_before_auto = data->index_before_move - (find_ptr(data->cmd) - data->cmd);
			else
				data->index_in_word_before_auto = 0;
		}
		init_autocomplete(data, split, ptr, prefix);
	}
	else if (data->list_auto->next)
		data->list_auto = data->list_auto->next;
	if (!data->list_auto)
	{
		index_to_go = data->absolute_index_before_move;
		while (data->index > 0)
			move_left_without_mod(data);
		ft_putstr(data->absolute_cmd_before_auto);
		free(data->cmd);
		data->cmd = data->absolute_cmd_before_auto;
		data->index = ft_strlen(data->cmd);
		while (data->index > index_to_go)
			move_left_without_mod(data);
		data->cmd_before_auto = NULL;
		data->absolute_cmd_before_auto = NULL;
		data->index_before_auto = 0;
		data->index_before_move = 0;
		return ;
	}
	// commentaire qui ne sert à rien
	while (data->index > data->index_before_move)
		move_left_without_mod(data);
	exec_tcap("cd");
	tmp = data->cmd;
	data->cmd = ft_strsub(data->cmd, 0, data->index);
	free(tmp);
	tmp = data->list_auto->str + ft_strlen(find_ptr(data->absolute_cmd_before_cmd_before_move));
	ft_putstr(tmp);
	data->index += ft_strlen(tmp);
	data->cmd = ft_strjoinaf1(data->cmd, tmp);
	tmp = data->absolute_cmd_before_auto + data->index_before_move;
	index_to_go = data->index;
	ft_putstr(tmp);
	data->index += ft_strlen(tmp);
	data->cmd = ft_strjoinaf1(data->cmd, tmp);
	while (data->index > index_to_go)
		move_left_without_mod(data);
}
