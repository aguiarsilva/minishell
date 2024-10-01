
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

// t_cmd	*fill_cmd (t_token *list) // currently only handles a single command // working version
// {
// 	t_cmd	*cmd_data;
// 	t_token	*cur;
// 	size_t	i;
// 	size_t	arg_count;
// 	t_token	*tmp;
//
// 	i = 0;
// 	arg_count = 0;
// 	cmd_data = safe_malloc(sizeof(t_cmd));
// 	if (!cmd_data)
// 		return (NULL);
// 	cmd_data->cmd = ft_strdup(list->val);
// 	cur = list->next;
// 	tmp = cur;
// 	while (tmp != NULL)
// 	{
// 		arg_count++;
// 		tmp = tmp->next;
// 	}
// 	cmd_data->args = safe_malloc((arg_count + 1) * sizeof(char *));
// 	if (!cmd_data->args)
// 		return (NULL);
// 	while (cur != NULL)
// 	{
// 		cmd_data->args[i] = ft_strdup(cur->val);
// 		cur = cur->next;
// 		i++;
// 	}
// 	cmd_data->args[i] = NULL;
// 	cmd_data->builtin = check_for_builtin(cmd_data->cmd);
// 	return (cmd_data);
// }

t_cmd *fill_cmd(t_token *list, t_redir *redir_list) // Accepting an existing redir_list
{
    t_cmd *cmd_data;
    t_token *cur;
    size_t i;
    size_t arg_count;

    i = 0;
    arg_count = 0;
    cmd_data = safe_malloc(sizeof(t_cmd));
    if (!cmd_data)
        return (NULL);

    cmd_data->cmd = ft_strdup(list->val);
    if (!cmd_data->cmd)
    {
        free(cmd_data);
        return (NULL);
    }

    // Initialize the redir field in cmd_data
    cmd_data->redir = redir_list; // later i have to add an interator if i can handle multiple commands

    // Set the current token pointer to the next token after the command
    cur = list->next;

    // First pass: Count arguments using a while loop
    while (cur != NULL)
    {
          // if (get_token_type(cur->val) != WORD) // handle proper argcount later
        {
            arg_count++; // Count valid arguments
        }
        cur = cur->next; // Move to the next token
    }

    // Allocate space for arguments
    cmd_data->args = safe_malloc((arg_count + 1) * sizeof(char *));
    if (!cmd_data->args)
    {
        free(cmd_data->cmd);
        free(cmd_data); // Free previously allocated cmd_data
        return (NULL);
    }

    // Second pass: Fill args array using a while loop
    cur = list->next; // Reset cur to start from the first argument
    i = 0; // Reset index for args
    while (cur != NULL)
    {
        // Check if the token is not a redirection token
    	if (get_token_type(cur->val) == WORD)
        {
            cmd_data->args[i] = ft_strdup(cur->val);
            if (!cmd_data->args[i])
            {
                // Handle allocation failure and free previously allocated args
                while (i > 0) // Free previously allocated arguments
                {
                    free(cmd_data->args[--i]);
                }
                free(cmd_data->args);
                free(cmd_data->cmd);
                free(cmd_data);
                return (NULL);
            }
            i++;
        }
        cur = cur->next; // Move to the next token
    }
    cmd_data->args[i] = NULL; // Null-terminate the args array

    cmd_data->builtin = check_for_builtin(cmd_data->cmd); // Check if it's a builtin command
    return (cmd_data);
}


char *combine_command_and_args(char *cmd, char **args) // temporary
{
	size_t	cmd_length = strlen(cmd);
	size_t	args_length = 0;
	int	i = 0;

	// Calculate total length for args
	while (args && args[i])
	{
		args_length += strlen(args[i]) + 1; // +1 for space
		i++;
	}
	// Allocate memory for combined command
	char *full_cmd = malloc(cmd_length + args_length + 1); // +1 for null terminator
	if (!full_cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(full_cmd, cmd);
	i = 0;
	while (args && args[i])
	{
		strcat(full_cmd, " ");
		strcat(full_cmd, args[i]);
		i++;
	}
	return (full_cmd);
}
