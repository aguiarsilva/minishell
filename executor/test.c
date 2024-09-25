
#include "../lib/minishell.h"

// t_cmd *fill_cmd(char **input) // need to rework to work with multiple cmds
// {
// 	t_cmd	*cmd_data;
// 	size_t	arg_count; // will get it from struct later
// 	size_t	i;

// 	cmd_data = safe_malloc(sizeof(t_cmd));
// 	if (!cmd_data)
// 		return (NULL);
// 	cmd_data->cmd = ft_strdup(input[0]);

// 	arg_count = 0;
// 	while (input[arg_count])
// 		arg_count++;
// //	fprintf(stderr,"arg_count =%d\n", arg_count);
// 	cmd_data->args = safe_malloc(sizeof(char *) * arg_count);
// 	i = 0;
// 	while (i < arg_count)
// 	{
// //		fprintf(stderr,"in while \n");
// //		fprintf(stderr,"%s\n", input[i]);
// 		cmd_data->args[i] = ft_strdup(input[i]);
// //		fprintf(stderr,"%s\n", cmd_data->args[i]);
// 		i++;
// 	}
// //	fprintf(stderr,"test %s\n", cmd_data->args[2]);
// 	cmd_data->args[arg_count] = NULL;
// 	cmd_data->builtin = check_for_builtin(cmd_data->cmd);
// 	return (cmd_data);
// }

t_cmd *fill_cmd (t_token *list)
{
	t_cmd	*cmd_data;
	t_token	*cur;

	size_t	i;
	size_t arg_count = 0;
	printf("begin");
	i = 0;
	
	cmd_data = safe_malloc(sizeof(t_cmd));
	if (!cmd_data)
		return (NULL);
	cmd_data->cmd = ft_strdup(list->val); // echo test
	cur = list->next;
		
	t_token *tmp = cur;
    while (tmp != NULL) {
        arg_count++;
        tmp = tmp->next;
    }
	    // Allocate memory for args, including space for NULL terminator
    cmd_data->args = safe_malloc((arg_count + 1) * sizeof(char *));
    if (!cmd_data->args)
        return (NULL);
	while (cur != NULL)
	{
		cmd_data->args[i] = ft_strdup(cur->val);
		cur = cur->next;
		i++;
	}
	cmd_data->args[i] = NULL;
	
	printf("here");
	cmd_data->builtin = check_for_builtin(cmd_data->cmd);
	return (cmd_data);
	
}
char *combine_command_and_args(const char *cmd, char **args) // temporary
{
	size_t cmd_length = strlen(cmd);
	size_t args_length = 0;
	int i = 0;

	// Calculate total length for args
	while (args && args[i])
	{
		args_length += strlen(args[i]) + 1; // +1 for space
		i++;
	}

	// Allocate memory for combined command
	char *full_cmd = malloc(cmd_length + args_length + 1); // +1 for null terminator
	if (!full_cmd) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (args && args[i]) {
		strcat(full_cmd, args[i]);
		if (args[i + 1] != NULL) {
			strcat(full_cmd, " "); // Add space between arguments
		}
		i++;
	}

	return full_cmd;
}