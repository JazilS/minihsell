/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:27:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/09 17:17:50 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_args(t_cmd *cmd_list, t_temp *parsed_list)
{
	int		i;
	t_cmd	*c_list;
	t_temp	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	while(c_list)
	{
		i = 0;
		while (p_list && p_list->status != PIPE)
		{
			if (p_list->status == ARG)
			{
				c_list->arg[i] = p_list->token;
				i++;
			}
			p_list = p_list->next;
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
}

t_cmd	*get_value(t_cmd *cmd_list, t_temp *parsed_list)
{
	int		i;
	t_cmd	*c_list;
	t_temp	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	while (c_list)
	{
		i = 0;
		while (p_list && p_list->status != PIPE)
		{
			if (p_list->status == ARG)
				i++;
			p_list = p_list->next;
		}
		c_list->arg = malloc(sizeof(char *) * i + 1);
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
	get_args(cmd_list, parsed_list);
	return (cmd_list);
}

t_cmd	*get_fd(t_cmd *cmd_list, t_temp *parsed_list)
{
	t_cmd	*c_list;
	t_temp	*p_list;
	
	p_list = parsed_list;
	while (c_list)
	{
		while (p_list && p_list->status != PIPE)
		{
			if (p_list->status == FILE_IN)
			{
				if (c_list->fd_in)
					close(c_list->fd_in);
				c_list->fd_in = open(p_list->token, O_RDONLY);
			}
			else if (p_list->status == FILE_OUT)
			{	
				if (c_list->fd_out)
					close(c_list->fd_out);
				c_list->fd_out = open(p_list->token, O_RDONLY);
			}
			p_list = p_list->next;
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
}

t_cmd	*create_cmd_list(t_temp *parsed_list, t_data_2 *data)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (i != data->cmd_count)
	{
		my_lstadd_back_cmd(&cmd_list, my_lstnew_cmd(0));
		i++;
	}
	cmd_list = get_fd(cmd_list, parsed_list);
	cmd_list = get_value(cmd_list, parsed_list);
	print_cmd_list(cmd_list);
	return (cmd_list);
}

void	init_data_2(t_data_2	*data)
{
	ft_memset(data, 0, sizeof(t_data_2));
	data->cmd_count = 0;
}

int main (int ac, char **av, char **env)
{
	t_cmd			*cmd_list;
	t_temp			*token;
	t_data_2			data;
	// char			*str;

	(void)env;
	(void)ac;
	(void)av;
	// while (1)
	// {
	// 	str = readline("minishell$> ");
	// 	add_history(str);
	// }
	init_data_2(&data);
	token = temp_list(&data);
	cmd_list = create_cmd_list(token, &data);
	// gerer les fd em premier puis recuperer tout les arguments etc ...
	(void)cmd_list;
	return (0);
}

