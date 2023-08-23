/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:03:26 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/23 22:15:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	struct s_symtab_entry	*entry;// Edge case handling
	struct s_symtab *symtab;

	symtab = get_local_symtab();// Or use get_global_symtab() as needed
	entry = do_lookup(name, symtab);// Check if the entry already exists
	if (entry != NULL && overwrite == 0)
		return (0); // Do not overwrite if the flag is set to 0
	if (entry != NULL)// Update the existing value if an entry with the given name already exists
		update_entry(entry, (char *)value, (char *)name);
	else
	{// Create a new entry if it doesn't exist
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
