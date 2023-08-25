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

int	prepare_command_and_open_pipe(char *orig_cmd, char **cmd_ptr)
{
	char	*cmd;
	int		cmdlen;
	int		fd;

	fd = -1;
	cmd = orig_cmd;
	cmdlen = ft_strlen(cmd);
	fd = pipe_command(cmd);
	*cmd_ptr = cmd;
	return (fd);
}

char	*read_from_fd(int fd, char *b, char **buf, size_t *bufsz)
{
	ssize_t	bytes_read;
	char	*p;

	*buf = NULL;
	*bufsz = 0;
	bytes_read = read_from_pipe(fd, b, sizeof(b));
	while (bytes_read > 0)
	{
		if (!*buf)
		{
			*buf = malloc(bytes_read + 1);
			if (!*buf)
				return (*buf);
			p = *buf;
		}
		else
		{
			*buf = ft_realloc(*buf, *bufsz + bytes_read);
			p = *buf + *bufsz;
		}
		ft_memcpy(p, b, bytes_read);
		*bufsz += bytes_read;
		bytes_read = read_from_pipe(fd, b, sizeof(b));
	}
	return (*buf);
}

char	*cleanup_and_return(int fd, char *cmd, char *buf)
{
	close(fd);
	free(cmd);
	if (!buf)
		fprintf(stderr, "error: %s: %s\n",
			"insufficient memory to perform command substitution",
			strerror(errno));
	return (buf);
}

char	*read_and_cleanup_pipe(int fd, char *cmd)
{
	char	b[1024];
	size_t	bufsz;
	char	*buf;

	if (fd == -1)
	{
		fprintf(stderr, "error: %s: %s\n", "failed to open pipe",
			strerror(errno));
		return (NULL);
	}
	buf = read_from_fd(fd, b, &buf, &bufsz);
	return (cleanup_and_return(fd, cmd, buf));
}

char	*command_substitute(char *orig_cmd)
{
	char	*cmd;
	int		fp;

	cmd = NULL;
	fp = prepare_command_and_open_pipe(orig_cmd, &cmd);
	return (read_and_cleanup_pipe(fp, cmd));
}

// char	*read_and_cleanup_pipe(int fd, char *cmd)
// {
// 	char	b[1024];
// 	size_t	bufsz;
// 	ssize_t	bytes_read;
// 	char	*buf;
// 	char	*p;

// 	buf = NULL;
// 	bufsz = 0;
// 	if (fd == -1)
// 	{
// 		fprintf(stderr, "error: %s: %s\n", "failed to open pipe",
// 			strerror(errno));
// 		return (NULL);
// 	}
// 	bytes_read = read_from_pipe(fd, b, sizeof(b));
// 	while (bytes_read > 0)
// 	{
// 		if (!buf)
// 		{
// 			buf = malloc(bytes_read + 1);
// 			if (!buf)
// 				return (buf);
// 			p = buf;
// 		}
// 		else
// 		{
// 			buf = ft_realloc(buf, bufsz + bytes_read);
// 			p = buf + bufsz;
// 		}
// 		ft_memcpy(p, b, bytes_read);
// 		bufsz += bytes_read;
// 		bytes_read = read_from_pipe(fd, b, sizeof(b));
// 	}
// 	close(fd);
// 	free(cmd);
// 	if (!buf)
// 		fprintf(stderr, "error: %s: %s\n",
// 			"insufficient memory to perform command substitution",
// 			strerror(errno));
// 	return (buf);
// }
// int	pipe_command(char *cmd)
// {
// 	int		fd[2];
// 	int		ret;
// 	pid_t	pid;

// 	ret = pipe(fd);
// 	if (ret == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		close(fd[0]);
// 		close(fd[1]);
// 		return (-1);
// 	}
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		execl("/bin/sh", "sh", "-c", cmd, NULL);
// 		_exit(127);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		return (fd[0]);
// 	}
// }
