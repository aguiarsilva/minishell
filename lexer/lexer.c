
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
    size_t i, len = ft_strlen(input);
    char buffer[1024] = {0};
    size_t buf_index = 0;
    int was_quoted = 0;

    for (i = 0; i < len; i++) {
        if (ft_isspace(input[i])) {
            if (buf_index > 0) {
                remove_quotes(buffer, &was_quoted);
                t_token *new_token = make_token(buffer, WORD);
                add_new_token_to_lst(&head, &tail, new_token);
                ft_memset(buffer, 0, 1024);
                buf_index = 0;
                was_quoted = 0;
            }
            continue;
        }

        // Check for special characters only if not inside quotes
        if (!was_quoted && (input[i] == '|' || 
            (input[i] == '=' && (buf_index == 0 || i == len - 1 || ft_isspace(input[i + 1]))))) {
            if (buf_index > 0) {
                remove_quotes(buffer, &was_quoted);
                t_token *new_token = make_token(buffer, WORD);
                add_new_token_to_lst(&head, &tail, new_token);
                ft_memset(buffer, 0, 1024);
                buf_index = 0;
            }
            char special_char[2] = {input[i], '\0'};
            t_token *special_token = make_token(special_char, 
                input[i] == '=' ? WORD : get_token_type(special_char));
            add_new_token_to_lst(&head, &tail, special_token);
        } 
        else if (input[i] == '<' && i + 1 < len && input[i + 1] == '<') {
			// Handle two consecutive '<' characters
			// Create token from buffer (if any)
			if (buf_index > 0) {
				t_token *new_token = make_token(buffer, WORD);
				add_new_token_to_lst(&head, &tail, new_token);
				memset(buffer, 0, 1024);
				buf_index = 0;
			}

			// Create token for '<<'
			char double_left[3] = {'<', '<', '\0'};
			t_token *double_left_token = make_token(double_left, get_token_type(double_left));
			add_new_token_to_lst(&head, &tail, double_left_token);
			i++; // Skip the second '<'
		}
		else if (input[i] == '>' && i + 1 < len && input[i + 1] == '>') {
			// Handle two consecutive '>' characters
			// Create token from buffer (if any)
			if (buf_index > 0) {
				t_token *new_token = make_token(buffer, WORD);
				add_new_token_to_lst(&head, &tail, new_token);
				memset(buffer, 0, 1024);
				buf_index = 0;
			}

			// Create token for '>>'
			char double_right[3] = {'>', '>', '\0'};
			t_token *double_right_token = make_token(double_right, get_token_type(double_right));
			add_new_token_to_lst(&head, &tail, double_right_token);
			i++; // Skip the second '>'
		}
        else {
            buffer[buf_index++] = input[i];
        }
    }

    if (buf_index > 0) {
        remove_quotes(buffer, &was_quoted);
        t_token *new_token = make_token(buffer, WORD);
        add_new_token_to_lst(&head, &tail, new_token);
    }

    return head;
}