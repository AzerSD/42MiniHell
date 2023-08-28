/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:52:16 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/27 02:52:16 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# define INVALID_VAR ((char *)-1)

typedef struct g_shell		t_shell;
typedef struct s_node		t_node;
typedef struct s_token		t_token;

struct						s_word
{
	char					*data;
	int						len;
	struct s_word			*next;
};

typedef struct s_marker
{
	char					*pstart;
	char					*p;
	int						in_dquotes;
	int						in_squotes;
	int						escaped;
}							t_m;

typedef struct s_match
{
	char					*smatch;
	char					*lmatch;
	char					*str;
}							t_match;

struct						s_var_expand
{
	struct s_symtab_entry	*entry;
	size_t					len;
	int						get_length;
	char					*sub;
	char					*var_name;
	char					*empty_val;
	char					*tmp;
	char					setme;
	char					*p;
	int						longest;
	char					*p2;
	int						expanded;
	char					buf[32];
	char					*result;
};

struct s_word				*expand(t_shell *g_shell, char *orig_word);

char						*word_expand_to_str(t_shell *g_shell, char *word);
char						*var_expand(t_shell *g_shell, char *orig_var_name);

struct s_word				*make_word(t_shell *g_shell, char *str);

void						free_all_words(t_shell *g_shell,
								struct s_word *first);

char						**get_filename_matches(char *pattern,
								glob_t *matches);

int							has_glob_chars(char *p, size_t len);

int							match_prefix(char *pattern, char *str, int longest);

int							match_suffix(char *pattern, char *str, int longest);

char						*command_substitute(t_shell *g_shell,
								char *orig_cmd);
void						remove_quotes(struct s_word *wordlist);
size_t						find_closing_quote(char *data);
size_t						find_closing_brace(char *data);

char						*tilde_expansion(t_shell *g_shell, char *s);

struct s_word				*pathnames_expand(t_shell *g_shell,
								struct s_word *words);

char						*wordlist_to_str(t_shell *g_shell,
								struct s_word *word);
void						delete_char_at(char *str, size_t index);

int							is_name(char *str);

char						*substitute_str(t_shell *g_shell, char *s1,
								char *s2, size_t *range);

int							substitute_word(t_shell *g_shell, char ***startp, \
								size_t *lenquot, \
								char *(func)(t_shell *, char *));
void						substitute_norm(t_shell *g_shell, char ***poop, \
								char *(func)(t_shell *, char *), size_t *len);

int							check_buffer_bounds(t_shell *g_shell, int *count,
								int *len, char ***buf);

char						*strchr_any(char *string, char *chars);

char						*quote_val(t_shell *g_shell, char *val,
								int add_quotes);
void						free_buffer(int len, char **buf);
char						*fix_cmd(t_shell *g_shell, char *orig_cmd,
								int backquoted);
void						fix_backquoted_cmd(char *cmd, size_t cmdlen);
void						remove_closing_brace(char *cmd, size_t cmdlen);
char						*extend_buffer(char *buf, size_t bufsz, int i);
void						remove_trailing_newlines(char *buf, size_t bufsz);
void						handle_quote_chars(char **p, int *in_double_quotes);
void						handle_other_chars(char **p, int *in_double_quotes);
void						handle_char(char **p, int *in_double_quotes);
void						remove_quotes(struct s_word *wordlist);
size_t						find_closing_quote(char *data);
void						process_word(struct s_word *word,
								int *in_double_quotes);
void						check_single_quotes(char **p, int *in_double_quotes,
								int *in_single_quotes);
void						check_double_quotes(char **p, int *in_double_quotes,
								int in_single_quotes);
void						check_backslash(char **p, int *escaped);
void						check_dollar_sign(t_shell *g_shell, char **pstart, \
								char **p);

void						init_match(t_match *match);
int							is_match_found(char *pattern, int longest,
								t_match *m);
void						check_pattern(char *pattern, int longest,
								t_match *m, char **s);

char						*exit_code_expansion(t_shell *g_shell,
								char *orig_var_name);
char						*setup_var(char *orig_var_name,
								struct s_var_expand *var);
void						check_result(t_shell *g_shell,
								struct s_var_expand *var);
void						init_svar_expand(struct s_var_expand *v);
char						*exit_code_to_str(unsigned char status);
void						search_colon(t_shell *g_shell, char *orig_var_name,
								struct s_var_expand *var);

int							prepare_command_and_open_pipe(t_shell *g_shell,
								char *orig_cmd, char **cmd_ptr);
char						*read_and_cleanup_pipe(t_shell *g_shell, int fd,
								char *cmd);
char						*command_substitute(t_shell *g_shell,
								char *orig_cmd);
char						*error_inv_var_sub(char *orig_var_name);
void						handle_get_length(struct s_var_expand *var);
bool						match(const char *pattern, const char *string);

bool						handle_asterisk_in_match(const char *pattern, \
								const char *string);
char						*create_final_string(char *before, char *s2, \
								char *after, char *final);
void						free_all_words(t_shell *g_shell, \
								struct s_word *first);

#endif
// char						*read_from_pipe(t_shell *g_shell, int fd, char *b,
// 								size_t *bufsz, char **p);
// void						check_dollar_sign(t_shell *g_shell, char **pstart,
// 								char **p, int in_single_quotes, int *escaped);
