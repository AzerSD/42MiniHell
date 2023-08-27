/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:21 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 19:45:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct g_shell		t_shell;
typedef struct s_cli		t_cli;
typedef struct s_node		t_node;
typedef struct s_token		t_token;
typedef struct s_curr_tok	t_curr_tok;

typedef struct s_parser
{
	t_token					*tok;
	t_cli					*cli;
	t_curr_tok				*curr;
	int						first_pipe;
}							t_parser;

typedef struct s_heredoc_data
{
	t_node					*redirection_node;
	t_token					*tok;
	int						tmp_fd;
	char					*tmp_file;
}							t_heredoc_data;

t_node						*execute_heredoc(t_shell *g_shell,
								t_heredoc_data *data, t_node *ptr);
t_node						*parse_cmd(t_shell *g_shell, struct s_token *tok,
								t_curr_tok *curr);
t_node						*parse_pipeline(t_token *tok, t_curr_tok *curr);
void						handle_child_process(int tmp_fd, int *pipe_fd);
void						handle_parent_process(t_shell *g_shell,
								int *pipe_fd, t_token *tok, int tmp_fd);
void						write_to_pipe_and_cleanup(t_shell *g_shell, int **n,
								t_token *tok,
								char *content);
char						*prepare_for_pipe(t_shell *g_shell, \
								int *pipe_fd, t_token *tok, int expanding);
t_heredoc_data				*prepare_heredoc(t_shell *g_shell, t_parser *prs,
								t_node *ptr);
int							create_temp_file(t_shell *g_shell, t_token *tok,
								t_node *ptr, char **tmp_file);

#endif
