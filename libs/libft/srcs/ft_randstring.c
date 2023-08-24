/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:52:59 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 22:28:23 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <unistd.h>

char	*ft_randstring(size_t length)
{
	char	*random_string;
	int		key;
	size_t	n;
	int		seed;

	static char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHI\
		JKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	seed = 0;
	random_string = NULL;
	if (length)
	{
		random_string = malloc(sizeof(char) * (length + 1));
		if (random_string)
		{
			n = 0;
			while (n < length)
			{
				key = (seed * 1103515245 + 12345) & 0x7FFF;
				key = key % (int)(sizeof(charset) - 1);
				random_string[n] = charset[key];
				seed += n + 1;
				n++;
			}
			random_string[length] = '\0';
		}
	}
	return (random_string);
}
