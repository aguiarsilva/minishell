#include "../lib/minishell.h"

char *get_process_id(int *index) {
    (*index)++;
    return ft_itoa(getpid());
}
