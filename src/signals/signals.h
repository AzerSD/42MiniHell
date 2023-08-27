/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 16:58:17 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct g_shell			t_shell;
typedef struct s_cli			t_cli;
typedef struct s_node			t_node;
typedef struct s_token			t_token;
typedef struct s_curr_tok		t_curr_tok;
typedef struct s_parsing		t_parsing;
typedef struct s_heredoc_data	t_heredoc_data;

void							signals(struct termios *mirror_termios);
void							rem_c(struct termios *mirror_termios);
void							signal_ctrl_c(void);
void							signal_ctrl_backslash(void);
void							signal_ctrl_d(void);

#endif
