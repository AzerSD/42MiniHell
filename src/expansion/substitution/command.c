/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/03/30 17:17:07 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:17:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_command(char *cmd)
{
	int fd[2];
	int ret;

	ret = pipe(fd);
	if (ret == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execl("/bin/sh", "sh", "-c", cmd, NULL);
		_exit(127);
	}
	else
	{
		close(fd[1]);
		return (fd[0]);
	}
}

ssize_t	read_from_pipe(int fd, char *buf, size_t count)
{
	return (read(fd, buf, count));
}

int	prepare_command_and_open_pipe(char *orig_cmd, char **cmd_ptr)
{
	char *cmd;
	int cmdlen;
	int fd;

	fd = -1;
	cmd = orig_cmd; // No need to "fix" the command here
	cmdlen = ft_strlen(cmd);
	fd = pipe_command(cmd);
	*cmd_ptr = cmd;
	return (fd);
}

char	*read_and_cleanup_pipe(int fd, char *cmd)
{
	char b[1024];
	size_t bufsz = 0;
	char *buf = NULL;
	char *p;

	buf = NULL;
	if (fd == -1)
	{
		fprintf(stderr, "error: %s: %s\n", "failed to open pipe",
			strerror(errno));
		return (NULL);
	}
	ssize_t bytes_read = read_from_pipe(fd, b, sizeof(b));
	while (bytes_read > 0)
	{
		if (!buf)
		{
			buf = malloc(bytes_read + 1);
			if (!buf)
				return (buf);
			p = buf;
		}
		else
		{
			buf = ft_realloc(buf, bufsz + bytes_read);
			p = buf + bufsz;
		}
		ft_memcpy(p, b, bytes_read);
		bufsz += bytes_read;
		bytes_read = read_from_pipe(fd, b, sizeof(b));
	}
	close(fd);
	free(cmd);
	if (!buf)
		fprintf(stderr, "error: %s: %s\n",
			"insufficient memory to perform command substitution",
			strerror(errno));
	return (buf);
}

char	*command_substitute(char *orig_cmd)
{
	char *cmd;
	int fp;

	cmd = NULL;
	fp = prepare_command_and_open_pipe(orig_cmd, &cmd);
	return (read_and_cleanup_pipe(fp, cmd));
}
