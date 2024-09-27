
// ReSharper disable All
#include "../lib/minishell.h"

int	open_input_or_output_file(char *filename, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == INPUT)
		ret = open(filename, O_RDONLY, 0666);
	else if (in_or_out == OUTPUT)
		ret = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		print_error_msg_and_exit(ERR_IMPOSSIBLE);
	if (ret == -1)
		print_error_open_file_and_exit(filename, errno); // not sure if this is enough or a custom function needed
	return (ret);
}