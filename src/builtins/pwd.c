/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/08/23 23:11:55 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int argc, ...)
{
	struct s_symtab_entry	*s;
	struct s_symtab			*symtab;

	symtab = SHELL_INSTANCE.s_symtab_stack.local_symtab;
	(void)argc;
	s = do_lookup("PWD", symtab);
	if (s)
		ft_printf_fd(1, "%s\n", s->val);
	SHELL_INSTANCE.status = 0;
	return (0);
}
