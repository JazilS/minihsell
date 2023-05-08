/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:03:37 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/08 19:52:01 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "pipex_bonus.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_cmd
{
	char			*command;
	char			**full_cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*token;
	struct s_token	*next;
}	t_token;

#endif