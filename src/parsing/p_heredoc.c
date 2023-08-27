/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:12:36 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 04:19:10 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_redirection_node(t_shell *g_shell, t_token *tok, t_node *ptr)
{
	t_node	*redirection_node;

	redirection_node = new_node(g_shell, NODE_HEREDOC);
	set_node_val_str(g_shell, redirection_node, tok->text);
	if (!redirection_node)
	{
		free_node_tree(ptr);
		free_token(g_shell, tok);
		return (NULL);
	}
	free_token(g_shell, tok);
	return (redirection_node);
}

t_token	*check_token(t_shell *g_shell, t_cli *cli, t_curr_tok *curr,
		t_node *ptr)
{
	t_token	*tok;

	tok = get_token(g_shell, cli, curr);
	if (tok == EOF_TOKEN)
	{
		free_node_tree(ptr);
		return (NULL);
	}
	return (tok);
}

int	create_temp_file(t_shell *g_shell, t_token *tok, t_node *ptr,
		char **tmp_file)
{
	int	tmp_fd;

	*tmp_file = "/tmp/heredoc";
	tmp_fd = open(*tmp_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_fd == -1)
	{
		free_node_tree(ptr);
		free_token(g_shell, tok);
		return (-1);
	}
	return (tmp_fd);
}

t_heredoc_data	*prepare_heredoc(t_parsing *prs, t_cli *cli, t_curr_tok *curr, \
		t_node *ptr)
{
	t_heredoc_data	*data;

	data = my_malloc(&(prs->g_shell)->memory, sizeof(t_heredoc_data));
	if (!data)
		return (NULL);
	data->redirection_node = new_redirection_node(prs->g_shell, prs->tok, ptr);
	if (!data->redirection_node)
		return (NULL);
	data->tok = check_token(prs->g_shell, cli, curr, ptr);
	if (!data->tok)
		return (NULL);
	data->tmp_fd = create_temp_file(prs->g_shell, data->tok, ptr, \
			&(data->tmp_file));
	if (data->tmp_fd == -1)
	{
		free_node_tree(ptr);
		free_token(prs->g_shell, data->tok);
		my_free(&(prs->g_shell)->memory, data->tmp_file);
		return (NULL);
	}
	return (data);
}

t_node	*execute_heredoc(t_parsing *prs, t_heredoc_data *data, t_node *ptr)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_node	*file_node;

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child_process(data->tmp_fd, pipe_fd);
	else
		handle_parent_process(prs, pipe_fd, data->tmp_fd);
	file_node = new_node(prs->g_shell, NODE_FILE);
	set_node_val_str(prs->g_shell, file_node, data->tmp_file);
	if (!file_node)
		return (free_node_tree(ptr), free_node_tree(ptr), NULL);
	add_child_node(data->redirection_node, file_node);
	return (add_child_node(ptr, data->redirection_node), ptr);
}
