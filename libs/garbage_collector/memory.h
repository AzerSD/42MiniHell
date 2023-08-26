/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:32:19 by asioud            #+#    #+#             */
/*   Updated: 2023/08/26 23:00:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <types/types.h>
# include <unistd.h>

typedef struct s_memory_block
{
	void					*adresse;
	size_t					size;
	struct s_memory_block	*next;
}							t_memory_block;

void						*add_mem_block(void **p_head, size_t size);
void						remove_mem_block(void **p_head, void *ptr);
void						*my_malloc(void **p_head, size_t size);
void						my_free(void **p_head, void *adresse);
void						free_all_mem(void **p_head);
void						display_memory(void *p_head);
void						*my_realloc(void **phead, void *ptr, size_t size);
#endif
