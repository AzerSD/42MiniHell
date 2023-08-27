/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:33:12 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/28 01:24:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token(t_cli *cli, t_curr_tok *curr, char nc, int *endloop)
{
	if (nc == '"' || nc == '\'' || nc == '`')
		handle_quotes(cli, curr, nc);
	else if (nc == '\\')
		handle_backslash(cli, curr);
	else if (nc == '$')
		handle_dollar_sign(cli, curr);
	else if (nc == ' ' || nc == '\t')
		handle_whitespace(curr, endloop);
	else if (nc == '\n')
		handle_newline(cli, curr, endloop);
	else if (nc == '=')
		handle_equals_sign(curr);
	else if (nc == '|')
		handle_pipe(cli, curr, endloop);
	else if (nc == '>' || nc == '<')
		handle_redirection(cli, curr, endloop, nc);
	else
		add_to_buf(nc, curr);
}

void	init_curr_tok(t_curr_tok *curr)
{
	curr->tok_buff = NULL;
	curr->tok_buff_size = 0;
	curr->tok_buff_index = -1;
	curr->tok_type = PARSE_DEFAULT;
}

int	helper(t_cli *cli, t_curr_tok *curr, char *nc, int *endloop)
{
	handle_token(cli, curr, *nc, endloop);
	if (*endloop == 1)
	{
		if (ft_strchr("|<>", *nc))
		{
			*nc = peek_char(cli);
			if (ft_strchr("|<>", *nc))
				return (1);
		}
		return (-1);
	}
	*nc = get_next_char(cli);
	return (0);
}

void	another_helper(t_curr_tok *curr)
{
	if (curr->tok_buff_index >= curr->tok_buff_size)
		curr->tok_buff_index--;
}

t_local_vars	init_local_vars(void)
{
	t_local_vars	lv;

	lv.nc = 0;
	lv.endloop = 0;
	lv.out = 0;
	return (lv);
}
