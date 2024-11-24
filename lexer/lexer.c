
#include "../lib/minishell.h"

bool	is_valid_var_char(char next_char)
{
	if (next_char == '\0' || ft_isspace(next_char)
		||next_char == '"' || next_char == '\''
		||next_char == '}' || next_char == ')'
		||next_char == ':' || next_char == '='
		||next_char == '^' || next_char == '%'
		|| (next_char >= '+' && next_char <= '/'))
		return (false);
	return (true);
}

char	*create_fake_pid(int *i)
{
	char	*exp_var;

	(*i)++;
	exp_var = ft_itoa(42424);
	if (!exp_var)
		return (NULL);
	return (exp_var);
}

int	calc_offset(char *split, int start, int *i)
{
	int	offset;

	offset = 0;
	if ((split[start] == '{' && split[*i] == '}')
		|| (split[start] == '(' && split[*i] == ')'))
	{
		offset++;
		(*i)++;
	}
	if (split[start + 1] == '{')
	{
		offset = -1;
		ft_putstr_fd("Error: Bad syntax near '{'\n", 2);
	}
	return (offset);
}

char	*find_exit_code(char *temp, t_env *env_lst)
{
	char	*temp2;
	char	*exp_var;
	t_env	*tmp;

	while (env_lst)
	{
		if (ft_strncmp("EC", env_lst->key, ft_strlen(env_lst->key)) == 0
			&& ft_strlen(env_lst->key) == 2)
			tmp = env_lst;
		env_lst = env_lst->next;
	}
	if (!tmp || !tmp->value) // Handle case where no "EC" variable is found or value is NULL
		return (NULL);
	temp2 = ft_strdup(tmp->value);
	if (!temp2)
		return (NULL);
	if (temp[1])
	{
		exp_var = ft_strjoin(temp2, &temp[1]);
		free(temp2);
	}
	else
		exp_var = temp2;
	return (exp_var);
}

int	find_exp_var(char *temp, char **exp_var, t_env *env_lst)
{
	char	*temp2;
	char	*temp3;
	int		i;

	i = -1;
	temp2 = ft_calloc(1, 1);
	*exp_var = NULL;
	while (temp[++i])
	{
		temp2 = ft_charjoin_mod(temp2, temp[i]);
		if (!temp2)
			return (1);
		temp3 = get_key_in_env_lst(env_lst, temp2);
		if (temp3)
			break ;
	}
	free(temp2);
	if (temp3 && !(ft_isalnum(temp[i + 1])) && temp[i + 1] != '_')
	{
		*exp_var = ft_strjoin(temp3, &temp[i + 1]);
		free(temp3);
		if (!(*exp_var))
			return (1);
	}
	return (0);
}

int	determine_exp_var(char *temp, t_env *lst, char **exp_var)
{

//	if (ft_isdigit(temp[0]) || temp[0] == '@') // did not understand that case for @
	if (ft_isdigit(temp[0]))
	{
		*exp_var = ft_strdup(temp + 1);
		if (!(*exp_var))
			return (1);
	}
	else if (temp[0] == '?') // not working as intended it segmentsfaults
	{
		*exp_var = find_exit_code(temp, lst);
		if (!(*exp_var))
			return (1);
	}
	else
		if (find_exp_var(temp, exp_var, lst))
			return (1);
	return (0);
}

// Helper function to check if character is valid in variable name
static bool	is_var_delimiter(char c)
{
	if (c == '"' || c == '\'' || c == '}' || c == ')'
		|| c == '$' || ft_isspace(c))
		return (false);
	return (true);
}

int	create_exp_var(char *split, int *i, t_env *env_lst, char **exp_var)
{
	int start;
	int offset;
	int var_length;
	char *var_name;

	start = *i;
	// Find the end of the variable name
	while (split[*i] && is_var_delimiter(split[*i]))
		(*i)++;
	// Calculate offset for variable extraction
	offset = calc_offset(split, start, i);
	if (offset == -1)
		return (1);
	// Extract the variable name
	var_length = *i - start - (2 * offset);
	var_name = ft_substr(split, start + offset, var_length);
	if (!var_name)
		return (1);
	// Process the variable and clean up
	if (determine_exp_var(var_name, env_lst, exp_var))
	{
		free(var_name);
		return (1);
	}
	free(var_name);
	return (0);
}

int	expand(char *str_to_expand, int *i, char **exp_word, t_env *env_lst)
{
	char	*exp_var;

	exp_var = NULL;
	if (str_to_expand[*i] && str_to_expand[*i] == '$') // edge case $$ returns process ID but we are not allowed to use get pid to get a real number
	{
		exp_var = create_fake_pid(i);
		if (!exp_var)
			return (free(*exp_word), 1);
	}
	else
	{
		// printf("in expand if before create_exp_var\n");
		if (create_exp_var(str_to_expand, i, env_lst, &exp_var))
			return (free(*exp_word), 1);
	}
	if (exp_var)
	{
		*exp_word = ft_strjoin(*exp_word, exp_var);
		if (!(*exp_word))
			return (1);
	}
	free(exp_var);
	return (0);
}

int	check_expand_helper(char *str_to_expand, int *i,
char **exp_word, t_env *env_lst)
{
	if (is_valid_var_char(str_to_expand[*i + 1]))
	{
		// printf("string %s is valid_var \n", str_to_expand);
		(*i)++;
		// printf("moved after $ i = %d\n", *i);
		if (expand(str_to_expand, i, exp_word, env_lst))
			return (1);
		(*i)--;
	}
	else
	{
		*exp_word = ft_charjoin_mod(*exp_word, str_to_expand[*i]);
		if (!(*exp_word))
			return (1);
	}
	return (0);
}

char	*check_expand(char *word, int i, t_env *env_lst)
{
	char	*exp_word;

	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		if (word[0] != '\'' && word[i] == '$')  //edge case when $ is quoted string
		{
//			printf("detected dollar symbol for word %s and i = %d\n", word, i);
			if (check_expand_helper(word, &i, &exp_word, env_lst))
				return (NULL);
		}
		else // loop character by character and just creates the whole string again if no $ symbol
		{
			exp_word = ft_charjoin_mod(exp_word, word[i]);
			if (!exp_word)
				return (NULL);
		}
		if (!word[i])
			break ;
	}
//	if (trim_flag)
//		exp_word = trim_word(exp_word);
	return (exp_word);
}

t_token	*make_word_token(char *wd, t_type type, t_env *env_lst)
{
	t_token	*new_tk;
	int		len;
	char	*checked_word;

	// printf("debug buffer print pre check expand: %s\n", wd);
	checked_word = check_expand(wd, -1, env_lst);
	// printf("debug buffer print after check expand: %s\n", wd);
	len = ft_strlen(checked_word);
	new_tk = malloc(sizeof(t_token));
	if (new_tk == NULL)
		return (NULL);
	new_tk->val = (char *)malloc(sizeof(char) * (len + 1));
	if (new_tk->val == NULL)
	{
		free(new_tk);
		return (NULL);
	}
	ft_strcpy(new_tk->val, checked_word);
	new_tk->eof_flag = false;
	new_tk->next = NULL;
	new_tk->type = type;
	free(checked_word);
	return (new_tk);
}

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

// t_token	*create_word_list(char *input, t_env **env_lst)
// {
//     t_token *head = NULL, *tail = NULL;
//     size_t i, len = ft_strlen(input);
//     char buffer[1024] = {0};
//     size_t buf_index = 0;
//     int was_quoted = 0;
//     int in_quotes = 0;

//     for (i = 0; i < len; i++)
//     {
//         if (input[i] == '"' && (i == 0 || input[i - 1] != '\\'))
//         {
//             in_quotes = !in_quotes;
//             buffer[buf_index++] = input[i];
//             continue;
//         }

//         if (ft_isspace(input[i]) && !in_quotes)
//         {
//             if (buf_index > 0)
//             {
//                 remove_quotes(buffer, &was_quoted);
//                 t_token *new_token = make_word_token(buffer, WORD, *env_lst);
//                 add_new_token_to_lst(&head, &tail, new_token);
//                 ft_memset(buffer, 0, 1024);
//                 buf_index = 0;
//                 was_quoted = 0;
//             }
//             continue;
//         }
//         // Check for special characters only if not inside quotes
//         if (!in_quotes && !was_quoted && (input[i] == '|' ||
//             (input[i] == '=' && (buf_index == 0 || i == len - 1 || ft_isspace(input[i + 1])))))
//         {
//             if (buf_index > 0)
//             {
//                 remove_quotes(buffer, &was_quoted);
//                 t_token *new_token = make_word_token(buffer, WORD, *env_lst);
//                 add_new_token_to_lst(&head, &tail, new_token);
//                 ft_memset(buffer, 0, 1024);
//                 buf_index = 0;
//             }
//             char special_char[2] = {input[i], '\0'};
//             t_token *special_token = make_word_token(special_char,
//                 input[i] == '=' ? WORD : get_token_type(special_char), *env_lst);
//             add_new_token_to_lst(&head, &tail, special_token);
//         }
//         else if (!in_quotes && input[i] == '<' && i + 1 < len && input[i + 1] == '<')
//         {
//             if (buf_index > 0)
//             {
//                 t_token *new_token = make_token(buffer, WORD);
//                 add_new_token_to_lst(&head, &tail, new_token);
//                 memset(buffer, 0, 1024);
//                 buf_index = 0;
//             }
//             char double_left[3] = {'<', '<', '\0'};
//             t_token *double_left_token = make_token(double_left, get_token_type(double_left));
//             add_new_token_to_lst(&head, &tail, double_left_token);
//             i++; // Skip the second '<'
//         }
//         else if (!in_quotes && input[i] == '>' && i + 1 < len && input[i + 1] == '>')
//         {
//             if (buf_index > 0)
//             {
//                 t_token *new_token = make_token(buffer, WORD);
//                 add_new_token_to_lst(&head, &tail, new_token);
//                 memset(buffer, 0, 1024);
//                 buf_index = 0;
//             }
//             char double_right[3] = {'>', '>', '\0'};
//             t_token *double_right_token = make_token(double_right, get_token_type(double_right));
//             add_new_token_to_lst(&head, &tail, double_right_token);
//             i++; // Skip the second '>'
//         }
//         else
//         {
//             buffer[buf_index++] = input[i];
//         }
//     }
//     if (buf_index > 0)
//     {
//         remove_quotes(buffer, &was_quoted);
//         t_token *new_token = make_word_token(buffer, WORD, *env_lst);
//         add_new_token_to_lst(&head, &tail, new_token);
//     }
//     return head;
// }

static void init_buffer_state(t_buffer_state *state)
{
    ft_memset(state->buffer, 0, BUFFER_SIZE);
    state->buf_index = 0;
    state->was_quoted = 0;
    state->in_quotes = 0;
}

static void init_token_list(t_token_list *list)
{
    list->head = NULL;
    list->tail = NULL;
}

static void flush_buffer(t_parser_context *ctx)
{
    if (ctx->state->buf_index > 0)
    {
        remove_quotes(ctx->state->buffer, &ctx->state->was_quoted);
        t_token *new_token = make_word_token(ctx->state->buffer, WORD, *ctx->env_lst);
        add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, new_token);
        ft_memset(ctx->state->buffer, 0, BUFFER_SIZE);
        ctx->state->buf_index = 0;
        ctx->state->was_quoted = 0;
    }
}

static void treat_quotes(char c, t_buffer_state *state)
{
    state->in_quotes = !(state->in_quotes);
    state->buffer[state->buf_index++] = c;
}

// static void add_special_token(t_parser_context *ctx, char c, int token_type)
// {
//     char special_char[2] = {c, '\0'};
//     t_token *special_token = make_word_token(special_char, token_type, *ctx->env_lst);
//     add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, special_token);
// }

static void process_special_char(char c, t_parser_context *ctx)
{
    flush_buffer(ctx);
    int token_type = (c == '=') ? WORD : get_token_type((char[2]){c, '\0'});
    char special_char[2] = {c, '\0'};
    t_token *special_token = make_word_token(special_char, token_type, *ctx->env_lst);
    add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, special_token);
}

static int is_equals_special(char c, t_char_context *char_ctx, t_buffer_state *state)
{
    if (c != '=')
        return (0);
    return (state->buf_index == 0 || 
            char_ctx->current_index == char_ctx->input_length - 1 || 
            ft_isspace(char_ctx->input[char_ctx->current_index + 1]));
}

static int should_process_double_char(t_char_context *char_ctx)
{
    if (char_ctx->current_index + 1 >= char_ctx->input_length)
        return (0);
        
    char current = char_ctx->input[char_ctx->current_index];
    char next = char_ctx->input[char_ctx->current_index + 1];
    
    if (current == '<' && next == '<')
        return ('<');
    if (current == '>' && next == '>')
        return ('>');
    return (0);
}

static void process_double_char(t_parser_context *ctx, char c, size_t *i)
{
    flush_buffer(ctx);
    char double_char[3] = {c, c, '\0'};
    t_token *double_token = make_token(double_char, get_token_type(double_char));
    add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, double_token);
    (*i)++;
}

static void handle_special_cases(t_parser_context *ctx, t_char_context *char_ctx)
{
    char c = char_ctx->input[char_ctx->current_index];
    int double_char;
    
    if (c == '"' && (char_ctx->current_index == 0 || 
                     char_ctx->input[char_ctx->current_index - 1] != '\\'))
    {
        treat_quotes(c, ctx->state);
        return;
    }
    
    if (!(ctx->state->in_quotes))
    {
        if (ft_isspace(c))
            flush_buffer(ctx);
        else if (!ctx->state->was_quoted && 
                 (c == '|' || is_equals_special(c, char_ctx, ctx->state)))
            process_special_char(c, ctx);
        else
        {
            double_char = should_process_double_char(char_ctx);
            if (double_char)
                process_double_char(ctx, double_char, &char_ctx->current_index);
            else
                ctx->state->buffer[ctx->state->buf_index++] = c;
        }
    }
    else
        ctx->state->buffer[ctx->state->buf_index++] = c;
}

// static void handle_character(const char *input, size_t *i, t_token **head,
//     t_token **tail, t_buffer_state *state, t_env **env_lst)
// {
//     char c;

//     c = input[*i];
//     handle_special_cases(c, input, i, head, tail, state, env_lst);
// }

t_token *create_word_list(char *input, t_env **env_lst)
{
    t_buffer_state state;
    t_token_list tokens;
    t_parser_context ctx;
    t_char_context char_ctx;
    
    init_buffer_state(&state);
    init_token_list(&tokens);
    
    ctx.state = &state;
    ctx.tokens = &tokens;
    ctx.env_lst = env_lst;
    
    char_ctx.input = input;
    char_ctx.input_length = ft_strlen(input);
    char_ctx.current_index = 0;
    
    while (char_ctx.current_index < char_ctx.input_length)
    {
        handle_special_cases(&ctx, &char_ctx);
        char_ctx.current_index++;
    }
    
    flush_buffer(&ctx);
    return tokens.head;
}