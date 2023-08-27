/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:43 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 16:58:31 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Lexical analysis
 * The data and function here will read input
 * to make it easier to convert them into tokens
 */

#ifndef LEXER_H
# define LEXER_H

# define EOF (-1)
# define ERRCHAR (0)

# define INIT_SRC_POS (-2)

typedef struct g_shell		t_shell;
typedef struct s_node		t_node;
typedef struct s_token		t_token;
typedef struct s_curr_tok	t_curr_tok;
typedef struct s_parsing	t_parsing;
/**
 * @brief This struct represents our command line
 * @param buffer: the command line
 * @param buff_size: the size of the command line
 * @param cur_pos: the current position in the command line
 */
typedef struct s_cli
{
	char					*buffer;
	long int				buff_size;
	long int				cur_pos;
}							t_cli;

char						get_next_char(t_cli *cli);

char						peek_char(t_cli *cli);

void						unget_char(t_cli *cli);

/**
 * @brief Skip whitespaces in the input buffer
 * @param cli The Command Line
 */
void						skip_whitespaces(t_cli *cli);

#endif
