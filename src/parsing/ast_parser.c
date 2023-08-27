/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 00:48:44 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 19:52:39 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_word	*get_node_content(t_shell *g_shell, t_node **child)
{
	struct s_word	*w;
	char			*str;

	if ((*child)->type == NODE_INPUT || (*child)->type == NODE_OUTPUT
		|| (*child)->type == NODE_APPEND || (*child)->type == NODE_HEREDOC)
	{
		*child = (*child)->next_sibling;
		return (NULL);
	}
	str = (*child)->val.str;
	if (!str)
		return (NULL);
	w = expand(g_shell, str);
	if (!w)
		return (NULL);
	return (w);
}

// void	parse_ast(t_shell *g_shell, t_node *node, int *argc, int *targc,
// 		char ***argv)
void	parse_ast(t_shell *g_shell, t_node *node, int **args,
		char ***argv)
{
	struct s_word	*w;
	t_node			*child;
	char			*arg;

	child = node->first_child;
	while (child)
	{
		w = get_node_content(g_shell, &child);
		if (!w)
			continue ;
		while (w)
		{
			if (check_buffer_bounds(g_shell, args[0], args[1], argv))
			{
				arg = my_malloc(&g_shell->memory, ft_strlen(w->data) + 1);
				if (arg)
				{
					ft_strcpy(arg, w->data);
					(*argv)[(*args[0])++] = arg;
				}
			}
			w = w->next;
		}
		child = child->next_sibling;
	}
	if (check_buffer_bounds(g_shell, args[0], args[1], argv))
		(*argv)[(*args[0])] = NULL;
}
