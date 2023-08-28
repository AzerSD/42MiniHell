/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:55:24 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 01:48:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_match(t_match *match)
{
	match->smatch = NULL;
	match->lmatch = NULL;
}

bool	match(const char *pattern, const char *string)
{
	while (*pattern != '\0' && *string != '\0')
	{
		if (*pattern == '?')
		{
			pattern++;
			string++;
		}
		else if (*pattern == '*')
		{
			pattern++;
			if (handle_asterisk_in_match(pattern, string))
				return (true);
			return (false);
		}
		else
		{
			if (*pattern != *string)
				return (false);
			pattern++;
			string++;
		}
	}
	return (*pattern == '\0' && *string == '\0');
}

int	has_glob_chars(char *p, size_t len)
{
	char	*p2;
	char	ob;
	char	cb;

	ob = 0;
	cb = 0;
	p2 = p + len;
	while (p < p2 && *p)
	{
		if (*p == '*' || *p == '?')
			return (1);
		else if (*p == '[')
			ob++;
		else if (*p == ']')
			cb++;
		p++;
	}
	if (ob && ob == cb)
		return (1);
	return (0);
}

int	is_match_found(char *pattern, int longest, t_match *m)
{
	char	*s;
	char	c;

	s = m->str + 1;
	c = *s;
	while (c)
	{
		*s = '\0';
		if (match(pattern, m->str) == 0)
		{
			if (!m->smatch)
			{
				if (!longest)
				{
					*s = c;
					return (1);
				}
				(m->smatch) = s;
			}
			m->lmatch = s;
		}
		*s = c;
		c = *(++s);
	}
	return (0);
}

void	check_pattern(char *pattern, int longest, t_match *m, char **s)
{
	while (*s > m->str)
	{
		if (match(pattern, m->str) == 0)
		{
			if (!m->smatch)
			{
				if (!longest)
					return ;
				m->smatch = *s;
			}
			m->lmatch = *s;
		}
		(*s)--;
	}
}
