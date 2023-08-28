/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:13:44 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 02:28:14 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(int argc, char **argv)
{
	if (!argc)
		return ;
	while (argc--)
		free(argv[argc]);
}

int	wait_for_child(pid_t child_pid)
{
	int	status;

	status = 0;
	waitpid(child_pid, &status, 0);
	return (status);
}

int	exec_cmd(t_shell *g_shell, int argc, char **argv)
{
	char	*path;

	(void)argc;
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, NULL);
	else
	{
		path = search_path(g_shell, argv[0]);
		if (!path)
			return (1);
		execve(path, argv, NULL);
	}
	return (0);
}
