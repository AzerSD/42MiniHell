/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:37:16 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/26 14:37:16 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_command(char *cmd)
{
	int fd[2];
	int ret = pipe(fd);
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

char	*read_from_pipe(t_shell *g_shell, int fd, char *b, size_t *bufsz,
		char **p)
{
	ssize_t i;
	char *buf = NULL;

	i = read(fd, b, 1024);
	while (i > 0)
	{
		if (!buf)
		{
			buf = my_malloc(&g_shell->memory, i + 1);
			if (!buf)
				return (buf);
			*p = buf;
		}
		else
		{
			buf = extend_buffer(buf, *bufsz, i);
			*p = buf + *bufsz;
		}
		*bufsz += i;
		ft_memcpy(*p, b, i);
		(*p)[i] = '\0';
		i = read(fd, b, 1024);
	}
	return (buf);
}

int	prepare_command_and_open_pipe(t_shell *g_shell, char *orig_cmd,
		char **cmd_ptr)
{
	char *cmd;
	int fd;

	cmd = fix_cmd(g_shell, orig_cmd, *orig_cmd == '`');
	if (!cmd)
		return (-1);
	fd = pipe_command(cmd);
	*cmd_ptr = cmd;
	return (fd);
}

char	*read_and_cleanup_pipe(t_shell *g_shell, int fd, char *cmd)
{
	char b[1024];
	size_t bufsz = 0;
	char *buf = NULL;
	char *p;

	if (fd == -1)
	{
		perror("failed to open pipe");
		return (NULL);
	}
	buf = read_from_pipe(g_shell, fd, b, &bufsz, &p);
	if (!bufsz)
	{
		free(cmd);
		return (NULL);
	}
	remove_trailing_newlines(buf, bufsz);
	close(fd);
	free(cmd);
	if (!buf)
		fprintf(stderr, "error: %s: %s\n",
			"insufficient memory to perform command substitution",
			strerror(errno));
	return (buf);
}

char	*command_substitute(t_shell *g_shell, char *orig_cmd)
{
	char *cmd;
	int fd;

	cmd = NULL;
	fd = prepare_command_and_open_pipe(g_shell, orig_cmd, &cmd);
	return (read_and_cleanup_pipe(g_shell, fd, cmd));
}

// FILE	*pipe_command(char *cmd)
// {
// 	FILE	*fp;

// 	fp = popen(cmd, "r");
// 	return (fp);
// }

// char	*read_from_pipe(t_shell *g_shell, FILE *fp, char *b, size_t *bufsz,
		// char **p)
// {
// 	int		i;
// 	char	*buf;

// 	i = fread(b, 1, 1024, fp);
// 	while (i)
// 	{
// 		if (!buf)
// 		{
// 			buf = my_malloc(&g_shell->memory, i + 1);
// 			if (!buf)
// 				return (buf);
// 			*p = buf;
// 		}
// 		else
// 		{
// 			buf = extend_buffer(buf, *bufsz, i);
// 			*p = buf + *bufsz;
// 		}
// 		*bufsz += i;
// 		ft_memcpy(*p, b, i);
// 		(*p)[i] = '\0';
// 		i = fread(b, 1, 1024, fp);
// 	}
// 	return (buf);
// }

// FILE	*prepare_command_and_open_pipe(t_shell *g_shell, char *orig_cmd,
		// char **cmd_ptr)
// {
// 	char	*cmd;
// 	size_t	cmdlen;
// 	FILE	*fp;

// 	fp = NULL;
// 	cmd = fix_cmd(g_shell, orig_cmd, *orig_cmd == '`');
// 	if (!cmd)
// 		return (NULL);
// 	cmdlen = ft_strlen(cmd);
// 	if (*orig_cmd == '`')
// 		fix_backquoted_cmd(cmd, cmdlen);
// 	else
// 		remove_closing_brace(cmd, cmdlen);
// 	fp = pipe_command(cmd);
// 	*cmd_ptr = cmd;
// 	return (fp);
// }

// char	*read_and_cleanup_pipe(t_shell *g_shell, FILE *fp, char *cmd)
// {
// 	char	b[1024];
// 	size_t	bufsz;
// 	char	*buf;
// 	char	*p;

// 	buf = NULL;
// 	if (!fp)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "error: %s: %s\n", "failed to open pipe",
// 			strerror(errno));
// 		return (NULL);
// 	}
// 	buf = read_from_pipe(g_shell, fp, b, &bufsz, &p);
// 	if (!bufsz)
// 	{
// 		free(cmd);
// 		return (NULL);
// 	}
// 	remove_trailing_newlines(buf, bufsz);
// 	pclose(fp);
// 	free(cmd);
// 	if (!buf)
// 		ft_printf_fd(STDERR_FILENO, "error: %s: %s\n", \
// 		"insufficient memory to perform command substitution",
			// strerror(errno));
// 	return (buf);
// }

// char	*command_substitute(t_shell *g_shell, char *orig_cmd)
// {
// 	char	*cmd;
// 	FILE	*fp;

// 	cmd = NULL;
// 	fp = prepare_command_and_open_pipe(g_shell, orig_cmd, &cmd);
// 	return (read_and_cleanup_pipe(g_shell, fp, cmd));
// }
