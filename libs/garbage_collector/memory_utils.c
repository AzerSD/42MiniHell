/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:59:06 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/27 03:05:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	free_all_mem(void **p_head)
{
	int				i;
	t_memory_block	*node;
	t_memory_block	*next;

	i = 1;
	if (p_head == NULL)
		return ;
	next = NULL;
	node = *p_head;
	while (node != NULL && node->adresse)
	{
		next = node->next;
		if (node->adresse != ((void *)0))
			free(node->adresse);
		node->adresse = ((void *)0);
		free(node);
		node = ((void *)0);
		node = next;
		i++;
	}
	*p_head = NULL;
}
