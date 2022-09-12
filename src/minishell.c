/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:38:44 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/13 00:04:19 by yfoucade         ###   ########.fr       */
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
	exit(0);
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

void	execute_commands(t_status *status)
{
	status->curr_command = status->commands;
	while (status->curr_command && !g_stop_non_int)
	{
		if (parse_curr_command(status))
			return ;
		if (!preprocess_redirections(status))
		{
			if (status->command->command_type == CMD_BUILTIN)
				execute_builtin(status);
			else if (status->command->command_type == CMD_ABS_PATH)
				summon_child(status);
			else
			{
				ft_putfd("command not found\n", STDERR_FILENO);
				status->exit_status = 127;
			}
		}
		postprocess_redirections(status);
		status->curr_command = status->curr_command->next;
		free_parsed_command(status);
	}
	if (g_stop_non_int)
		free_and_exit(status);
}

void	execute_pipeline(t_status *status)
{
	if (!is_valid_quoting(status->curr_pipeline))
	{
		set_error_msg(status, "minishell: quoting error\n");
		status->return_value = ERR_QUOTE;
		status->exit_status = 1;
		return ;
	}
	status->commands = ft_split_unquoted_c(status->curr_pipeline, '|');
	if (!status->commands)
		malloc_error(status);
	else if (!is_valid_pipeline(status->commands))
	{
		set_error_msg(status, "minishell: pipeline error\n");
		status->return_value = ERR_PIPELINE;
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
				// flush in execute_commands()
				if (status->return_value)
					flush_error_msg(status, NULL);
				save_prev_pipeline(status);
			}
			free_curr_pipeline(status);
			tmp = tmp->next;
		}
		free_pipelines(status);
	}
}
