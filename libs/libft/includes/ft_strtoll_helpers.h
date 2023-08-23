/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll_helpers.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:14:02 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/23 23:14:00 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOLL_HELPERS_H
# define FT_STRTOLL_HELPERS_H

# include "../includes/libft.h"

int			ft_iswspace(const char nptr);
int			ft_isxdigit(char c);
t_strtoll	*strtoll_init(void);
void		skip_whitespace(t_strtoll *strtoll);
void		handle_sign(t_strtoll *strtoll);
void		handle_hex(t_strtoll *strtoll, int *base);
void		convert_digits(t_strtoll *strtoll, unsigned long long *acc,
				int base);

#endif
