/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:21 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 05:22:07 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parsing	t_parsing;
typedef struct s_token		t_token;


typedef struct s_heredoc_data
{
	t_node		*redirection_node;
	t_token		*tok;
	int			tmp_fd;
	char		*tmp_file;
}				t_heredoc_data;

t_node			*execute_heredoc(t_parsing *prs, t_heredoc_data *data, t_node *ptr);

t_node			*parse_cmd(t_parsing *prs, t_token *tok, t_curr_tok *curr);
void			handle_child_process(int tmp_fd, int *pipe_fd);
void			handle_parent_process(t_parsing *prs, int *pipe_fd, int tmp_fd);

void			write_to_pipe_and_cleanup(t_parsing *prs, int *pipe_fd,
					int tmp_fd, char *content);

char			*prepare_for_pipe(t_parsing *prs, int *pipe_fd, int expanding,
					char *line);

t_heredoc_data	*prepare_heredoc(t_parsing *prs, t_cli *cli, t_curr_tok *curr,
					t_node *ptr);
int				create_temp_file(t_shell *g_shell, t_token *tok, t_node *ptr,
					char **tmp_file);
t_node			*p_heredoc(t_parsing *prs, t_cli *cli, t_curr_tok *curr,
					t_node *ptr);
#endif
