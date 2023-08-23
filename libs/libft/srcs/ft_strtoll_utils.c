/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:50:21 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/23 23:16:17 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_strtoll_helpers.h"
#include "../includes/libft.h"

int	ft_isxdigit(char c)
{
	if (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

t_strtoll	*strtoll_init(void)
{
	t_strtoll	*strtoll;

	strtoll = (t_strtoll *)malloc(sizeof(t_strtoll));
	if (!strtoll)
		return (NULL);
	strtoll->s = NULL;
	strtoll->neg = 0;
	strtoll->any = 0;
	strtoll->cutlim = 0;
	strtoll->c = 0;
	strtoll->cutoff = 0;
	strtoll->start = NULL;
	return (strtoll);
}
