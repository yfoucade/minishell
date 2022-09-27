/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/27 13:19:45 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_status(t_status *status, char **env)
{
	status->input = NULL;
	status->ft_isatty = isatty(STDIN_FILENO);
	errno = 0;
	status->pipelines = NULL;
	status->commands = NULL;
	status->curr_command = NULL;
	status->tokens = NULL;
	status->lst_args = NULL;
	status->lst_redirections = NULL;
	status->args = NULL;
	status->redirections = NULL;
	status->environ = copy_environ(env);
	status->in_pipe = NULL;
	status->out_pipe = NULL;
	status->curr_pipeline = NULL;
	status->prev_pipeline = NULL;
	status->command = NULL;
	status->return_value = 0;
	status->error_msg = NULL;
	status->exit_status = 0;
	status->hide_empty = TRUE;
	status->in_fd = STDIN_FILENO;
	status->out_fd = STDOUT_FILENO;
	if (add_custom_variables(status))
		panic(status);
}

void	free_status(t_status *status)
{
	if (!status)
		return ;
	free(status->input);
	free_str_list(status->pipelines);
	free_str_list(status->commands);
	free_str_list(status->tokens);
	free_str_list(status->lst_args);
	free_str_list(status->lst_redirections);
	free_array(status->args);
	free_array(status->redirections);
	free_array(status->environ);
	free(status->in_pipe);
	free(status->out_pipe);
	free(status->curr_pipeline);
	free(status->prev_pipeline);
	free(status->command);
	free(status->error_msg);
}

void	free_parsed_command(t_status *status)
{
	free_str_list(status->tokens);
	status->tokens = NULL;
	free_str_list(status->lst_args);
	status->lst_args = NULL;
	free_str_list(status->lst_redirections);
	status->lst_redirections = NULL;
	free_array(status->args);
	status->args = NULL;
	free_array(status->redirections);
	status->redirections = NULL;
	if (status->command)
	{
		if (status->command->command_type == CMD_ABS_PATH)
			free(status->command->u_command_ref.command_path);
	}
	free(status->command);
	status->command = NULL;
}

void	set_exit_status(t_status *status)
{
	if (WIFEXITED(status->child_exit_status))
		status->exit_status = WEXITSTATUS(status->child_exit_status);
	else
		status->exit_status = 1;
}

void	free_and_exit(t_status *status)
{
	free_status(status);
	exit(1);
}
