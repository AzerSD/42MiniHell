/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/22 22:21:28 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_strtoll_helpers.h"
#include "../includes/libft.h"

static int	handle_base(t_strtoll *strtoll)
{
	if (strtoll->c == '0')
		return (8);
	else
		return (10);
}

static long long	handle_result(t_strtoll *strtoll, unsigned long long acc)
{
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
	return (acc);
}

static void	handle_endptr(t_strtoll *strtoll, char **endptr)
{
	if (endptr != NULL)
	{
		if (strtoll->any)
			*endptr = (char *)(strtoll->s - 1);
		else
			*endptr = (char *)(strtoll->s);
	}
}

static void	initialize_conversion(t_strtoll *strtoll, unsigned long long *acc,
		int base)
{
	strtoll->cutlim = strtoll->cutoff % base;
	strtoll->cutoff /= base;
	*acc = 0;
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
		base = handle_base(strtoll);
	if (base < 2 || base > 36)
		return (errno = EINVAL, free(strtoll), 0);
	if (strtoll->neg)
		strtoll->cutoff = -(unsigned long long)LLONG_MIN;
	else
		strtoll->cutoff = LLONG_MAX;
	initialize_conversion(strtoll, &acc, base);
	convert_digits(strtoll, &acc, base);
	acc = handle_result(strtoll, acc);
	handle_endptr(strtoll, endptr);
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
