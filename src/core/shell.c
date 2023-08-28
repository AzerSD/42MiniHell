/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 02:03:59 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(void)
{
	char	*cmd;

	if (isatty(STDIN_FILENO))
		cmd = readline(MAG "minishell> " RESET);
	else
	{
		cmd = get_next_line(STDIN_FILENO);
		cmd = ft_strtrim(cmd, "\n");
	}
	return (cmd);
}

void	main_loop_sub(t_shell *g_shell)
{
	char	*cmd;
	t_cli	cli;

	cmd = get_cmd();
	if (!cmd)
	{
		free_all_mem(&g_shell->memory);
		exit(g_shell->status);
	}
	if (isatty(STDIN_FILENO))
		add_history(cmd);
	cli.buffer = cmd;
	cli.buff_size = ft_strlen(cmd);
	cli.cur_pos = INIT_SRC_POS;
	g_shell->status = parse_and_execute(g_shell, &cli);
}

void	main_loop(t_shell *g_shell)
{
	int		original_stdout;
	int		original_stdin;
	int		original_stderr;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	original_stderr = dup(STDERR_FILENO);
	while (true)
	{
		main_loop_sub(g_shell);
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stderr, STDERR_FILENO);
		unlink("/tmp/heredoc");
	}
}

int	main(int argc, char **argv, char **env)
{
	struct termios	mirror_termios;
	t_shell			*g_shell;

	g_shell = malloc(sizeof(t_shell));
	g_shell->memory = NULL;
	g_shell->status = 0;
	(void)argc;
	(void)argv;
	init_symtab(g_shell, env);
	signals(&mirror_termios);
	main_loop(g_shell);
	rl_clear_history();
	free_all_mem(&g_shell->memory);
	return (g_shell->status);
}

int	parse_and_execute(t_shell *g_shell, t_cli *cli)
{
	t_node		*ast_cmd;
	t_token		*tok;
	t_curr_tok	*curr;

	curr = my_malloc(&(g_shell->memory), sizeof(t_curr_tok));
	skip_whitespaces(cli);
	tok = get_token(g_shell, cli, curr);
	if (curr->tok_buff_index == -1)
		return (0);
	ast_cmd = parse_cmd(g_shell, tok, curr);
	if (!ast_cmd)
	{
		ft_printf_fd(STDERR_FILENO, "error: syntax error near unexpected \
			token\n");
		return (2);
	}
	return (execc(g_shell, ast_cmd));
}

// void	main_loop(t_shell *g_shell)
// {
// 	t_cli	cli;
// 	char	*cmd;
// 	int		original_stdout;
// 	int		original_stdin;
// 	int		original_stderr;

// 	original_stdout = dup(STDOUT_FILENO);
// 	original_stdin = dup(STDIN_FILENO);
// 	original_stderr = dup(STDERR_FILENO);
// 	while (true)
// 	{
// 		cmd = get_cmd();
// 		if (!cmd)
// 		{
// 			free_all_mem(&g_shell->memory);
// 			exit(g_shell->status);
// 		}
// 		if (isatty(STDIN_FILENO))
// 			add_history(cmd);
// 		cli.buffer = cmd;
// 		cli.buff_size = ft_strlen(cmd);
// 		cli.cur_pos = INIT_SRC_POS;
// 		g_shell->status = parse_and_execute(g_shell, &cli);
// 		dup2(original_stdout, STDOUT_FILENO);
// 		dup2(original_stdin, STDIN_FILENO);
// 		dup2(original_stderr, STDERR_FILENO);
// 		unlink("/tmp/heredoc");
// 	}
// }
