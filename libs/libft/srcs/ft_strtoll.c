/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/22 21:22:33 by lhasmi           ###   ########.fr       */
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

int	ft_isxdigit(char c)
{
	if (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}
int ft_islower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int ft_isupper(char c)
{
	if (c >= 'A' && c <= 'Z')
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

static void	skip_whitespace(t_strtoll *strtoll)
{
	while (ft_iswspace((unsigned char)strtoll->c))
		strtoll->c = *strtoll->s++;
}

static void	handle_sign(t_strtoll *strtoll)
{
	if (strtoll->c == '-')
	{
		strtoll->neg = 1;
		strtoll->c = *strtoll->s++;
	}
	else if (strtoll->c == '+')
		strtoll->c = *strtoll->s++;
}

static void	handle_hex(t_strtoll *strtoll, int *base)
{
	if ((*base == 0 || *base == 16) && strtoll->c == '0' && (*strtoll->s == 'x'
			|| *strtoll->s == 'X') && ft_isxdigit(strtoll->s[1]))
	{
		strtoll->c = strtoll->s[1];
		strtoll->s += 2;
		*base = 16;
	}
}

static void	convert_digits(t_strtoll *strtoll, unsigned long long *acc,
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

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	t_strtoll			*strtoll;
	unsigned long long	acc;

	strtoll = strtoll_init();
	strtoll->start = nptr;
	strtoll->s = nptr;
	strtoll->c = *strtoll->s++;
	skip_whitespace(strtoll);
	handle_sign(strtoll);
	handle_hex(strtoll, &base);
	if (base == 0)
	{
		if (strtoll->c == '0')
			base = 8;
		else
			base = 10;
	}
	if (base < 2 || base > 36)
		return (errno = EINVAL, free(strtoll), 0);
	if (strtoll->neg)
		strtoll->cutoff = -(unsigned long long)LLONG_MIN;
	else
		strtoll->cutoff = LLONG_MAX;
	strtoll->cutlim = strtoll->cutoff % base;
	strtoll->cutoff /= base;
	acc = 0;
	convert_digits(strtoll, &acc, base);
	if (strtoll->any < 0)
	{
		if (strtoll->neg)
			acc = LLONG_MIN;
		else
			acc = LLONG_MAX;
		errno = ERANGE;
	}
	else if (strtoll->neg)
		acc = -acc;
	else if (!strtoll->any)
		strtoll->s = strtoll->start;
	if (endptr != NULL)
	{
		if (strtoll->any)
			*endptr = (char *)(strtoll->s - 1);
		else
			*endptr = (char *)(strtoll->s);
	}
	free(strtoll);
	return (acc);
}

// long long	ft_strtoll(const char *nptr, char **endptr, int base)
// {
// 	t_strtoll			*strtoll;
// 	unsigned long long	acc;

// 	strtoll = strtoll_init();
// 	strtoll ->s = nptr;
// 	acc = 0;
// 	// Skip white space
// 	do
// 	{
// 		strtoll ->c = *strtoll ->s++;
// 	} while (ft_iswspace((unsigned char)strtoll->c));
// 	// Handle sign
// 	if (strtoll ->c == '-')
// 	{
// 		strtoll ->neg = 1;
// 		strtoll ->c = *strtoll ->s++;
// 	}
// 	else if (strtoll -> c == '+')
// 		strtoll ->c = *strtoll ->s++;
// 	// Handle hex
// 	if ((base == 0 || base == 16) && strtoll ->c == '0' && (*strtoll ->s == 'x'
// 			|| *strtoll ->s == 'X')
// 		&& ft_isxdigit(strtoll ->s[1]))
// 	{
// 		strtoll ->c = strtoll ->s[1];
// 		strtoll ->s += 2;
// 		base = 16;
// 	}
// 	// Determine base
// 	if (base == 0){
// 		base = strtoll ->c == '0' ? 8 : 10;
// 	}
// 	if (base < 2 || base > 36){
// 		errno = EINVAL;
// 		goto noconv;
// 	}
// 	// Initialize variables for conversion
// 	strtoll ->cutoff = strtoll ->neg ?
// 		-(unsigned long long)LLONG_MIN : LLONG_MAX;
// 	strtoll ->cutlim = strtoll ->cutoff % base;
// 	strtoll ->cutoff /= base;
// 	acc = 0;
// 	// Convert digits
// 	for (;; strtoll ->c = *strtoll ->s++)
// 	{
// 		if (ft_isdigit(strtoll ->c))
// 			strtoll ->c -= '0';
// 		else if (ft_isupper(strtoll ->c))
// 			strtoll ->c -= 'A' - 10;
// 		else if (ft_islower(strtoll ->c))
// 			strtoll ->c -= 'a' - 10;
// 		else
// 			break ;
// 		if (strtoll ->c >= base)
// 			break ;
// 		if (strtoll ->any < 0 || acc > strtoll ->cutoff || (acc == strtoll
// 				->cutoff && strtoll ->c > strtoll ->cutlim))
// 			strtoll ->any = -1;
// 		else
// 		{
// 			strtoll ->any = 1;
// 			acc *= base;
// 			acc += strtoll ->c;
// 		}
// 	}
// 	// Handle result
// 	if (strtoll ->any < 0)
// 	{
// 		acc = strtoll ->neg ? LLONG_MIN : LLONG_MAX;
// 		errno = ERANGE;
// 	}
// 	else if (strtoll ->neg)
// 		acc = -acc;
// 	else if (!strtoll ->any)
// 	{
// 	noconv:
// 		strtoll ->s = nptr;
// 	}
// 	// Assign end pointer if required
// 	if (endptr != NULL)
// 		*endptr = (char *)(strtoll ->any ? strtoll ->s - 1 : strtoll ->s);
// 	free (strtoll);
// 	return (acc);
// }
