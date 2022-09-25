/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/25 02:49:59 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell(t_status *status)
{
	if (status->in_fd != STDIN_FILENO)
		dup2(status->in_fd, STDIN_FILENO);
	else if (status->in_pipe)
		dup2(status->in_pipe[0], STDIN_FILENO);
	if (status->out_fd != STDOUT_FILENO)
		dup2(status->out_fd, STDOUT_FILENO);
	else if (status->out_pipe)
		dup2(status->out_pipe[1], STDOUT_FILENO);
	execve(status->command->u_command_ref.command_path,
		status->args, status->environ);
}

void	summon_child(t_status *status)
{
	status->child_id = fork();
	if (!status->child_id)
		subshell(status);
	if (status->ft_isatty)
		waiting_handlers(status);
	waitpid(status->child_id, &status->child_exit_status, 0);
	install_handlers(status);
	set_exit_status(status);
}

void	execute(t_status *status)
{
	status->child_id = fork();
	if (!status->child_id)
	{
		if (status->out_pipe)
			close_pipe_end(status->out_pipe, PIPE_OUT);
		if (status->in_fd != STDIN_FILENO)
			dup2(status->in_fd, STDIN_FILENO);
		else if (status->in_pipe)
			dup2(status->in_pipe[0], STDIN_FILENO);
		if (status->out_fd != STDOUT_FILENO)
			dup2(status->out_fd, STDOUT_FILENO);
		else if (status->out_pipe)
			dup2(status->out_pipe[1], STDOUT_FILENO);
		if (status->ft_isatty)
			waiting_handlers(status);
		if (status->command->command_type == CMD_BUILTIN)
			execute_builtin(status);
		else if (status->command->command_type == CMD_ABS_PATH)
			execve(status->command->u_command_ref.command_path,
		status->args, status->environ);
	}
}

void	reap_child(t_status *status)
{
	if (wait(&status->child_exit_status) == status->child_id)
		set_exit_status(status);
}

void	execute_commands(t_status *status)
{
	int	n_children;

	n_children = 0;
	status->curr_command = status->commands;
	while (status->curr_command && !g_stop_non_int)
	{
		if (!parse_curr_command(status) && !preprocess_redirections(status))
		{
			if (!status->command
				|| (status->command->command_type != CMD_BUILTIN
					&& status->command->command_type != CMD_ABS_PATH))
			{
				status->tmp_exit = ft_cmd_not_found(status->args[0]);
			}
			else
			{
				++n_children;
				execute(status);
			}
		}
		flush_error_msg(status, NULL);
		postprocess_redirections(status);
		status->curr_command = status->curr_command->next;
		free_parsed_command(status);
	}
	while (n_children--)
		reap_child(status);
	if (g_stop_non_int)
		free_and_exit(status);
}

void	execute_pipeline(t_status *status)
{
	if (!is_valid_quoting(status->curr_pipeline))
	{
		flush_error_msg(status, "quoting error\n");
		status->exit_status = 1;
		return ;
	}
	status->commands = ft_split_unquoted_c(status->curr_pipeline, '|');
	if (!is_valid_pipeline(status->commands))
	{
		free_str_list(status->commands);
		status->commands = NULL;
		flush_error_msg(status, "pipeline error\n");
		status->exit_status = ERR_PIPELINE;
		return ;
	}
	execute_commands(status);
	free_str_list(status->commands);
	status->commands = NULL;
	return ;
}

void	run_shell(t_status *status)
{
	t_str_list	*tmp;

	while (TRUE)
	{
		read_input(status);
		tmp = status->pipelines;
		while (tmp)
		{
			status->curr_pipeline = ft_strdup(tmp->str);
			if (!status->curr_pipeline)
				malloc_error(status);
			else if (*status->curr_pipeline)
			{
				decide_add_history(status);
				execute_pipeline(status);
				save_prev_pipeline(status);
			}
			free_curr_pipeline(status);
			tmp = tmp->next;
		}
		free_pipelines(status);
	}
}
