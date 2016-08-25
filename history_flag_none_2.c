#include <sh21.h>

void			print_line_info(t_history *list, int i, int flg, t_cmd *cmd)
{
	putnbr_builtin(cmd, i, 1);
	if (flg == 1)
	{
		putchar_builtin(cmd, ' ', 1);
		if (list->time > 0)
			putnbr_builtin(cmd, list->time, 1);
		else
			putstr_builtin(cmd, "[NO TIMESTAMP]", 1);
	}
	putchar_builtin(cmd, ' ', 1);
	putstr_builtin(cmd, list->line, 1);
	putchar_builtin(cmd, '\n', 1);
}
