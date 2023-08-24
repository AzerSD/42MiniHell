/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 18:12:42 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *g_shell, int argc, ...)
{
	struct s_symtab_entry	*s;
	struct s_symtab			*symtab;

	symtab = g_shell->s_symtab_stack.local_symtab;
	(void)argc;
	s = do_lookup("PWD", symtab);
	if (s)
		ft_printf_fd(1, "%s\n", s->val);
	g_shell->status = 0;
	return (0);
}
