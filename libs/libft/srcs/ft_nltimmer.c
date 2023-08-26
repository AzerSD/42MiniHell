/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nltimmer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:43:03 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/26 15:44:36 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "../includes/libft.h"

void	remove_trailing_newlines(char *str, size_t bufsz)
{
	if (!str || bufsz == 0)
		return ;
	for (ssize_t i = bufsz - 1; i >= 0; --i)
	{
		if (str[i] == '\n')
			str[i] = '\0';
		else if (str[i] != '\0')
			break ;
	}
}
