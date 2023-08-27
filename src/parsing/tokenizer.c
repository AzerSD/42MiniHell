/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:27 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 01:23:37 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		*it_tk_bf(t_shell *g_shell, t_cli *cli, t_curr_tok *curr);

static t_token	*create_token(t_shell *g_shell, char *str)
{
	t_token	*tok;
	char	*nstr;

	tok = my_malloc(&(g_shell->memory), sizeof(t_token));
	if (!tok)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->text_len = ft_strlen(str);
	nstr = my_malloc(&(g_shell->memory), tok->text_len + 1);
	if (!nstr)
	{
		free(tok);
		return (NULL);
	}
	ft_strcpy(nstr, str);
	tok->text = nstr;
	return (tok);
}

t_token	*get_token(t_shell *g_shell, t_cli *cli, t_curr_tok *curr)
{
	t_token			*tok;
	t_local_vars	lv;

	lv = init_local_vars();
	init_curr_tok(curr);
	lv.nc = get_next_char(cli);
	if (lv.nc == ERRCHAR || lv.nc == EOF || it_tk_bf(g_shell, cli,
			curr) != 0)
		return (EOF_TOKEN);
	while (lv.nc != EOF)
	{
		lv.out = helper(cli, curr, &(lv.nc), &(lv.endloop));
		if (lv.out == 1)
			return (EOF_TOKEN);
		else if (lv.out == -1)
			break ;
	}
	if (curr->tok_buff_index == 0)
		return (EOF_TOKEN);
	another_helper(curr);
	curr->tok_buff[curr->tok_buff_index] = '\0';
	tok = create_token(g_shell, curr->tok_buff);
	tok->cli = cli;
	return (tok);
}

static void	*set_error_and_return(int flag)
{
	if (flag == ENODATA)
		errno = ENODATA;
	else if (flag == ENOMEM)
		errno = ENOMEM;
	return (EOF_TOKEN);
}

static void	*it_tk_bf(t_shell *g_shell, t_cli *cli, t_curr_tok *curr)
{
	if (!cli || !cli->buffer || !cli->buff_size)
		return (set_error_and_return(ENODATA));
	if (!curr->tok_buff)
	{
		curr->tok_buff_size = 1024;
		curr->tok_buff = my_malloc(&(g_shell->memory), curr->tok_buff_size);
		if (!curr->tok_buff)
			return (set_error_and_return(ENOMEM));
	}
	curr->tok_buff_index = 0;
	curr->tok_buff[0] = '\0';
	curr->tok_type = PARSE_DEFAULT;
	return (0);
}
