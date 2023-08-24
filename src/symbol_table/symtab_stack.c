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

static void	symtab_stack_add(struct s_symtab *symtab)
{
	SHELL_INSTANCE.s_symtab_stack.symtab_list \
	[SHELL_INSTANCE.s_symtab_stack.symtab_count++] = symtab;
	SHELL_INSTANCE.s_symtab_stack.local_symtab = symtab;
}

struct s_symtab	*symtab_stack_push(void)
{
	struct s_symtab	*st;

	st = new_symtab();
	symtab_stack_add(st);
	return (st);
}

struct s_symtab	*symtab_stack_pop(void)
{
	struct s_symtab	*st;

	if (SHELL_INSTANCE.s_symtab_stack.symtab_count == 0)
		return (NULL);
	st = SHELL_INSTANCE.s_symtab_stack.symtab_list \
		[SHELL_INSTANCE.s_symtab_stack.symtab_count - 1];
	SHELL_INSTANCE.s_symtab_stack.symtab_list \
	[--SHELL_INSTANCE.s_symtab_stack.symtab_count] = NULL;
	if (SHELL_INSTANCE.s_symtab_stack.symtab_count == 0)
	{
		SHELL_INSTANCE.s_symtab_stack.local_symtab = NULL;
		SHELL_INSTANCE.s_symtab_stack.global_symtab = NULL;
	}
	else
		SHELL_INSTANCE.s_symtab_stack.local_symtab = \
		SHELL_INSTANCE.s_symtab_stack.symtab_list
		[SHELL_INSTANCE.s_symtab_stack.symtab_count - 1];
	return (st);
}

struct s_symtab	*get_local_symtab(void)
{
	return (SHELL_INSTANCE.s_symtab_stack.local_symtab);
}

struct s_symtab	*get_global_symtab(void)
{
	return (SHELL_INSTANCE.s_symtab_stack.global_symtab);
}
