/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:07 by asioud            #+#    #+#             */
/*   Updated: 2023/08/19 21:18:18 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(enum e_node_type type)
{
	t_node	*node;

	node = my_malloc(&g_shell.memory, sizeof(t_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

void	add_child_node(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent || !child)
		return ;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

void	add_parent_node(t_node *child, t_node *parent)
{
	if (child == NULL || parent == NULL)
	{
		return ;
	}
	add_child_node(parent, child);
}

void	set_node_val_str(t_node *node, char *val)
{
	char	*val2;

	node->val_type = VAL_STR;
	if (!val)
		node->val.str = NULL;
	else
	{
		//use ft_strdup instead of ft_strcpy to avoid segfault when val is NULL (ex: echo $)
		val2 = ft_strdup(val);
		if (!val2)
			node->val.str = NULL;
		else
			node->val.str = val2;
	}
}

void	free_node_tree(t_node *node)
{
	t_node	*child;
	t_node	*next;

	if (!node)
		return ;
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	if (node->val_type == VAL_STR)
		if (node->val.str)
			free(node->val.str);
	free(node);
}
