/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:59 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 02:28:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct g_shell			t_shell;
typedef struct s_cli			t_cli;
typedef struct s_node			t_node;
typedef struct s_token			t_token;
typedef struct s_heredoc_data	t_heredoc_data;

char							*search_path(t_shell *g_shell, char *file);

/**
 * @brief Frees the memory allocated for the given arguments.
 * @param argc The number of arguments.
 * @param argv null-terminated strings containing the arguments.
 */
void							free_argv(int argc, char **argv);

int								execute_pipeline(t_shell *g_shell,
									t_node *node);

/**
 * @brief Executes a command represented by a node tree.
 * @param node A pointer to a t_node struct representing the command node.
 * @return 0 on success, or 1 if an error occurs.
 *
 * This function parses the arguments from the node tree, checks for built-in
 * commands, and forks the current process to execute the command. It waits for
 * the child process to terminate and returns its status.
 */
int								execc(t_shell *g_shell, t_node *node);

/**
 * @brief Parses the command arguments from a node tree and stores them in an
 * 		array of strings.
 * @param node A pointer to a t_node struct representing the command node.
 * @param argc To store the number of arguments.
 * @param targc To Store the Total number of arguments.
 * @param argv A null-terminated strings that will store the arguments.
 * @return 0 on success, or a non-zero value if an error occurs.
 */
void							parse_ast(t_shell *g_shell, t_node *node, \
									int **args, char ***argv);

/**
 * @brief Executes a command with the given arguments.
 * @param argc The number of arguments, including the command itself.
 * @param argv The first element is the command and the rest are the arguments.
 * @return 0 on success, or 1 if an error occurs.
 */
int								exec_cmd(t_shell *g_shell, int argc,
									char **argv);

////////////////////////////////////////////////////////////////////
//                          Redirections                          //
////////////////////////////////////////////////////////////////////

/**
 * @brief Redirects the standard input and output of the current process.
 * @param node The AST node representing the command to be executed.
 * @return 0 on success, 1 on failure.
 */
int								setup_redirections(t_shell *g_shell,
									t_node *node);

#endif
