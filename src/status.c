/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfoucade <yfoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:06:03 by yfoucade          #+#    #+#             */
/*   Updated: 2022/09/01 13:04:16 by yfoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_status(t_status *status)
{
	status->input = NULL;
	status->pipelines = NULL;
	status->commands = NULL;
	status->curr_command = NULL;
	status->tokens = NULL;
	status->lst_args = NULL;
	status->lst_redirections = NULL;
	status->args = NULL;
	status->redirections = NULL;
	status->environ = NULL;
	status->in_pipe = NULL;
	status->out_pipe = NULL;
	status->curr_pipeline = NULL;
	status->prev_pipeline = NULL;
	status->command = NULL;
	status->error_msg = NULL;
	status->return_value = 0;
	status->exit_status = 0;
	status->in_fd = STDIN_FILENO;
	status->out_fd = STDOUT_FILENO;
}

void	free_status(t_status *status)
{
	free(status->input);
	free_str_list(status->pipelines);
	free_str_list(status->commands);
	// points to an element of status->commands, no need to free.
	// free_str_list(status->curr_command);
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

void	save_prev_pipeline(t_status *status)
{
	free(status->prev_pipeline);
	status->prev_pipeline = status->curr_pipeline;
	status->curr_pipeline = NULL;
}

void	free_curr_pipeline(t_status *status)
{
	free(status->curr_pipeline);
	status->curr_pipeline = NULL;
}

void	free_pipelines(t_status *status)
{
	free_str_list(status->pipelines);
	status->pipelines = NULL;
}

void	free_pipe(int **tab)
{
	free(*tab);
	*tab = NULL;
}

void	create_pipe(int **tab)
{
	*tab = malloc(sizeof(**tab) * 2);
	pipe(*tab);
}

void	close_pipe_end(int *tab, int end)
{
	close(tab[end]);
}

char	set_error_msg(t_status *status, char *str)
{
	free(status->error_msg);
	status->error_msg = ft_strdup(str);
	// if status->error_msg does not end with '\n', add a newline character.
	if (!status->error_msg)
		return (ERR_MALLOC);
	return (SUCCESS);
}

void	flush_error_msg(t_status *status)
{
	if (!status->error_msg)
		return ;
	printf("%s", status->error_msg);
	free(status->error_msg);
	status->error_msg = NULL;
	status->return_value = 0;
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
	if (status->command->command_type == CMD_ABS_PATH)
		free(status->command->u_command_ref.command_path);
	status->command->command_type = 0;
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