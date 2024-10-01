#include "../lib/minishell.h"

char *expand_env_variables(char *input, int index, t_env *env_list, int should_trim) 
{
    char *expanded_str = ft_calloc(1, 1);
    if (!expanded_str)
        return NULL;

    while (input[++index]) {
        if (input[0] != '\'' && input[index] == '$') {
            if (expand_variable(input, &index, &expanded_str, env_list))
                return NULL;
        } else {
            expanded_str = append_char(expanded_str, input[index]);
            if (!expanded_str)
                return NULL;
        }
        if (!input[index])
            break;
    }

    if (should_trim)
        expanded_str = trim_quotes(expanded_str);

    return expanded_str;
}

int expand_single_variable(char *input, int *index, char **expanded_str, t_env *env_list) {
    (*index)++;
    if (valid_variable_char(input[*index])) {
        if (perform_expansion(input, index, expanded_str, env_list))
            return 1;
    } else {
        *expanded_str = append_char(*expanded_str, input[*index - 1]);
        if (!(*expanded_str))
            return 1;
    }
    return 0;
}

int perform_expansion(char *input, int *index, char **expanded_str, t_env *env_list) {
    char *expansion_value = NULL;

    if (input[*index] == '$') {
        expansion_value = get_process_id(index);
    } else if (create_expansion_value(input, index, env_list, &expansion_value)) {
        return free(*expanded_str), 1;
    }

    if (expansion_value) {
        *expanded_str = join_strings(*expanded_str, expansion_value);
        if (!(*expanded_str))
            return 1;
    }

    free(expansion_value);
    return 0;
}

char *append_char(char *str, char c) {
    char *new_str;
    int len = ft_strlen(str);

    new_str = ft_calloc(len + 2, sizeof(char));
    if (!new_str)
        return NULL;

    ft_strlcpy(new_str, str, len + 1);
    new_str[len] = c;

    free(str);
    return new_str;
}

char *join_strings(char *str1, char *str2) {
    char *new_str = ft_strjoin(str1, str2);
    if (!new_str)
        return NULL;

    free(str1);
    return new_str;
}
