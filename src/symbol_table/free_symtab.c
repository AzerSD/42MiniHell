/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 00:50:39 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 00:50:39 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_symtab(struct s_symtab *symtab)
{
	struct s_symtab_entry	*entry;
	struct s_symtab_entry	*next;

	if (symtab == NULL)
		return ;
	entry = symtab->first;
	while (entry)
	{
		if (entry->name)
			my_free(&shell_instance.memory, entry->name);
		if (entry->val)
			my_free(&shell_instance.memory, entry->val);
		if (entry->func_body)
			free_node_tree(entry->func_body);
		next = entry->next;
		my_free(&shell_instance.memory, entry);
		entry = next;
	}
	my_free(&shell_instance.memory, symtab);
}

void	free_symtab_entry(struct s_symtab_entry *entry)
{
	if (entry->val)
		my_free(&shell_instance.memory, entry->val);
	if (entry->func_body)
		free_node_tree(entry->func_body);
	my_free(&shell_instance.memory, entry->name);
	my_free(&shell_instance.memory, entry);
}

struct s_symtab_entry	*add_to_symtab(const char *symbol)
{
	struct s_symtab			*st;
	struct s_symtab_entry	*entry;

	if (!symbol || symbol[0] == '\0')
		return (NULL);
	st = shell_instance.s_symtab_stack.local_symtab;
	entry = do_lookup(symbol, st);
	if (entry)
		return (entry);
	entry = create_symtab_entry(symbol);
	add_entry_to_symtab(st, entry);
	return (entry);
}

struct s_symtab_entry	*create_symtab_entry(const char *symbol)
{
	struct s_symtab_entry	*entry;

	entry = my_malloc(&shell_instance.memory, sizeof(struct s_symtab_entry));
	if (!entry)
	{
		ft_printf_fd(2, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(entry, 0, sizeof(struct s_symtab_entry));
	entry->name = my_malloc(&shell_instance.memory, ft_strlen(symbol) + 1);
	if (!entry->name)
	{
		ft_printf_fd(2, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(entry->name, symbol);
	return (entry);
}

int	remove_subsequent_entry(struct s_symtab_entry *entry, \
		struct s_symtab *symtab)
{
	struct s_symtab_entry	*e;
	struct s_symtab_entry	*p;

	e = symtab->first;
	p = NULL;
	while (e && e != entry)
	{
		p = e;
		e = e->next;
	}
	if (e == entry)
	{
		p->next = entry->next;
		return (1);
	}
	return (0);
}
