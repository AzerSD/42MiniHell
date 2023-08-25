/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:03:26 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/25 16:57:33 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	struct s_symtab_entry	*entry;
	struct s_symtab			*symtab;

	symtab = get_local_symtab();
	entry = do_lookup(name, symtab);
	if (entry != NULL && overwrite == 0)
		return (0);
	if (entry != NULL)
		update_entry(entry, (char *)value, (char *)name);
	else
	{
		entry = create_symtab_entry(name);
		if (entry == NULL)
		{
			perror("minishell: setenv: Memory allocation failed");
			return (-1);
		}
		symtab_entry_setval(entry, (char *)value);
		add_entry_to_symtab(symtab, entry);
	}
	return (0);
}

void	print_export_error(void)
{
	const char	*export_err_msg;

	export_err_msg = "bash: export: --: invalid option\nexport: "
		"usage: export [-nf] [name[=value] ...] \
			or export -p\n ";
	ft_printf_fd(STDERR_FILENO, export_err_msg);
}
