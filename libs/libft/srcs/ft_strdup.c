/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:10:08 by asioud            #+#    #+#             */
/*   Updated: 2023/08/26 22:56:10 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*out;

	len = ft_strlen((char *)str) + 1;
	out = ft_calloc(len + 1, sizeof(char));
	if (!out)
		return (NULL);
	ft_memcpy(out, str, len);
	return (out);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char name[] = "test";
// 	char *dst;
// 	dst = ft_strdup(name);
// 	printf("%s", dst);
// }
