/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:35:23 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/25 13:04:14 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(int fd[2])
{
	int	ret;

	ret = pipe(fd);
	if (ret == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	execute_command_in_child(int fd[2], char *cmd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execl("/bin/sh", "sh", "-c", cmd, NULL);
	_exit(127);
}

int	pid_error(int fd[2])
{
	perror("fork");
	close(fd[0]);
	close(fd[1]);
	return (-1);
}

int	pipe_command(char *cmd)
{
	int		fd[2];
	int		ret;
	pid_t	pid;

	ret = create_pipe(fd);
	if (ret == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (pid_error(fd));
	if (pid == 0)
	{
		execute_command_in_child(fd, cmd);
		_exit(127);
	}
	else
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

ssize_t	read_from_pipe(int fd, char *buf, size_t count)
{
	return (read(fd, buf, count));
}
