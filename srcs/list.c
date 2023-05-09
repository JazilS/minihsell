/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:03:03 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/09 17:13:19 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_temp *token)
{
	t_temp	*temp;

	temp = token;
	while (temp)
	{
		printf("str =		%s\n", temp->token);
		printf("status =	%d\n\n", temp->status);
		temp = temp->next;
	}
}

void	print_cmd_list(t_cmd *token)
{
	int		i;
	t_cmd	*temp;

	temp = token;
	while (temp)
	{
		i = 0;
		while (temp->arg[i])
		{
			printf("arg[%d]=		%s\n", i, temp->arg[i]);
			i++;
		}
		temp = temp->next;
	}
}


void	my_lstadd_back(t_temp **lst, t_temp *new)
{	
	t_temp	*current_node;

	current_node = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new;
}

t_temp	*my_lstnew(char *content, int status)
{
	t_temp	*liste;

	liste = malloc(sizeof(*liste));
	liste->token = content;
	liste->status = status;
	liste->next = NULL;
	return (liste);
}

void	my_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{	
	t_cmd	*current_node;

	current_node = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new;
}

t_cmd	*my_lstnew_cmd(int zero)
{
	t_cmd	*liste;

	liste = malloc(sizeof(*liste));
	liste->next = NULL;
	liste->fd_in = zero;
	liste->fd_out = zero;
	return (liste);
}

int	first_char(char **str_split, char *str, t_data_2 *data, int i)
{
	if(str[0] == '<')
		return (REDIR_IN);
	else if(str[0] == '>')
		return (REDIR_OUT);
	else if(str[0] == '|')
		return (PIPE);
	else
	{
		if (i == 0 || str_split[i - 1][0] == '|')
		{
			data->cmd_count += 1;
			return (COMMAND);
		}
		else if (str_split[i - 1][0] == '>')
			return (FILE_OUT);
		else if (str_split[i - 1][0] == '<')
			return (FILE_IN);
		else
			return (ARG);
	}
	return (0);
}

t_temp *temp_list(t_data_2 *data)
{
	t_temp	*list;
	int		i;
	char	**str_split;
	
	i = 0;
	list = NULL;
	str_split = ft_split("cat arg | cat arg < in arg | cat arg arg arg < in > out" , ' ');
	while (str_split[i])
	{
		my_lstadd_back(&list, my_lstnew(str_split[i], first_char(str_split, str_split[i], data, i)));
		i++;
	}
	data->parsed_list_size = i;
	print_list(list);
	printf("----nombre d'exec = %d\n", data->cmd_count);
	printf("----parsed list size = %d\n", data->parsed_list_size);
	return (list);
}
