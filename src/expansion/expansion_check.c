/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:49:41 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 22:43:17 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_single_quotes(char **p, int *in_double_quotes,
		int *in_single_quotes)
{
	if (**p == '\'' && !*in_double_quotes)
	{
		*in_single_quotes = !(*in_single_quotes);
		(*p)++;
	}
}

void	check_double_quotes(char **p, int *in_double_quotes,
		int in_single_quotes)
{
	if (**p == '"' && !in_single_quotes)
	{
		*in_double_quotes = !(*in_double_quotes);
		(*p)++;
	}
}

void	check_backslash(char **p, int *escaped)
{
	if (**p == '\\')
		*escaped = 1;
}

// int	substitute_word(t_shell *g_shell, char ***startp, size_t *lenquot,
// 		char *(func)(t_shell *, char *))
void	check_dollar_sign(t_shell *g_shell, char **pstart, char **p)
{
	char	c;
	char	*p2;

	c = (*p)[1];
	if (c == '\"')
		(*pstart)++;
	else if (c == '?')
		substitute_word(g_shell, (char **[]){pstart, p}, \
			(size_t []){2, 0}, var_expand);
	else
	{
		if (!ft_isalpha((*p)[1]) && (*p)[1] != '_')
			return ;
		p2 = *p + 1;
		while (ft_isalnum(*p2) || *p2 == '_')
			p2++;
		if (p2 == *p + 1)
			return ;
		substitute_word(g_shell, (char **[]){pstart, p}, \
			(size_t []){p2 - *p, 0}, var_expand);
	}
}
