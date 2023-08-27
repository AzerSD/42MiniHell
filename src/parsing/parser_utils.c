/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:03:52 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/28 01:16:23 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_parser_init( t_parser *parser, t_token *tok, t_curr_tok *curr)
{
	parser->first_pipe = 0;
	parser->cli = tok->cli;
	parser->tok = tok;
	parser->curr = curr;
}

void	exit_with_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
