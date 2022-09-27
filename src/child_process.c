/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 04:19:00 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/27 14:52:13 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_file_descriptors(t_status *status)
{
	if (status->out_pipe)
		close_pipe_end(status->out_pipe, PIPE_OUT);
	if (status->in_fd != STDIN_FILENO)
	{
		dup2(status->in_fd, STDIN_FILENO);
		if (status->in_pipe)
			close(status->in_pipe[0]);
		status->in_pipe = NULL;
	}
	else if (status->in_pipe)
		dup2(status->in_pipe[0], STDIN_FILENO);
	if (status->out_fd != STDOUT_FILENO)
	{
		dup2(status->out_fd, STDOUT_FILENO);
		if (status->out_pipe)
			close(status->out_pipe[1]);
		status->out_pipe = NULL;
	}
	else if (status->out_pipe)
		dup2(status->out_pipe[1], STDOUT_FILENO);
}

char	execute(t_status *status)
{
	if (status->command->command_type == CMD_BUILTIN
		&& !status->in_pipe && !status->out_pipe)
	{
		process_output(status);
		status->exit_status = status->command->u_command_ref.fun_ptr(status);
		return (0);
	}
	status->child_id = fork();
	if (!status->child_id)
	{
		signal(SIGQUIT, SIG_DFL);
		dup_file_descriptors(status);
		if (status->ft_isatty)
			waiting_handlers(status);
		if (status->command->command_type == CMD_BUILTIN)
			execute_builtin(status);
		else if (status->command->command_type == CMD_ABS_PATH)
		{
			execve(status->command->u_command_ref.command_path,
				status->args, status->environ);
			ft_putfd("minishell: exec format error\n", STDERR_FILENO);
			close_pipes(status);
			free_parsed_command(status);
			free_status(status);
			exit(1);
		}
	}
	return (1);
}

void	reap_child(t_status *status)
{
	if (wait(&status->child_exit_status) == status->child_id)
		set_exit_status(status);
}
