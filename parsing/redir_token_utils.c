

#include "../lib/minishell.h"

bool	is_filename(const char *str)
{
	const char	*dot_position;
	const char	*file_extension;

	dot_position = ft_strrchr(str, '.');

	if (dot_position && dot_position != str && *(dot_position + 1) != '\0')
	{
		file_extension = dot_position + 1;
		while (*file_extension != '\0')
		{
			if (!ft_isalnum(*file_extension))
				return (false);
			file_extension++;
		}
		//		fprintf(stderr, "print recogniced file names %s\n", str);
		return (true);
	}
	return (false);
}

int	determine_redirection_type(int filetype)
{
	if (filetype == INPUT || filetype == HEREDOC_INPUT)
		return (REDIR_IN);
	else if (filetype == OUTPUT)
		return (REDIR_OUT);
	else if (filetype == APPEND_OUTPUT)
		return (APPEND);
	else
		return (WORD);
}