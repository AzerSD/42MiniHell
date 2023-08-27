/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:44:12 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 19:53:21 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_for_pipe(t_shell *g_shell, int *pipe_fd, t_token *tok,
		int expanding)
{
	struct s_word	*w;

	w = NULL;
	close(pipe_fd[0]);
	if (getncount(tok->text, '\'') >= 2 || getncount(tok->text, '\"') >= 2)
	{
		w = make_word(g_shell, tok->text);
		expanding = 0;
		remove_quotes(w);
		tok->text = w->data;
		my_free(&g_shell->memory, w);
		w = NULL;
	}
	return ("");
}

void	write_to_pipe_and_cleanup(t_shell *g_shell, int **n, t_token *tok, \
		char *content)
{
	struct s_word	*w;
	char			*line;

	w = NULL;
	while (content && (ft_strncmp(content, tok->text, ft_strlen(content)
				- 1) != 0 || content[0] == '\n'))
	{
		write(n[0][1], content, ft_strlen(content));
		line = get_next_line(STDIN_FILENO);
		if (ft_strchr(line, '$') && ft_strncmp(line, tok->text,
				ft_strlen(content) - 1) != 0)
			w = expand(g_shell, line);
		if (w)
			content = w->data;
		else
			content = line;
		w = NULL;
	}
	close(n[0][1]);
	wait(NULL);
	close(n[1][0]);
}

void	handle_parent_process(t_shell *g_shell, int *pipe_fd, t_token *tok,
		int tmp_fd)
{
	int		expanding;
	char	*content;

	expanding = 0;
	content = prepare_for_pipe(g_shell, pipe_fd, tok, expanding);
	write_to_pipe_and_cleanup(g_shell, (int *[]){pipe_fd, &tmp_fd}, \
		tok, content);
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

t_node	*p_heredoc(t_shell *g_shell, t_parser *prs,
		t_node *ptr)
{
	t_heredoc_data	*data;

	data = prepare_heredoc(g_shell, prs, ptr);
	if (!data)
		return (NULL);
	ptr = execute_heredoc(g_shell, data, ptr);
	my_free(&g_shell->memory, data);
	return (ptr);
}
