
#include "../lib/minishell.h"

t_token	*make_token(char *wd, t_type type)
{
	t_token	*new_tk;
	int		len;

	len = ft_strlen(wd);
	new_tk = malloc(sizeof(t_token));
	if (new_tk == NULL)
		return (NULL);
	new_tk->val = (char *)malloc(sizeof(char) * (len + 1));
	if (new_tk->val == NULL)
	{
		free(new_tk);
		return (NULL);
	}
	ft_strcpy(new_tk->val, wd);
	new_tk->eof_flag = false;
	new_tk->next = NULL;
	new_tk->type = type;
	return (new_tk);
}

void	assign_token_type(t_token *token_list)
{
	t_token	*current;
	t_token	*previous;

	current = token_list;
	previous = NULL;
	while (current != NULL)
	{
		current->type = get_token_type(current->val);
		if (previous != NULL && get_token_type(previous->val) == HEREDOC)
			current->eof_flag = true;
		previous = current;
		current = current->next;
	}
}

t_token *create_word_list(char *input) {
    t_token *head = NULL, *tail = NULL;
    size_t i, len = strlen(input);
    char buffer[1024] = {0};
    size_t buf_index = 0;

    for (i = 0; i < len; i++) {
        // Check for whitespace
        if (isspace(input[i])) {
            if (buf_index > 0) {
                t_token *new_token = make_token(buffer, WORD);
                add_new_token_to_lst(&head, &tail, new_token);
                memset(buffer, 0, 1024);
                buf_index = 0;
            }
            continue;
        }

        // Check for special characters
        if (input[i] == '=' || input[i] == '<' || input[i] == '>' || input[i] == '|') {
            // Create token from buffer (if any)
            if (buf_index > 0) {
                t_token *new_token = make_token(buffer, WORD);
                add_new_token_to_lst(&head, &tail, new_token);
                memset(buffer, 0, 1024);
                buf_index = 0;
            }

            // Create token for special character
            char special_char[2] = {input[i], '\0'};
            t_token *special_token = make_token(special_char, get_token_type(special_char));
            add_new_token_to_lst(&head, &tail, special_token);
        }
        else {
            buffer[buf_index++] = input[i];
        }
    }

    // Create last token from buffer (if any)
    if (buf_index > 0) {
        t_token *new_token = make_token(buffer, WORD);
        add_new_token_to_lst(&head, &tail, new_token);
    }

    return head;
}