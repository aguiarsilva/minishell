/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:22:57 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/27 14:22:57 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LST_H
# define ENV_LST_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

//env_lst.c
t_env	*create_env_lst(char **ori_env, char **argv);
// env_lst_free.c
void	free_env_node(t_env *node);
void	free_env_lst(t_env **head);
// env_lst_utils.c
char	**env_list_to_array(t_env *env_list);
char	*get_key_in_env_lst(t_env *env_lst, char *key);
int		set_value_in_env_lst(t_env *env_lst, char *key, char *value);
void	update_exit_code(t_env *env_lst, int exit_code);
// env_lst_utils2.c
void	add_or_update_env_var(t_env **env_list, char *key, char *value);

#endif
