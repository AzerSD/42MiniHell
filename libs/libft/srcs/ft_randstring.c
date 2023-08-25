/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:52:59 by asioud            #+#    #+#             */
/*   Updated: 2023/08/25 12:23:16 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*randstr_initiator(void)
{
	static char	*charset;

	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHI\
		JKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	return (charset);
}

void	key_calc(int seed, int *keyp, char *charset)
{
	*keyp = (seed * 1103515245 + 12345) & 0x7FFF;
	*keyp = *keyp % (int)ft_strlen(charset);
}

char	*randstr_malloc(size_t length)
{
	char	*random_string;

	random_string = malloc(sizeof(char) * (length + 1));
	if (!random_string)
		return (NULL);
	return (random_string);
}

char	*ft_randstring(size_t length)
{
	int			key;
	size_t		n;
	char		*random_string;
	int			seed;
	static char	*charset;

	charset = randstr_initiator();
	random_string = randstr_malloc(length);
	seed = 0;
	key = 0;
	if (length && random_string)
	{
		n = 0;
		while (n < length)
		{
			key_calc(seed, &key, charset);
			random_string[n] = charset[key];
			seed += n + 1;
			n++;
		}
		random_string[length] = '\0';
	}
	return (random_string);
}

// key = (seed * 1103515245 + 12345) & 0x7FFF;
// key = key % (int)(sizeof(charset) - 1);
