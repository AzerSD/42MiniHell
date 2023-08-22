/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:07:19 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/22 22:24:55 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_iswspace(const char nptr)
{
	if (nptr == ' ' || nptr == '\t' || nptr == '\n' || nptr == '\v'
		|| nptr == '\f' || nptr == '\r')
		return (1);
	return (0);
}

void	skip_whitespace(t_strtoll *strtoll)
{
	while (ft_iswspace((unsigned char)strtoll->c))
		strtoll->c = *strtoll->s++;
}

void	handle_sign(t_strtoll *strtoll)
{
	if (strtoll->c == '-')
	{
		strtoll->neg = 1;
		strtoll->c = *strtoll->s++;
	}
	else if (strtoll->c == '+')
		strtoll->c = *strtoll->s++;
}

void	handle_hex(t_strtoll *strtoll, int *base)
{
	if ((*base == 0 || *base == 16) && strtoll->c == '0' && (*strtoll->s == 'x'
			|| *strtoll->s == 'X') && ft_isxdigit(strtoll->s[1]))
	{
		strtoll->c = strtoll->s[1];
		strtoll->s += 2;
		*base = 16;
	}
}

void	convert_digits(t_strtoll *strtoll, unsigned long long *acc,
		int base)
{
	while (1)
	{
		if (ft_isdigit(strtoll->c))
			strtoll->c -= '0';
		else if (ft_isupper(strtoll->c))
			strtoll->c -= 'A' - 10;
		else if (ft_islower(strtoll->c))
			strtoll->c -= 'a' - 10;
		else
			break ;
		if (strtoll->c >= base)
			break ;
		if (strtoll->any < 0 || *acc > strtoll->cutoff
			|| (*acc == strtoll->cutoff && strtoll->c > strtoll->cutlim))
			strtoll->any = -1;
		else
		{
			strtoll->any = 1;
			*acc *= base;
			*acc += strtoll->c;
		}
		strtoll->c = *strtoll->s++;
	}
}
