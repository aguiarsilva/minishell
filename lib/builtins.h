
#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H

//echo.c
int		echo(t_cmd *cmd_data);
int		check_for_builtin(char *cmd);
#endif //MINISHELL_BUILTINS_H
