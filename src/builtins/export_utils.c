/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:03:26 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/27 02:58:10 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(t_shell *g_shell, const char *name, const char *value,
		int overwrite)
{
	struct s_symtab_entry	*entry;
	struct s_symtab			*symtab;

	symtab = get_local_symtab(g_shell);
	entry = do_lookup(name, symtab);
	if (entry != NULL && overwrite == 0)
		return (0);
	if (entry != NULL)
		update_entry(g_shell, entry, (char *)value, (char *)name);
	else
	{
		entry = create_symtab_entry(g_shell, name);
		if (entry == NULL)
		{
			perror("minishell: setenv: Memory allocation failed");
			return (-1);
		}
		symtab_entry_setval(g_shell, entry, (char *)value);
		add_entry_to_symtab(symtab, entry);
	}
	return (0);
}
