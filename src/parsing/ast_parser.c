/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 00:48:44 by asioud            #+#    #+#             */
/*   Updated: 2023/08/23 22:29:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_word	*get_node_content(t_node **child)
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
	w = expand(str);
	if (!w)
		return (NULL);
	return (w);
}

void	add_argument(char **argv, int *argc, const char *data)
{
	char	*arg;

	arg = my_malloc(&shell_instance.memory, ft_strlen(data) + 1);
	if (arg)
	{
		ft_strcpy(arg, data);
		argv[(*argc)++] = arg;
	}
}

void	parse_ast(t_node *node, int *argc, int *targc, char ***argv)
{
	struct s_word	*w;
	t_node			*child;

	child = node->first_child;
	while (child)
	{
		w = get_node_content(&child);
		if (!w)
			continue ;
		while (w)
		{
			if (check_buffer_bounds(argc, targc, argv))
				add_argument(*argv, argc, w->data);
			w = w->next;
		}
		child = child->next_sibling;
	}
	(*argv)[(*argc)] = NULL;
}

// void	parse_ast(t_node *node, int *argc, int *targc, char ***argv)
// {
// 	struct s_word	*w;
// 	t_node			*child;
// 	char			*arg;

// 	child = node->first_child;
// 	while (child)
// 	{
// 		w = get_node_content(&child);
// 		if (!w)
// 			continue ;
// 		while (w)
// 		{
// 			if (check_buffer_bounds(argc, targc, argv))
// 			{
// 				arg = my_malloc(&shell_instance.memory, ft_strlen(w->data) + 1);
// 				if (arg)
// 				{
// 					ft_strcpy(arg, w->data);
// 					(*argv)[(*argc)++] = arg;
// 				}
// 			}
// 			w = w->next;
// 		}
// 		child = child->next_sibling;
// 	}
// 	(*argv)[(*argc)] = NULL;
// }
