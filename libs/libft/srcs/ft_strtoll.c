/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/21 20:28:56 by lhasmi           ###   ########.fr       */
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

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	const char			*s;
	unsigned long long	acc;
	char				c;
	unsigned long long	cutoff;
	int					neg;
	int					any;
	int					cutlim;

	s = nptr;
	neg = 0, any = 0, cutlim = 0;
	acc = 0;
	// Skip white space
	do
	{
		c = *s++;
	} while (ft_iswspace((unsigned char)c));
	// Handle sign
	if (c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else if (c == '+')
		c = *s++;
	// Handle hex
	if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')
		&& isxdigit(s[1]))
	{
		c = s[1];
		s += 2;
		base = 16;
	}
	// Determine base
	if (base == 0){
		base = c == '0' ? 8 : 10;
	}
	if (base < 2 || base > 36){
		errno = EINVAL;
		goto noconv;
	}
	// Initialize variables for conversion
	cutoff = neg ? -(unsigned long long)LLONG_MIN : LLONG_MAX;
	cutlim = cutoff % base;
	cutoff /= base;
	acc = 0;
	// Convert digits
	for (;; c = *s++)
	{
		if (isdigit(c))
			c -= '0';
		else if (isupper(c))
			c -= 'A' - 10;
		else if (islower(c))
			c -= 'a' - 10;
		else
			break ;
		if (c >= base)
			break ;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	// Handle result
	if (any < 0)
	{
		acc = neg ? LLONG_MIN : LLONG_MAX;
		errno = ERANGE;
	}
	else if (neg)
		acc = -acc;
	else if (!any)
	{
	noconv:
		s = nptr;
	}
	// Assign end pointer if required
	if (endptr != NULL)
		*endptr = (char *)(any ? s - 1 : s);
	return (acc);
}

// static unsigned char	charmap(char c)
// {
// 	char	chr;

// 	chr = ft_toupper(c);
// 	if (chr >= '0' && chr <= '9')
// 		return (chr - '0');
// 	if (chr >= 'A' && chr <= 'Z')
// 		return (chr - 'A' + 10);
// 	return (36);
// }

// static int	getbase(const char **nptr, int base)
// {
// 	const char	*ptr;

// 	ptr = *nptr;
// 	if (base == 0)
// 	{
// 		if (*ptr == '0')
// 		{
// 			++ptr;
// 			if (*ptr == 'x' || *ptr == 'X')
// 			{
// 				base = 16;
// 				++ptr;
// 			}
// 			else
// 				base = 8;
// 		}
// 		else
// 			base = 10;
// 	}
// 	*nptr = ptr;
// 	return (base);
// }

// long long	ft_strtoll(const char *nptr, char **endptr, int base)
// {
// 	int				neg;
// 	long long		result;
// 	long long		prev_result;
// 	unsigned char	digit;
// 	const char		*start;

// 	start = nptr;
// 	// to ensure endptr remains unchanged if no conversion is done
// 	if (base < 0 || base == 1 || base > 36)
// 	{
// 		errno = EINVAL;
// 		if (endptr)
// 			*endptr = (char *)nptr;
// 		return (0); // Base out of valid range
// 	}
// 	neg = 1;
// 	result = 0;
// 	prev_result = 0;
// 	while (ft_iswspace(*nptr))
// 		nptr++;
// 	if (*nptr == '-')
// 	{
// 		neg = -1;
// 		nptr++;
// 	}
// 	else if (*nptr == '+')
// 		nptr++;
// 	base = getbase(&nptr, base);
// 	while ((digit = charmap(*nptr)) < base)
// 	{
// 		prev_result = result;
// 		result = result * base + digit;
// 		if (result < prev_result)
// 		{
// 			errno = ERANGE;
// 			if (endptr)
// 				*endptr = (char *)(nptr + 1);
// 			// point to character after last valid char
// 			return (neg == -1 ? FT_LONG_MIN : FT_LONG_MAX);
// 		}
// 		nptr++;
// 	}
// 	if (endptr)
// 	{
// 		if (nptr == start) // No conversion done, endptr remains unchanged
// 			*endptr = (char *)nptr;
// 		else // Point to the character after the last valid character processed
// 			*endptr = (char *)(nptr - 1);
// 	}
// 	return (result * neg);
// }
