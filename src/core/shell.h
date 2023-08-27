/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:55:30 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 17:05:00 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct g_shell			t_shell;
typedef struct s_node			t_node;
typedef struct s_heredoc_data	t_heredoc_data;
typedef struct s_token			t_token;
typedef struct s_curr_tok		t_curr_tok;
typedef struct s_cli			t_cli;

void							prompt_display_ps1(void);
void							prompt_display_ps2(void);
int								parse_and_execute(t_shell *g_shell, t_cli *cli);
// void	print_ast(t_node *node, int indent);

#endif
