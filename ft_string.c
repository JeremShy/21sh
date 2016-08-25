#include <sh21.h>

char	*insert_char(char *str, int index, char c)
{
	char *ret;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_strncpy(ret, str, index);
	ret[index] = c;
	ft_strcpy(ret + index + 1, str + index);
	free(str);
	return (ret);
}

char	*delete_char(char *str, int index)
{
	char *ret;

	ret = (char*)malloc(sizeof(char) * ft_strlen(str));
	ft_strncpy(ret, str, index - 1);
	ft_strcpy(ret + index - 1, str + index);
	free(str);
	return (ret);
}
