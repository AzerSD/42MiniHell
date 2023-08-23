/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:50:34 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 19:50:34 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home_from_symtab(void)
{
	struct s_symtab_entry	*entry;
	char					*home;

	home = NULL;
	entry = get_symtab_entry("HOME");
	if (entry && entry->val)
		home = entry->val;
	else
	{
		return (NULL);
	}
	return (home);
}

char	*tilde_expansion(char *s)
{
	char	*home;
	char	*s2;
	size_t	len;

	home = NULL;
	len = ft_strlen(s);
	s2 = NULL;
	if (len == 1)
		home = find_home_from_symtab();
	if (!home)
		return (NULL);
	s2 = my_malloc(&SHELL_INSTANCE.memory, ft_strlen(home) + 1);
	if (!s2)
		return (NULL);
	ft_strcpy(s2, home);
	return (s2);
}
