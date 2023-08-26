/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/08/26 15:56:15 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/26 15:56:15 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>  // for open
#include <unistd.h> // for read, close


// char	*my_strdup(void *memory, const char *str)
// {
// 	size_t len;
// 	char *out;

// 	len = ft_strlen((char *)str) + 1;
// 	out = my_malloc(memory, len);
// 	if (!out)
// 		return (NULL);
// 	ft_memcpy(out, str, len);
// 	return (out);
// }

// char	*find_home_from_etc_passwd(t_shell *g_shell, char *s)
// {
// 	int fd;
// 	char buf[1024];
// 	ssize_t bytes_read;
// 	char *username;
// 	char *home = NULL;
// 	char *line;
// 	char *tmp_buf;

// 	username = ft_substr(s, 1, ft_strlen(s) - 1);
// 	fd = open("/etc/passwd", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		free(username);
// 		return (NULL);
// 	}
// 	while ((bytes_read = read(fd, buf, sizeof(buf) - 1)) > 0)
// 	{
// 		buf[bytes_read] = '\0';
// 		tmp_buf = buf;
// 		line = ft_strtok(tmp_buf, "\n");
// 		while (line)
// 		{
// 			if (ft_strncmp(username, line, ft_strlen(username)) == 0
// 				&& line[ft_strlen(username)] == ':')
// 			{
// 				home = ft_strtok(line, ":");
// 				for (int i = 0; i < 5; ++i)
// 					home = ft_strtok(NULL, ":");
// 				if (home)
// 					home = my_strdup(&g_shell->memory, home);
// 				close(fd);
// 				free(username);
// 				return (home);
// 			}
// 			line = ft_strtok(NULL, "\n");
// 		}
// 	}
// 	close(fd);
// 	free(username);
// 	return (NULL);
// }

// char	*get_home_from_cmd(t_shell *g_shell, const char *cmd)
// {
// 	int fd;
// 	char *cmd_copy;
// 	char b[1024];
// 	size_t bufsz = 0;
// 	char *buf = NULL;
// 	char *p;

// 	cmd_copy = my_malloc(&g_shell->memory, ft_strlen(cmd) + 1);
// 	if (!cmd_copy)
// 		return (NULL);
// 	ft_strcpy(cmd_copy, cmd);
// 	fd = pipe_command(cmd_copy);
// 	if (fd == -1)
// 	{
// 		perror("failed to open pipe");
// 		return (NULL);
// 	}
// 	buf = read_from_pipe(g_shell, fd, b, &bufsz, &p);
// 	close(fd);
// 	if (buf)
// 		remove_trailing_newlines(buf, bufsz);
// 	free(cmd_copy);
// 	return (buf);
// }

// char	*find_home_from_pwnam(t_shell *g_shell, char *s)
// {
// 	char *home = NULL;

// 	home = find_home_from_etc_passwd(g_shell, s);
// 	if (home)
// 		return (home);
// 	char *temp1 = ft_strdup("eval echo ~");
// 	char *temp2 = ft_substr(s, 1, ft_strlen(s) - 1);
// 	char *cmd = ft_strjoin(temp1, temp2);
// 	free(temp1);
// 	free(temp2);
// 	home = get_home_from_cmd(g_shell, cmd);
// 	free(cmd);
// 	return (home);
// }

// char	*find_home_from_symtab(t_shell *g_shell)
// {
// 	struct s_symtab_entry *entry;
// 	char *home;

// 	home = NULL;
// 	entry = get_symtab_entry(g_shell, "HOME");
// 	if (entry && entry->val)
// 		home = entry->val;
// 	else
// 		home = get_home_from_cmd(g_shell, "echo $HOME");
// 	return (home);
// }

// char	*tilde_expansion(t_shell *g_shell, char *s)
// {
// 	char *home;
// 	char *s2;
// 	size_t len;

// 	home = NULL;
// 	len = ft_strlen(s);
// 	s2 = NULL;
// 	if (len == 1)
// 		home = find_home_from_symtab(g_shell);
// 	else
// 		home = find_home_from_pwnam(g_shell, s);
// 	if (!home)
// 	{
// 		home = my_strdup(&g_shell->memory, s);
// 		return (home);
// 	}
// 	s2 = my_malloc(&g_shell->memory, ft_strlen(home) + 1);
// 	if (!s2)
// 		return (NULL);
// 	ft_strcpy(s2, home);
// 	return (s2);
// }

char	*find_home_from_symtab(t_shell *g_shell)
{
	struct s_symtab_entry	*entry;
	// struct passwd			*pass;
	char					*home;

	home = NULL;
	entry = get_symtab_entry(g_shell, "HOME");
	if (entry && entry->val)
		home = entry->val;
	else
		return (NULL);
	// {
	// 	pass = getpwuid(getuid());
	// 	if (pass)
	// 		home = pass->pw_dir;
	// }
	return (home);
}

// char	*find_home_from_pwnam(char *s)
// {
// 	struct passwd	*pass;
// 	char			*home;

// 	home = NULL;
// 	pass = getpwnam(s + 1);
// 	if (pass)
// 		home = pass->pw_dir;
// 	return (home);
// }

char	*tilde_expansion(t_shell *g_shell, char *s)
{
	char	*home;
	char	*s2;
	size_t	len;

	home = NULL;
	len = ft_strlen(s);
	s2 = NULL;
	if (len == 1)
		home = find_home_from_symtab(g_shell);
	// else
	// 	home = find_home_from_pwnam(s);
	if (!home)
		return (NULL);
	s2 = my_malloc(&g_shell->memory, ft_strlen(home) + 1);
	if (!s2)
		return (NULL);
	ft_strcpy(s2, home);
	return (s2);
}
