/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:05:51 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 17:02:35 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTAB_H
# define SYMTAB_H

typedef struct g_shell			t_shell;
typedef struct s_cli			t_cli;
typedef struct s_node			t_node;
typedef struct s_token			t_token;
typedef struct s_curr_tok		t_curr_tok;
typedef struct s_heredoc_data	t_heredoc_data;

enum							e_symbol_type
{
	SYM_STR,
	SYM_FUNC,
};

struct							s_symtab_entry
{
	struct s_node				*func_body;
	enum e_symbol_type			val_type;
	struct s_symtab_entry		*next;
	unsigned int				flags;
	char						*name;
	char						*val;
};

struct							s_symtab
{
	int							level;
	struct s_symtab_entry		*first;
	struct s_symtab_entry		*last;
};

# define MAX_SYMTAB 256

struct							s_symtab_stack
{
	int							symtab_count;
	struct s_symtab				*symtab_list[MAX_SYMTAB];
	struct s_symtab				*global_symtab;
	struct s_symtab				*local_symtab;
};

void							update_entry(t_shell *g_shell,
									struct s_symtab_entry *entry, char *new_val,
									char *name);

int								rem_from_symtab(t_shell *g_shell,
									struct s_symtab_entry *entry,
									struct s_symtab *symtab);

struct s_symtab_entry			*do_lookup(const char *str,
									struct s_symtab *symtable);

struct s_symtab_entry			*add_to_symtab(t_shell *g_shell,
									const char *symbol);

struct s_symtab_entry			*get_symtab_entry(t_shell *g_shell,
									const char *str);

struct s_symtab					*symtab_stack_push(t_shell *g_shell);

struct s_symtab					*get_global_symtab(t_shell *g_shell);

struct s_symtab					*get_local_symtab(t_shell *g_shell);

struct s_symtab					*symtab_stack_pop(t_shell *g_shell);

struct s_symtab					*new_symtab(t_shell *g_shell);

void							symtab_entry_setval(t_shell *g_shell,
									struct s_symtab_entry *entry, char *val);

void							free_symtab(t_shell *g_shell,
									struct s_symtab *symtab);

void							export_symtab(t_shell *g_shell);

void							init_symtab_stack(t_shell *g_shell);

void							init_symtab(t_shell *g_shell, char **env);

void							string_to_symtab(t_shell *g_shell,
									const char *env_var);

char							*get_varname(t_shell *g_shell, const char *str);

int								remove_entry_from_symtab(struct \
									s_symtab_entry *entry, \
									struct s_symtab *symtab);

void							free_symtab_entry(t_shell *g_shell,
									struct s_symtab_entry *entry);

struct s_symtab_entry			*create_symtab_entry(t_shell *g_shell,
									const char *symbol);

void							add_entry_to_symtab(struct s_symtab *st,
									struct s_symtab_entry *entry);

int								remove_subsequent_entry(struct \
									s_symtab_entry *entry, \
									struct s_symtab *symtab);
#endif
