/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/12 17:56:10 by kgezgin          ###   ########.fr       */
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
	if (list->fd_out > 0 && dup2(list->fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error fd_out");
		// free
		exit(EXIT_FAILURE); // recuperer le bon code erreur
	}
}


void	exec_pipe(t_cmd *list, t_data *data)
{
	int	previous_fd;

	previous_fd = -1;
	while (list)
	{
		// printf("	fd in avant exec = %d\n\n", list->fd_in);
		if (list->is_ok)
		{
			if (list->next)
			{
					previous_fd = data->fd_pipe[0];
					if (pipe(data->fd_pipe) == -1)
						return (perror("Pipe"));
					if (list->fd_in == 0)
						list->fd_in = previous_fd;
					if (list->fd_out == 0)
						list->fd_out = data->fd_pipe[1];
			}
			else
			{

					previous_fd = data->fd_pipe[0];
					if (list->fd_in == 0)
						list->fd_in = previous_fd;
					close(data->fd_pipe[1]);
			}
			data->pid[data->index] = fork();
			if (data->pid[data->index] == 0)
			{
				// dprintf(2, "previous fd	= %d\n", previous_fd);
				// dprintf(2, "fd_pipe[0]	= %d\n", data->fd_pipe[0]);
				// dprintf(2, "fd_pipe[1]	= %d\n", data->fd_pipe[1]);
				// dprintf(2, "fd_out		= %d\n", list->fd_out);
				// dprintf(2, "fd_in 		= %d\n", list->fd_in);
				if (list->fd_in == -1)
				{
					printf("test");
					perror("fd_in");
					// free
					exit (1);
				}
				else if (list->fd_out == - 1)
				{
					perror("fd_out");
					// free
					exit (1);
				}
				redirections(list);
				get_path_and_exec(list, data);
			}
			list = list->next;
			data->index++;
		}
		else
		{
			list = list->next;
			data->index++;
		}
	}
}
void	get_path_and_exec(t_cmd *list, t_data *data)
{
	ft_path(data->env, data);
	if (is_path(list->command) == 1)
		data->path = list->command;
	else
		data->path = path_check(data, list);
	// dprintf(2, "\ndata->path = %s\n", data->path);
	// int i = 0;
	// while (list->arg[i])
	// {
		// dprintf(2, "list->arg[%d] = %s\n\n", i, list->arg[i]);
		// i++;
	// }
	execve(data->path, list->arg, data->env);
}

void	exec_one_command(t_cmd *list, t_data *data)
{
	if (list->is_ok)
	{
		data->pid[0] = fork();
		if (data->pid[0] == 0)
		{
			// dprintf(2, "fd_in 		= %d\n", list->fd_in);
			// dprintf(2, "fd_out		= %d\n", list->fd_out);
			redirections(list);
			get_path_and_exec(list, data);
		}
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
		exec_one_command(list, data);
	else
		exec_pipe(list, data);
	// ft_wait(data);
	wait(0);
	return (0);
}

void	ft_unlink(t_cmd *list)
{
	t_cmd	*temp;
	int		i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->here_doc_tmp[i])
		{
			unlink (temp->here_doc_tmp[i]);
			free (temp->here_doc_tmp[i]);
			free (temp->limiter[i]);
			i++;
		}
		free(temp->here_doc_tmp);
		free (temp->limiter);
		temp = temp->next;
	}
}

void	ft_free_list(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*tmp2;

	temp = (*lst);
	while (temp)
	{
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
}

int main (int ac, char **av, char **env)
{
	t_cmd			*cmd_list;
	t_temp			*token;
	t_data			data;
	// char			*str;

	(void)ac;
	// if (ac != 1)
	// 	return (printf("erreur arguments"), 1);
	// while (1)
	// {
	// 	str = readline("minishell$> ");
	// 	if (!str)
	// 			break ;
		init_data(&data, env);
		token = temp_list(&data, av, av[1]);
		cmd_list = create_cmd_list(token, &data);
		(void)cmd_list;
		main_exec(cmd_list, &data);
		ft_unlink(cmd_list);
		// unlink(".here_doc_1.tmp");
		// unlink(".here_doc_2.tmp");
		// add_history(str);
		// free(str);
	// }
	return (0);
}