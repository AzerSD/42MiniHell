/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:45:41 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/23 20:49:55 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

char	*ft_strstr(char *haystack, char *needle)
{
	char	*h;
	char	*n;

	if (!*needle)
		return (haystack);
	if (!haystack || !needle)
		return (NULL);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			h = haystack;
			n = needle;
			while (*h && *n && *h == *n)
			{
				h++;
				n++;
			}
			if (!*n)
				return (haystack);
		}
		haystack++;
	}
	return (NULL);
}

// int main() {
//     const char *haystack = "OpenAI is great!";
//     const char *needle = "AI";
//     const char *result = strstr(haystack, needle);

//     if (result) {
//         printf("Found: %s\n", result);
//     } else {
//         printf("Not Found\n");
//     }

//     return (0);
// }
