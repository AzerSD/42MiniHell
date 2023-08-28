/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:46:54 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/28 02:00:49 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_asterisk_in_match(const char *pattern, const char *string)
{
	while (*string != '\0')
	{
		if (match(pattern, string))
			return (true);
		string++;
	}
	return (match(pattern, string));
}

char	*create_final_string(char *before, char *s2, char *after, char *final)
{
	ft_strcpy(final, before);
	ft_strcat(final, s2);
	ft_strcat(final, after);
	return (final);
}

void	free_all_words(t_shell *g_shell, struct s_word *first)
{
	struct s_word	*del;

	while (first)
	{
		del = first;
		first = first->next;
		if (del->data)
			my_free(&g_shell->memory, del->data);
		my_free(&g_shell->memory, del);
	}
}
