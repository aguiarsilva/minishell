

#include "../lib/minishell.h"

// Process a single token into args array
int	process_token_to_args(t_cmd *cmd_data, t_token *cur, int *arg_index)
{
	if (get_token_type(cur->val) != WORD)
		return (1);
	cmd_data->args[*arg_index] = ft_strdup(cur->val);
	if (!cmd_data->args[*arg_index])
		return (0);  // Allocation failed

//	ft_printf(stderr, "Copied arg: %s\n", cmd_data->args[*arg_index]); // broken print
	(*arg_index)++;
	return (1);
}

int	fill_arguments(t_cmd *cmd_data, t_token *token_list, size_t *arg_count)
{
	int			arg_index;
	t_token		*cur;
	t_token		*prev;

	arg_index = 0;
	cur = token_list;
	prev = NULL;
	cmd_data->args = malloc((*arg_count + 1) * sizeof(char *));
	if (!cmd_data->args)
		return (-1);
	while (cur && cur->type != PIPE)
	{
		if (is_skippable_token(prev, cur))
		{
			prev = cur;
			cur = cur->next;
			continue ;
		}
		if (!process_token_to_args(cmd_data, cur, &arg_index))
			return (cleanup_args(cmd_data->args, arg_index), -1);
		prev = cur;
		cur = cur->next;
	}
	cmd_data->args[arg_index] = NULL;
	return (0);
}

static t_token	*find_next_pipe_symbol(t_token *token_list)
{
	t_token	*cur;

	cur = token_list->next;
	while (cur != NULL && cur->type != PIPE)
		cur = cur->next;
	return (cur);
}

static t_cmd	*create_cmd_from_tokens(t_token *token_list,
										t_redir *redir_list,
										t_cmd **head, t_cmd **tail)
{
	t_cmd	*cmd_data;
	size_t	arg_count;

	if (token_list->type != WORD)
	{
		fprintf(stderr, "Error: First token is not a command (WORD)\n"); //debug print
		return (cleanup_cmd_list(*head));
	}
	cmd_data = create_new_cmd_node(token_list->val, redir_list);
	if (!cmd_data)
		return (cleanup_cmd_list(*head));
	arg_count = count_arguments(token_list->next);
	if (fill_arguments(cmd_data, token_list->next, &arg_count) < 0)
		return (cleanup_cmd_list(*head));
	add_new_cmd_to_cmd_lst(head, tail, cmd_data);
	return (NULL);
}

t_cmd	*fill_cmd_lst(t_token *token_list, t_redir *redir_list)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*cur;

	if (token_list && token_list->val && is_special_command(token_list->val))
		return NULL;
	if (!is_valid_redirection_syntax(token_list))
	{
		fprintf(stderr, "minishell: syntax error near unexpected token\n");
		return NULL;
	}
	head = NULL;
	tail = NULL;
	while (token_list != NULL)
	{
		if (create_cmd_from_tokens(token_list, redir_list, &head, &tail))
			return (NULL);
		cur = find_next_pipe_symbol(token_list);
		if (cur != NULL && cur->type == PIPE)
			token_list = cur->next;
		else
			break ;
	}
	return (head);
}

// Main function to parse the token list and fill the command structure
//t_cmd*	fill_cmd(t_token *token_list, t_redir *redir_list)
//{
//	t_cmd	*head;
//	t_cmd	*tail;
//	t_cmd	*cmd_data;
//	size_t	arg_count;
//
//	head = NULL;
//	tail = NULL;
//	// Start parsing the token list
//	while (token_list != NULL)
//	{
//		if (token_list->type != WORD)
//		{
//			fprintf(stderr, "Error: First token is not a command (WORD)\n");
//			free_cmd_list(head);
//			return NULL;
//		}
//
//		// Create a new command node
//		cmd_data = create_new_cmd_node(token_list->val, redir_list);
//		if (!cmd_data)
//		{
//			free_cmd_list(head);
//			return NULL;
//		}
//
//		// Count the arguments for this command
//		arg_count = count_arguments(token_list->next);
//		// fprintf(stderr, "argcount %lu\n", arg_count);
//		// Fill the arguments for the command
//		if (fill_arguments(cmd_data, token_list->next, arg_count) < 0)
//		{
//			free_cmd_list(head);
//			return (NULL);
//		}
//
//		// Add the command to the command list
//		if (head == NULL)
//		{
//			head = cmd_data; // Set head if list is empty
//			tail = cmd_data; // Initialize tail
//		}
//		else
//		{
//			tail->next = cmd_data; // Link the new command
//			tail = cmd_data; // Update tail
//		}
//
//		// Move to the next token (after the pipe if it exists)
//		t_token* cur = token_list->next;
//		while (cur != NULL && cur->type != PIPE)
//			cur = cur->next;
//		if (cur != NULL && cur->type == PIPE)
//			token_list = cur->next;
//		else
//			break; // Exit if no more commands
//	}
//	return (head); // Return the head of the command list
//}

//// Main argument filling function
//int	fill_arguments(t_cmd* cmd_data, t_token* token_list, size_t arg_count)
//{
//	int arg_index = 0;
//	t_token* cur = token_list;
//	t_token* prev = NULL;
//
//	// Allocate args array
//	cmd_data->args = malloc((arg_count + 1) * sizeof(char*));
//	if (!cmd_data->args)
//		return -1;
//
//	// Process tokens
//	while (cur && cur->type != PIPE) {
//		// Skip certain tokens
//		if (is_skippable_token(prev, cur)) {
//			prev = cur;
//			cur = cur->next;
//			continue;
//		}
//
//		// Try to process current token
//		if (!process_token_to_args(cmd_data, cur, &arg_index)) {
//			cleanup_args(cmd_data->args, arg_index);
//			return -1;
//		}
//
//		prev = cur;
//		cur = cur->next;
//	}
//
//	// Null-terminate args array
//	cmd_data->args[arg_index] = NULL;
//	return 0;
//}