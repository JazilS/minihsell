/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:03:37 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/09 17:13:32 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "pipex_bonus.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# define REDIR_IN 1
# define FILE_IN 2
# define FILE_OUT 3
# define REDIR_OUT 4
# define PIPE 5
# define COMMAND 6
# define ARG 7
# define HERE_DOC 8
# define APPEND 9


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

typedef struct s_data_2
{
	int				cmd_count;
	int				parsed_list_size;
	int				reduced_size;
}	t_data_2;




t_temp 				*temp_list(t_data_2 *data);
int					first_char(char **str_split, char *str, t_data_2 *data, int i);
t_temp				*my_lstnew(char *content, int status);
void				my_lstadd_back(t_temp **lst, t_temp *new);
void				print_cmd_list(t_cmd *token);
void				print_list(t_temp *token);
t_cmd				*my_lstnew_cmd(int zero);
void				my_lstadd_back_cmd(t_cmd **lst, t_cmd *new);

#endif