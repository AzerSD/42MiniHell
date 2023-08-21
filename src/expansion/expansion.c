/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:17 by asioud            #+#    #+#             */
/*   Updated: 2023/08/20 19:31:19 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	norm_tilde(char **p2, int *tilde_quoted)
{
	int	i;

	if (**p2 == '\\')
	{
		*tilde_quoted = 1;
		(*p2)++;
	}
	else if (**p2 == '"' || **p2 == '\'')
	{
		i = find_closing_quote(*p2);
		if (i)
		{
			*tilde_quoted = 1;
			*p2 += i;
		}
	}
	else if (**p2 == '/')
		return (1);
	(*p2)++;
	return (0);
}

void	check_tilde(char **pstart, char **p, int in_double_quotes)
{
	char	*p2;
	int		tilde_quoted;
	int		len;

	if (**p == '~' && !in_double_quotes)
	{
		tilde_quoted = 0;
		p2 = *p + 1;
		while (*p2)
		{
			if (norm_tilde(&p2, &tilde_quoted))
				break ;
		}
		if (tilde_quoted)
		{
			*p = p2;
			return ;
		}
		len = p2 - *p;
		substitute_word(pstart, p, len, tilde_expansion, !in_double_quotes);
	}
}

int	init_expand(t_m *m, char *orig_word)
{
	m->in_dquotes = 0;
	m->in_squotes = 0;
	if (!orig_word)
		return (1);
	if (!*orig_word)
		return (0);
	m->pstart = ft_strdup(orig_word);
	if (!m->pstart)
		return (1);
	m->p = m->pstart;
	m->escaped = 0;
	return (1);
}

struct s_word	*expand(char *orig_word)
{
	t_m				*m;
	struct s_word	*words;
	struct s_word	*w;

	m = (t_m *)my_malloc(g_shell.memory, sizeof(t_m));
	if (!init_expand(m, orig_word))
	{
		w = make_word(orig_word);
		free(m);
		return (w);
	}
	while (*(m->p))
	{
		m->escaped = 0;
		check_tilde(&(m->pstart), &(m->p), m->in_dquotes);
		check_double_quotes(&(m->p), &(m->in_dquotes), (m->in_squotes));
		if (!*(m->p))
			break ;
		check_single_quotes(&(m->p), &(m->in_dquotes), &(m->in_squotes));
		if (!*(m->p))
			break ;
		check_backslash(&(m->p), &(m->escaped));
		check_dollar_sign(&(m->pstart), &(m->p), m->in_squotes, &m->escaped);
		(m->p)++;
	}
	words = make_word(m->pstart);
	words = pathnames_expand(words);
	if (m->pstart)
		free(m->pstart);
	if (m)
		free(m);
	return (remove_quotes(words), words);
}

void	free_all_words(struct s_word *first)
{
	struct s_word	*del;

	while (first)
	{
		del = first;
		first = first->next;
		if (del->data)
			my_free(&g_shell.memory, del->data);
		my_free(&g_shell.memory, del);
	}
}
