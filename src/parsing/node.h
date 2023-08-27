/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:12 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 16:58:36 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct g_shell		t_shell;
typedef struct s_cli		t_cli;
typedef struct s_node		t_node;
typedef struct s_token		t_token;
typedef struct s_curr_tok	t_curr_tok;

enum						e_node_type
{
	NODE_COMMAND,
	NODE_VAR,
	NODE_ASSIGNMENT,
	NODE_PIPE,
	NODE_LIST,
	NODE_INPUT,
	NODE_OUTPUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_FILE,
};

enum						e_val_type
{
	VAL_SINT = 1,
	VAL_UINT,
	VAL_SLLONG,
	VAL_ULLONG,
	VAL_FLOAT,
	VAL_LDOUBLE,
	VAL_CHR,
	VAL_STR,
};

union						u_symval
{
	unsigned long long		ullong;
	unsigned long			uint;
	long long				sllong;
	long double				ldouble;
	double					sfloat;
	long					sint;
	char					chr;
	char					*str;
};

typedef struct s_node
{
	enum e_node_type		type;
	enum e_val_type			val_type;
	union u_symval			val;
	struct s_node			*first_child;
	struct s_node			*next_sibling;
	struct s_node			*prev_sibling;
	int						children;
	int						line_nbr;

}							t_node;

t_node						*new_node(t_shell *g_shell, enum e_node_type type);

void						add_child_node(t_node *parent, t_node *child);
void						add_parent_node(t_node *child, t_node *parent);

void						free_node_tree(t_shell *g_shell, t_node *node);

void						set_node_val_str(t_shell *g_shell, t_node *node,
								char *val);
void						print_ast(t_node *node, int indent);

#endif
