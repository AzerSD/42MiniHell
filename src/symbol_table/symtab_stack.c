/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:26:53 by asioud            #+#    #+#             */
/*   Updated: 2023/04/12 19:26:53 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	symtab_stack_add(t_shell *g_shell, struct s_symtab *symtab)
{
	g_shell->s_symtab_stack.symtab_list \
	[g_shell->s_symtab_stack.symtab_count++] = symtab;
	g_shell->s_symtab_stack.local_symtab = symtab;
}

struct s_symtab	*symtab_stack_push(t_shell *g_shell)
{
	struct s_symtab	*st;

	st = new_symtab(g_shell);
	symtab_stack_add(g_shell, st);
	return (st);
}

struct s_symtab	*symtab_stack_pop(t_shell *g_shell)
{
	struct s_symtab	*st;

	if (g_shell->s_symtab_stack.symtab_count == 0)
		return (NULL);
	st = g_shell->s_symtab_stack.symtab_list \
		[g_shell->s_symtab_stack.symtab_count - 1];
	g_shell->s_symtab_stack.symtab_list \
	[--g_shell->s_symtab_stack.symtab_count] = NULL;
	if (g_shell->s_symtab_stack.symtab_count == 0)
	{
		g_shell->s_symtab_stack.local_symtab = NULL;
		g_shell->s_symtab_stack.global_symtab = NULL;
	}
	else
		g_shell->s_symtab_stack.local_symtab = \
		g_shell->s_symtab_stack.symtab_list
		[g_shell->s_symtab_stack.symtab_count - 1];
	return (st);
}

struct s_symtab	*get_local_symtab(t_shell *g_shell)
{
	return (g_shell->s_symtab_stack.local_symtab);
}

struct s_symtab	*get_global_symtab(t_shell *g_shell)
{
	return (g_shell->s_symtab_stack.global_symtab);
}
