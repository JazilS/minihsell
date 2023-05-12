/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:03:37 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/12 14:32:44 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include"../get_next_line/get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define REDIR_IN 1
# define FILE_IN 2
# define FILE_OUT 3
# define REDIR_OUT 4
# define PIPE 5
# define COMMAND 6
# define ARG 7
# define HERE_DOC 8
# define APPEND 9
# define LIMITER 10


typedef struct s_cmd
{
	char			*command;
	char			**arg;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_temp
{
	char			*token;
	int				status;
	struct s_temp	*next;
}	t_temp;

typedef struct s_token
{
	char			*token;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	int				cmd_count;
	int				parsed_list_size;
	int				fd_pipe[2];
	char			*path;
	int				index;
	char			**env;
	char			**path_begining;
	pid_t			*pid;
}	t_data;


void				print_list(t_temp *token);
void				print_cmd_list(t_cmd *token);
void				my_lstadd_back(t_temp **lst, t_temp *new);
t_temp				*my_lstnew(char *content, int status);
int					first_char(char *str, int prev_status);
t_temp 				*temp_list(t_data *data, char **av, char *str);

void				get_args(t_cmd *cmd_list, t_temp *parsed_list);
t_cmd				*get_value(t_cmd *cmd_list, t_temp *parsed_list);
t_cmd				*get_fd(t_cmd *cmd_list, t_temp *parsed_list);
t_cmd				*create_cmd_list(t_temp *parsed_list, t_data *data);
void				my_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd				*my_lstnew_cmd(int zero);
void				init_data(t_data *data, char **env);

void				redirections(t_cmd *list);
void				get_path_and_exec(t_cmd *list, t_data *data);
void				exec_pipe(t_cmd *list, t_data *data);
void				exec_one_command(t_cmd *list, t_data *data);
int					main_exec(t_cmd *list, t_data *data);

int					is_path(char *str);
char				*path_check(t_data *data, t_cmd *list);
void				ft_error_path(t_data *data, char *temp, t_cmd *list);
void				ft_path(char **envp, t_data *data);
void				ft_wait(t_data *data);


#endif