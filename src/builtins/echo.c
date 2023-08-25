/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:25 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/25 15:25:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_echo_options(char **argv, int *i)
{
	char	*arg;
	int		n_option;

	n_option = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		arg = argv[*i] + 1;
		while (*arg == 'n')
			arg++;
		if (*arg == '\0')
		{
			n_option = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (n_option);
}

void	echo_argv(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

void	check_newline(int n_option)
{
	if (n_option == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ft_echo(int argc, ...)
{
	int		i;
	int		n_option;
	char	**argv;
	va_list	args;

	va_start(args, argc);
	argv = va_arg(args, char **);
	if (argc <= 0)
		return (-1);
	i = 1;
	n_option = 0;
	if (argc > 1)
	{
		n_option = parse_echo_options(argv, &i);
		echo_argv(argv, i);
	}
	check_newline(n_option);
	va_end(args);
	shell_instance.status = 0;
	return (0);
}
		// if (argv[i + 1] && argv[i][0] != '\0')
