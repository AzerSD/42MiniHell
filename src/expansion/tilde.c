/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/08/26 15:56:15 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/26 15:56:15 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home_from_symtab(t_shell *g_shell)
{
	struct s_symtab_entry	*entry;
	char					*home;

	home = NULL;
	entry = get_symtab_entry(g_shell, "HOME");
	if (entry && entry->val)
		home = entry->val;
	else
		return (NULL);
	return (home);
}

char	*tilde_expansion(t_shell *g_shell, char *s)
{
	char	*home;
	char	*s2;
	size_t	len;

	home = NULL;
	len = ft_strlen(s);
	s2 = NULL;
	if (len == 1)
		home = find_home_from_symtab(g_shell);
	if (!home)
		return (NULL);
	s2 = my_malloc(&g_shell->memory, ft_strlen(home) + 1);
	if (!s2)
		return (NULL);
	ft_strcpy(s2, home);
	return (s2);
}
