/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 18:16:04 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(struct s_symtab_entry *entry)
{
	while (entry)
	{
		ft_printf_fd(STDERR_FILENO, "declare -x %s=%s\n", \
		entry->name, entry->val);
		entry = entry->next;
	}
	return (0);
}

int	process_plus_equal(t_shell *g_shell, char *name, \
	struct s_symtab *symtab, char **argv)
{
	char					*value;
	char					*old_value;
	struct s_symtab_entry	*entry;
	char					*new_value;

	old_value = "";
	if (!name || !is_valid_variable_name(argv[1]))
	{
		ft_printf_fd(STDERR_FILENO, \
			"minishell: export: `%s': not a valid identifier\n", argv[1]);
		return (1);
	}
	value = ft_strtok(NULL, "+=");
	entry = do_lookup(name, symtab);
	if (entry)
		old_value = entry->val;
	new_value = my_malloc(&g_shell->memory, ft_strlen(old_value) \
	+ ft_strlen(value) + 1);
	ft_strcpy(new_value, old_value);
	ft_strcat(new_value, value);
	ft_setenv(g_shell, name, new_value, 1);
	free(new_value);
	return (0);
}

int	process_equal(t_shell *g_shell, char *name, char **argv)
{
	if (is_valid_variable_name(name))
	{
		string_to_symtab(g_shell, argv[1]);
		return (0);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n",
			name);
		return (1);
	}
}

int	check_input_arguments(t_shell *g_shell, char **argv, struct s_symtab *symtab, char *name)
{
	struct s_symtab_entry	*entry;

	if (argv[1][0] == '-')
		return (ft_printf_fd(STDERR_FILENO, \
		"bash: export: --: invalid option\nexport: \
        usage: export [-nf] [name[=value] ...] or export -p\n"), 2);
	name = get_varname(g_shell, argv[1]);
	if (!name)
		name = argv[1];
	if (ft_strstr(argv[1], "+=") != NULL)
	{
		name = ft_strtok(argv[1], "+=");
		return (process_plus_equal(g_shell, name, symtab, argv));
	}
	else if (ft_strchr(argv[1], '=') != NULL)
		return (process_equal(g_shell, name, argv));
	else
	{
		entry = do_lookup(argv[1], symtab);
		if (entry)
			return (ft_printf_fd(STDERR_FILENO, "declare -x %s=%s\n", \
			entry->name, entry->val), 0);
		else if (!is_valid_variable_name(name))
			return (ft_printf_fd(STDERR_FILENO, \
			"minishell: export: `%s': not a valid identifier\n", argv[1]), 1);
		return (0);
	}
}

int	ft_export(t_shell *g_shell, int argc, ...)
{
	struct s_symtab_entry	*entry;
	struct s_symtab			*symtab;
	char					**argv;
	char					*name;
	va_list					args;

	entry = NULL;
	name = NULL;
	symtab = g_shell->s_symtab_stack.local_symtab;
	va_start(args, argc);
	argv = va_arg(args, char **);
	entry = symtab->first;
	va_end(args);
	if (argc == 1)
		return (print_export(entry));
	else
	{
		va_start(args, argc);
		argv = va_arg(args, char **);
		va_end(args);
		return (check_input_arguments(g_shell, argv, symtab, name));
	}
	return (0);
}
