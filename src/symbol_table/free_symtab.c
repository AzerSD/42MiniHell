/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:10:46 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/27 02:10:46 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_symtab(t_shell *g_shell, struct s_symtab *symtab)
{
	struct s_symtab_entry	*entry;
	struct s_symtab_entry	*next;

	if (symtab == NULL)
		return ;
	entry = symtab->first;
	while (entry)
	{
		if (entry->name)
			my_free(&g_shell->memory, entry->name);
		if (entry->val)
			my_free(&g_shell->memory, entry->val);
		if (entry->func_body)
			free_node_tree(g_shell, entry->func_body);
		next = entry->next;
		my_free(&g_shell->memory, entry);
		entry = next;
	}
	my_free(&g_shell->memory, symtab);
}

void	free_symtab_entry(t_shell *g_shell, struct s_symtab_entry *entry)
{
	if (entry->val)
		my_free(&g_shell->memory, entry->val);
	if (entry->func_body)
		free_node_tree(g_shell, entry->func_body);
	my_free(&g_shell->memory, entry->name);
	my_free(&g_shell->memory, entry);
}

struct s_symtab_entry	*add_to_symtab(t_shell *g_shell, const char *symbol)
{
	struct s_symtab			*st;
	struct s_symtab_entry	*entry;

	if (!symbol || symbol[0] == '\0')
		return (NULL);
	st = g_shell->s_symtab_stack.local_symtab;
	entry = do_lookup(symbol, st);
	if (entry)
		return (entry);
	entry = create_symtab_entry(g_shell, symbol);
	add_entry_to_symtab(st, entry);
	return (entry);
}

struct s_symtab_entry	*create_symtab_entry(t_shell *g_shell,
		const char *symbol)
{
	struct s_symtab_entry	*entry;

	entry = my_malloc(&(g_shell->memory), sizeof(struct s_symtab_entry));
	if (!entry)
	{
		ft_printf_fd(2, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(entry, 0, sizeof(struct s_symtab_entry));
	entry->name = my_malloc(&(g_shell->memory), ft_strlen(symbol) + 1);
	if (!entry->name)
	{
		ft_printf_fd(2, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(entry->name, symbol);
	return (entry);
}

int	remove_subsequent_entry(struct s_symtab_entry *entry,
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
