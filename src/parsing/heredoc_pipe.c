/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:44:12 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 19:12:35 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_for_pipe(t_shell *g_shell, int *pipe_fd, t_token *tok, int expanding, char *line)
{
	struct s_word	*w;
	char			*content;

	w = NULL;
	close(pipe_fd[0]);
	if (getncount(tok->text, '\'') >= 2 || getncount(tok->text, '\"') >= 2)
	{
		w = make_word(g_shell, tok->text);
		expanding = 0;
		remove_quotes(w);
		tok->text = w->data;
		free(w);
		w = NULL;
	}
	line = get_next_line(fileno(stdin));
	{
		if (ft_strchr(line, '$') && expanding)
			w = expand(g_shell, line);
		if (w)
			content = w->data;
		else
			content = line;
	}
	return (content);
}

void	write_to_pipe_and_cleanup(t_shell *g_shell, int *pipe_fd, t_token *tok,
		int tmp_fd, char *content)
{
	struct s_word	*w;
	char			*line;

	w = NULL;
	while (content && (ft_strncmp(content, tok->text, ft_strlen(content)
				- 1) != 0))
	{
		write(pipe_fd[1], content, ft_strlen(content));
		line = get_next_line(fileno(stdin));
		if (ft_strchr(line, '$'))
			w = expand(g_shell, line);
		if (w)
			content = w->data;
		else
			content = line;
		w = NULL;
	}
	close(pipe_fd[1]);
	wait(NULL);
	close(tmp_fd);
}

void	handle_parent_process(t_shell *g_shell, int *pipe_fd, t_token *tok, int tmp_fd)
{
	int		expanding;
	char	*line;
	char	*content;

	expanding = 0;
	line = NULL;
	content = prepare_for_pipe(g_shell, pipe_fd, tok, expanding, line);
	write_to_pipe_and_cleanup(g_shell, pipe_fd, tok, tmp_fd, content);
}

void	handle_child_process(int tmp_fd, int *pipe_fd)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	close(pipe_fd[1]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
	while ((bytes_read) > 0)
	{
		buffer[bytes_read] = '\0';
		write(tmp_fd, buffer, bytes_read);
		bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
	}
	close(tmp_fd);
	exit(EXIT_SUCCESS);
}

t_node	*p_heredoc(t_shell *g_shell, t_token *tok, t_cli *cli, t_curr_tok *curr, t_node *ptr)
{
	t_heredoc_data	*data;

	data = prepare_heredoc(g_shell, tok, cli, curr, ptr);
	if (!data)
		return (NULL);
	ptr = execute_heredoc(g_shell, data, ptr);
	free(data);
	return (ptr);
}
