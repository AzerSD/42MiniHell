/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:22:52 by asioud            #+#    #+#             */
/*   Updated: 2023/08/23 23:15:17 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

struct					s_builtin
{
	char				*name;
	int					(*func)(int argc, ...);
};
typedef struct s_builtin_info
{
	struct s_builtin	*builtins;
	int					count;
}						t_builtin_info;

int						exec_builtin(int argc, char **argv);
int						ft_exit(int argc, ...);
int						ft_unset(int argc, ...);
int						ft_echo(int argc, ...);
int						ft_env(int argc, ...);
int						ft_pwd(int argc, ...);
int						ft_cd(int argc, ...);
int						ft_export(int argc, ...) __attribute__((unused));

t_builtin_info			*get_bt(void);
int						ft_setenv(const char *name, const char *value,
							int overwrite);

#endif
