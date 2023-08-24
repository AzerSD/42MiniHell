/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:28:17 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 17:54:24 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(t_shell *g_shell, const char *str)
{
	char	*eq;
	int		len;
	char	*var_name;

	eq = ft_strchr(str, '=');
	if (eq)
	{
		len = eq - str;
		var_name = my_malloc(&(g_shell->memory), len + 1);
		ft_strncpy(var_name, str, len);
		var_name[len] = '\0';
		return (var_name);
	}
	else
		return (NULL);
}

void	string_to_symtab(t_shell *g_shell, const char *env_var)
{
	struct s_symtab_entry	*entry;
	char					*eq;
	char					*name;

	eq = ft_strchr(env_var, '=');
	if (eq)
	{
		name = get_varname(g_shell, env_var);
		entry = add_to_symtab(g_shell, name);
		if (entry)
			symtab_entry_setval(g_shell, entry, eq + 1);
	}
	else
	{
		entry = add_to_symtab(g_shell, env_var);
		if (entry)
			symtab_entry_setval(g_shell, entry, NULL);
	}
}

void	init_symtab(t_shell *g_shell, char **env)
{
	char					**p2;

	init_symtab_stack(g_shell);
	p2 = env;
	while (*p2)
	{
		string_to_symtab(g_shell, *p2);
		p2++;
	}
}

void	init_symtab_stack(t_shell *g_shell)
{
	struct s_symtab	*global_symtab;

	global_symtab = my_malloc(&(g_shell->memory), sizeof(struct s_symtab));
	g_shell->s_symtab_stack.symtab_count = 1;
	if (!global_symtab)
	{
		ft_printf_fd(STDERR_FILENO, "fatal error: no memory \
		for global symbol table\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(global_symtab, 0, sizeof(struct s_symtab));
	g_shell->s_symtab_stack.global_symtab = global_symtab;
	g_shell->s_symtab_stack.local_symtab = global_symtab;
	g_shell->s_symtab_stack.symtab_list[0] = global_symtab;
}

struct s_symtab	*new_symtab(t_shell *g_shell)
{
	struct s_symtab	*symtab;

	symtab = my_malloc(&(g_shell->memory), sizeof(struct s_symtab));
	if (!symtab)
	{
		ft_printf_fd(STDERR_FILENO, "fatal error: no memory \
		for new symbol table\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(symtab, 0, sizeof(struct s_symtab));
	return (symtab);
}
