/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:22:52 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 23:28:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct g_shell	t_shell;
typedef struct s_node	t_node;

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

struct					s_builtin
{
	char				*name;
	int					(*func)(t_shell *g_shell, int argc, ...);
};
typedef struct s_builtin_info
{
	struct s_builtin	*builtins;
	int					count;
}						t_builtin_info;

int						exec_builtin(t_shell *g_shell, int argc, char **argv);
int						ft_exit(t_shell *g_shell, int argc, ...);
int						ft_unset(t_shell *g_shell, int argc, ...);
int						ft_echo(t_shell *g_shell, int argc, ...);
int						ft_env(t_shell *g_shell, int argc, ...);
int						ft_pwd(t_shell *g_shell, int argc, ...);
int						ft_cd(t_shell *g_shell, int argc, ...);
int32_t					is_flag(char **arg, int flag);
int						ft_export(t_shell *g_shell, int argc,
							...) __attribute__((unused));

t_builtin_info			*get_bt(t_shell *g_shell);
int						ft_setenv(t_shell *g_shell, const char *name,
							const char *value, int overwrite);

#endif
