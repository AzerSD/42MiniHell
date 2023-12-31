/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:33:04 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 21:16:55 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*my_realloc(void **phead, void *ptr, size_t size)
{
	size_t	i;
	char	*out;

	i = 0;
	if (!ptr)
		return (NULL);
	out = my_malloc(phead, size);
	if (!out)
		return (NULL);
	while (size-- > 0)
	{
		out[i] = ((uint8_t *)ptr)[i];
		i++;
	}
	return (out);
}

void	*add_mem_block(void **p_head, size_t size)
{
	t_memory_block	*block;

	block = (t_memory_block *) malloc(sizeof(t_memory_block) + size);
	if (!block)
		return (0);
	block->adresse = malloc(size);
	if (!block->adresse)
		return (0);
	block->size = size;
	block->next = *p_head;
	*p_head = block;
	return (block->adresse);
}

void	remove_mem_block(void **p_head, void *ptr)
{
	t_memory_block	*block;
	t_memory_block	*prev;

	block = *p_head;
	prev = NULL;
	while (block)
	{
		if (block->adresse == ptr)
		{
			if (prev == NULL)
				*p_head = block->next;
			else
				prev->next = block->next;
			free(block);
			block = ((void *)0);
			break ;
		}
		prev = block;
		block = block->next;
	}
}

void	*my_malloc(void **p_head, size_t size)
{
	return (add_mem_block(p_head, size));
}

void	my_free(void **p_head, void *adresse)
{
	remove_mem_block(p_head, adresse);
	free(adresse);
	adresse = ((void *) 0);
}

void	free_all_mem(void **p_head)
{
	int					i;
	t_memory_block		*node;
	t_memory_block		*next;

	i = 1;
	if (p_head == NULL)
		return ;
	next = NULL;
	node = *p_head;
	while (node != NULL && node->adresse)
	{
		next = node->next;
		if (node->adresse != ((void *) 0))
			free(node->adresse);
		node->adresse = ((void *) 0);
		free(node);
		node = ((void *) 0);
		node = next;
		i++;
	}
	*p_head = NULL;
}
