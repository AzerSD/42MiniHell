/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:47 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 22:39:51 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_shell *g_shell, int argc, char **argv)
{
	char	*path;

	(void)argc;
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, NULL);
	else
	{
		path = search_path(g_shell, argv[0]);
		if (!path)
			return (1);
		execve(path, argv, NULL);
	}
	return (0);
}

pid_t	fork_command(t_shell *g_shell, int argc, char **argv)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		exec_cmd(g_shell, argc, argv);
		ft_printf_fd(STDERR_FILENO, "minishell: %s: \
			No such file or directory\n", \
			argv[0]);
		if (errno == ENOEXEC)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(0);
	}
	return (child_pid);
}

int	exec_child_process(t_shell *g_shell, int argc, char **argv)
{
	int		status;
	pid_t	child_pid;

	status = 0;
	child_pid = fork_command(g_shell, argc, argv);
	if (child_pid == -1)
	{
		ft_printf_fd(STDERR_FILENO, "error: failed to fork command: %s\n", \
		strerror(errno));
		return (1);
	}
	waitpid(child_pid, &status, 0);
	status = WEXITSTATUS(status);
	g_shell->status = status;
	return (status);
}

void	init_vars(int *argc, int *targc, char ***argv, int *ret)
{
	*argc = 0;
	*targc = 0;
	*argv = NULL;
	*ret = 0;
}

int	execc(t_shell *g_shell, t_node *node)
{
	char	**argv;
	int		argc;
	int		targc;
	int		ret;
	int		pipeline_status;

	init_vars(&argc, &targc, &argv, &ret);
	if (!node)
		return (1);
	if (node->type == NODE_ASSIGNMENT)
		return (string_to_symtab(g_shell, node->first_child->val.str), 0);
	if (node->type == NODE_PIPE)
	{
		ret = dup(STDIN_FILENO);
		pipeline_status = execute_pipeline(g_shell, node);
		dup2(ret, STDIN_FILENO);
		close(ret);
		g_shell->status = pipeline_status;
		return (pipeline_status);
	}
	parse_ast(g_shell, node, (int *[]){&argc, &targc}, &argv);
	if (setup_redirections(g_shell, node))
		return (1);
	ret = exec_builtin(g_shell, argc, argv);
	if (ret >= 0)
		return (g_shell->status = ret, ret);
	if (!argv[0])
		return (1);
	return (exec_child_process(g_shell, argc, argv));
}
