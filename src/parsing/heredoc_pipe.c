/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:44:12 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 05:17:54 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_for_pipe(t_parsing *prs, int *pipe_fd, \
		int expanding, char *line)
{
	struct s_word	*w;

	(void)line;
	w = NULL;
	close(pipe_fd[0]);
	if (getncount(prs->tok->text, '\'') >= 2 || \
		getncount(prs->tok->text, '\"') >= 2)
	{
		w = make_word(prs->g_shell, prs->tok->text);
		expanding = 0;
		remove_quotes(w);
		prs->tok->text = w->data;
		my_free(&(prs->g_shell->memory), w);
		w = NULL;
	}
	return ("");
}

void	write_to_pipe_and_cleanup(t_parsing *prs, int *pipe_fd, \
		int tmp_fd, char *content)
{
	struct s_word	*w;
	char			*line;

	w = NULL;
	while (content && (ft_strncmp(content, prs->tok->text, ft_strlen(content)
				- 1) != 0 || content[0] == '\n'))
	{
		write(pipe_fd[1], content, ft_strlen(content));
		line = get_next_line(STDIN_FILENO);
		if (ft_strchr(line, '$') && ft_strncmp(line, prs->tok->text,
				ft_strlen(content) - 1) != 0)
			w = expand(prs->g_shell, line);
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

void	handle_parent_process(t_parsing *prs, int *pipe_fd, \
		int tmp_fd)
{
	int		expanding;
	char	*line;
	char	*content;

	expanding = 0;
	line = NULL;
	content = prepare_for_pipe(prs, pipe_fd, expanding, line);
	(void)tmp_fd;
	write_to_pipe_and_cleanup(prs, pipe_fd, tmp_fd, content);
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

t_node	*p_heredoc(t_parsing *prs, t_cli *cli, t_curr_tok *curr,
		t_node *ptr)
{
	t_heredoc_data	*data;

	data = prepare_heredoc(prs, cli, curr, ptr);
	if (!data)
		return (NULL);
	ptr = execute_heredoc(prs, data, ptr);
	my_free(&(prs->g_shell->memory), data);
	return (ptr);
}
