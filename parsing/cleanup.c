#include "../lib/minishell.h"

void    free_prompt(t_prompt *prompt)
{
    free(prompt->symbols);
    free(prompt->whitespace);
}

void    free_mutil_cmd_arr(char **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}

void    free_tk(t_token *tk_list)
{
    t_token *tk_list_placeholder;

    if (!tk_list)
        return ;
    while (tk_list)
    {
        free(tk_list->val);
        free_multi_cmd_arr(tk_list->multi_cmd);
        tk_list_placeholder = tk_list;
        tk_list = tk_list->next;
        free(tk_list_placeholder);
    }
}