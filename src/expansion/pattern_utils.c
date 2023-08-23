/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:55:24 by asioud            #+#    #+#             */
/*   Updated: 2023/08/23 22:52:18 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_match(t_match *match)
{
	match->smatch = NULL;
	match->lmatch = NULL;
}

bool match(const char *pattern, const char *string) {
    while (*pattern != '\0' && *string != '\0') {
        if (*pattern == '?') {
            // '?' matches any single character
            pattern++;
            string++;
        } else if (*pattern == '*') {
            // '*' matches zero or more characters
            pattern++;
            while (*string != '\0') {
                if (match(pattern, string)) {
                    return true;
                }
                string++;
            }
            return match(pattern, string); // Try matching the rest of the pattern
        } else {
            // Regular character comparison
            if (*pattern != *string) {
                return false;
            }
            pattern++;
            string++;
        }
    }
    
    // Check if both pattern and string are at the end
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
