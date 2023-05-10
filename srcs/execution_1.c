/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/10 16:30:32 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirections(t_cmd *list)
{
	if (list->fd_in > 0 && dup2(list->fd_in, STDIN_FILENO) == -1)
	{
		perror("Error fd_in");
		// free
		exit(EXIT_FAILURE); // recuperer le bon code erreur
	}
	// else
	// 	close (list->fd_in);
	if (list->fd_out > 0 && dup2(list->fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error fd_out");
		// free
		exit(EXIT_FAILURE); // recuperer le bon code erreur
	}
	if (list->fd_in)
		close(list->fd_in);	
	// if (list->fd_out)
	// 	close(list->fd_out);
}

void	get_path_and_exec(t_cmd *list, t_data *data)
{
	ft_path(data->env, data);
	if (is_path(list->command) == 1)
		data->path = list->command;
	else
		data->path = path_check(data, list);
	execve(data->path, list->arg, data->env);
}

void	exec_pipe(t_cmd *list, t_data *data)
{
	int	previous_fd;

	previous_fd = -1;
	while (list)
	{
		if (list->next)
		{
			previous_fd = data->fd_pipe[0];
			if (pipe(data->fd_pipe) == -1)
				return (perror("Pipe"));
			if (list->fd_in < 1)
				list->fd_in = previous_fd;
			if (list->fd_out < 1)
				list->fd_in = data->fd_pipe[1];
		}
		else
			close(data->fd_pipe[1]);
		data->pid[data->index] = fork();
		if (data->pid[data->index] == 0)
		{
			redirections(list);
			get_path_and_exec(list, data);
		}
		list = list->next;
		data->index++;
	}		
}

void	exec_one_command(t_cmd *list, t_data *data)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		redirections(list);
		get_path_and_exec(list, data);
	}
}

int	main_exec(t_cmd *list, t_data *data)
{
	// print_cmd_list(list);
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	data->index = 0;
	data->fd_pipe[0] = 0;
	data->fd_pipe[1] = 0;
	if (data->cmd_count == 1)
	{
		exec_one_command(list, data);
		// free et close ce qu'il faut
		exit (EXIT_SUCCESS);
	}
	else
		exec_pipe(list, data);
	ft_wait(data);
	return (0);
}

int main (int ac, char **av, char **env)
{
	t_cmd			*cmd_list;
	t_temp			*token;
	t_data			data;
	char			*str;

	(void)ac;
	// if (ac != 1)
	// 	return (printf("erreur arguments"), 1);
	while (1)
	{
		str = readline("minishell$> ");
		if (!str)
				break ;
		init_data(&data, env);
		token = temp_list(&data, av, str);
		cmd_list = create_cmd_list(token, &data);
		main_exec(cmd_list, &data);
		add_history(str);
		// free(str);
	}
	return (0);
}