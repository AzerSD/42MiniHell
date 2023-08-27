/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:09:50 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 22:41:46 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_word(struct s_word *word, int *in_double_quotes)
{
	char	*p;

	p = word->data;
	while (*p)
		handle_char(&p, in_double_quotes);
	word->len = ft_strlen(word->data);
}

void	substitute_norm(t_shell *g_shell, char ***poop, \
		char *(func)(t_shell *, char *), size_t *len)
{
	*poop[0] = malloc(*len + 1);
	if (!*poop[0])
	{
		(*poop[2]) += *len;
		return ;
	}
	ft_strncpy(*poop[0], *poop[2], *len);
	(*poop[0])[(*len)--] = '\0';
	if (func)
	{
		*poop[1] = func(g_shell, *poop[0]);
		if (*poop[1] == INVALID_VAR)
			*poop[1] = NULL;
		if (*poop[1])
			free(*poop[0]);
	}
	else
		*poop[1] = *poop[0];
}

int	substitute_word(t_shell *g_shell, char ***startp, size_t *lenquot,
		char *(func)(t_shell *, char *))
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	substitute_norm(g_shell, (char **[]){&tmp, &tmp2, startp[1]}, \
		func, &lenquot[0]);
	if (!tmp2)
		return (0);
	i = (*startp[1]) - (*startp[0]);
	tmp = quote_val(g_shell, tmp2, lenquot[1]);
	free(tmp2);
	if (tmp)
	{
		tmp2 = substitute_str(g_shell, *startp[0], tmp, \
			(size_t[]){i, i + lenquot[0]});
		if (tmp2)
		{
			(*startp[0]) = tmp2;
			lenquot[0] = ft_strlen(tmp);
		}
	}
	(*startp[1]) = (*startp[0]) + i + lenquot[0] - 1;
	return (1);
}

char	*word_expand_to_str(t_shell *g_shell, char *word)
{
	struct s_word	*w;
	char			*res;

	w = expand(g_shell, word);
	if (!w)
		return (NULL);
	res = wordlist_to_str(g_shell, w);
	free_all_words(g_shell, w);
	return (res);
}

struct s_word	*make_word(t_shell *g_shell, char *str)
{
	struct s_word	*word;
	size_t			len;
	char			*data;

	word = my_malloc(&g_shell->memory, sizeof(struct s_word));
	if (!word)
		return (NULL);
	len = ft_strlen(str);
	data = my_malloc(&g_shell->memory, len + 1);
	if (!data)
	{
		free(word);
		return (NULL);
	}
	ft_strcpy(data, str);
	word->data = data;
	word->len = len;
	word->next = NULL;
	return (word);
}
