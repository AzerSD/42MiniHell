/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 00:26:03 by asioud            #+#    #+#             */
/*   Updated: 2023/08/23 21:08:37 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_entry(struct s_symtab_entry *entry, char *new_val, char *name)
{
	entry = do_lookup(name, shell_instance.s_symtab_stack.local_symtab);
	if (!entry)
	{
		entry = add_to_symtab(name);
	}
	symtab_entry_setval(entry, new_val);
}

void	symtab_entry_setval(struct s_symtab_entry *entry, char *val)
{
	char	*val2;

	if (entry->val)
	{
		my_free(&shell_instance.memory, entry->val);
	}
	if (!val)
	{
		entry->val = NULL;
	}
	else
	{
		val2 = my_malloc(&shell_instance.memory, ft_strlen(val) + 1);
		if (val2)
			ft_strcpy(val2, val);
		else
			ft_printf_fd(STDERR_FILENO,
				"error: no memory for symbol table entry's value\n");
		entry->val = val2;
	}
}

struct s_symtab_entry	*get_symtab_entry(const char *str)
{
	int						i;
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	i = shell_instance.s_symtab_stack.symtab_count - 1;
	while (i >= 0)
	{
		symtab = shell_instance.s_symtab_stack.symtab_list[i];
		entry = do_lookup(str, symtab);
		if (entry)
		{
			return (entry);
		}
		i--;
	}
	return (NULL);
}

int	remove_entry_from_symtab(struct s_symtab_entry *entry, \
		struct s_symtab *symtab)
{
	int	res;

	res = 0;
	if (symtab->first == entry)
	{
		symtab->first = symtab->first->next;
		if (symtab->last == entry)
			symtab->last = NULL;
		res = 1;
	}
	else
	{
		res = remove_subsequent_entry(entry, symtab);
	}
	return (res);
}
