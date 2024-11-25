
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

t_token	*create_word_list(char *input, t_env **env_lst)
{
	t_buffer_state		state;
	t_token_list		tokens;
	t_parser_context	ctx;
	t_char_context		char_ctx;
	
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
