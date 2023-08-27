/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 04:41:52 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_parser
{
	t_token		*tok;
	t_cli		*cli;
	t_curr_tok	*curr;
	int			first_pipe;
}				t_parser;

t_node	*p_pipe(t_shell *g_shell, t_node **ptr, t_node **parent,
		int *first_pipe)
{
	t_node	*null_node;

	if (*first_pipe)
		*ptr = *parent;
	*parent = new_node(g_shell, NODE_PIPE);
	(*parent)->val.str = "|";
	add_child_node(*parent, *ptr);
	*ptr = *parent;
	null_node = new_node(g_shell, NODE_COMMAND);
	add_child_node(*ptr, null_node);
	*ptr = null_node;
	*first_pipe = 1;
	return (*ptr);
}

t_node	*p_word(t_shell *g_shell, t_token *tok, t_node *ptr,
		enum e_node_type type)
{
	t_node	*word;

	word = new_node(g_shell, type);
	set_node_val_str(g_shell, word, tok->text);
	if (!word)
	{
		free_node_tree(ptr);
		free_token(g_shell, tok);
		return (NULL);
	}
	add_child_node(ptr, word);
	return (ptr);
}

t_node	*p_redirection(t_shell *g_shell, t_node *ptr, t_parser *parser,
		enum e_node_type type)
{
	t_node	*redirection_node;
	t_node	*file_node;

	redirection_node = new_node(g_shell, type);
	set_node_val_str(g_shell, redirection_node, parser->tok->text);
	if (!redirection_node)
	{
		free_node_tree(ptr);
		return (free_token(g_shell, parser->tok), NULL);
	}
	free_token(g_shell, parser->tok);
	parser->tok = get_token(g_shell, parser->cli, parser->curr);
	if (parser->tok == EOF_TOKEN)
		return (free_node_tree(ptr), NULL);
	file_node = new_node(g_shell, NODE_FILE);
	set_node_val_str(g_shell, file_node, parser->tok->text);
	if (!file_node)
	{
		free_node_tree(ptr);
		return (free_token(g_shell, parser->tok), NULL);
	}
	add_child_node(redirection_node, file_node);
	add_child_node(ptr, redirection_node);
	return (ptr);
}

t_node	*parse_token(t_parsing *prs, t_node *ptr, t_node **parent_ptr,
		t_parser *parser)
{
	enum e_node_type	type;

	type = get_node_type(parser->curr->tok_type);
	if (type == NODE_PIPE)
	{
		ptr = p_pipe(prs->g_shell, &ptr, parent_ptr, &parser->first_pipe);
	}
	else if (type == NODE_INPUT || type == NODE_OUTPUT || type == NODE_APPEND)
	{
		ptr = p_redirection(prs->g_shell, ptr, parser, type);
	}
	else if (type == NODE_HEREDOC)
	{
		ptr = p_heredoc(prs, parser->cli, parser->curr, ptr);
	}
	else
	{
		ptr = p_word(prs->g_shell, parser->tok, ptr, type);
	}
	return (ptr);
}

t_node	*parse_cmd(t_parsing *prs, t_token *tok, t_curr_tok *curr)
{
	t_node				*ptr;
	t_node				*parent;
	t_parser			parser;
	enum e_node_type	type;

	parser.first_pipe = 0;
	if (!tok || !curr)
		return (NULL);
	type = get_node_type(curr->tok_type);
	ptr = new_node(prs->g_shell, type);
	parent = ptr;
	parser.cli = tok->cli;
	parser.tok = tok;
	parser.curr = curr;
	while (parser.tok != NULL && parser.tok != EOF_TOKEN)
	{
		if (parser.tok->text[0] == '\n')
		{
			free_token(prs->g_shell, parser.tok);
			break ;
		}
		ptr = parse_token(prs, ptr, &parent, &parser);
		parser.tok = get_token(prs->g_shell, parser.cli, parser.curr);
	}
	return (parent);
}

// t_node	*parse_token(t_parsing *prs, t_node *ptr, t_node **parent_ptr,
// 		t_parser *parser)
