#include "../lib/minishell.h"

void    free_prompt(t_prompt *prompt)
{
    free(prompt->symbols);
    free(prompt->whiltespace);
}
