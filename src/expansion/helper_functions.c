/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:54:23 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/28 01:54:23 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_word_and_advance(char **dest, struct s_word *w)
{
	ft_strcpy(*dest, w->data);
	*dest += w->len;
	ft_strcpy(*dest, " ");
	*dest += 1;
}

char	*wordlist_to_str(t_shell *g_shell, struct s_word *word)
{
	size_t			len ;
	struct s_word	*w;
	char			*str;
	char			*str2;

	len = 0;
	w = word;
	if (!word)
		return (NULL);
	while (w)
	{
		len += w->len + 1;
		w = w->next;
	}
	str = my_malloc(&g_shell->memory, len + 1);
	str2 = str;
	w = word;
	while (w)
	{
		copy_word_and_advance(&str2, w);
		w = w->next;
	}
	str2[-1] = '\0';
	return (str);
}

void	delete_char_at(char *str, size_t index)
{
	char	*p1;
	char	*p2;

	p1 = str + index;
	p2 = p1 + 1;
	while (*p1)
		*p1++ = *p2++;
}

int	is_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
	return (1);
}

char	*substitute_str(t_shell *g_shell, char *s1, char *s2, size_t *range)
{
	char	*before;
	size_t	afterlen;
	size_t	totallen;
	char	*after;
	char	*final;

	before = (char *)my_malloc(&g_shell->memory, (range[0] + 1)
			* sizeof(char));
	ft_strncpy(before, s1, range[0]);
	before[range[0]] = '\0';
	afterlen = ft_strlen(s1) - range[1] + 1;
	after = (char *)my_malloc(&g_shell->memory, afterlen * sizeof(char));
	if (!after)
		return (NULL);
	ft_strcpy(after, s1 + range[1] + 1);
	totallen = range[0] + afterlen + ft_strlen(s2);
	final = my_malloc(&g_shell->memory, totallen + 1);
	if (!final)
		return (my_free(&g_shell->memory, final), NULL);
	if (!totallen)
		final[0] = '\0';
	else
		final = create_final_string(before, s2, after, final);
	return (my_free(&g_shell->memory, after), final);
}
