/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 09:05:58 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/06 12:22:55 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			exc_double(t_shell *shell, bool *status)
{
	int				offset;
	char			*track;
	char			*ptr_to_exc;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(shell->buffer.content + offset++, "!!")))
	{
		track = shell->buffer.content;
		sh_move_home(shell);
		while (track++ != ptr_to_exc)
			sh_move_right(shell);
		if (shell->cmd)
		{
			sh_delete_current_char(shell);
			sh_delete_current_char(shell);
			auto_manage_buffer(shell, shell->cmd->content);
			*status = true;
		}
		sh_move_end(shell);
	}
}

t_cmd				*get_cmd_by_id(t_shell *shell, int id)
{
	t_cmd			*cmd;

	if (id < 0 && shell->cmd)
		id += shell->cmd->id + 1;
	if (!shell->cmd
			|| (unsigned)id > shell->cmd->id
			|| (unsigned)id < !shell->cmd->last->id)
		return NULL;
	cmd = shell->cmd;
	while (cmd && (unsigned)id != cmd->id)
		cmd = cmd->next;
	return (cmd);
}

static int			good_number_of_digits(char *str)
{
	int				number_of_digits;
	int				minus;

	minus = 0;
	number_of_digits = 0;
	if (*str == '-')
	{
		str++;
		minus = 1;
	}
	while (ft_isdigit(*(str++)))
		number_of_digits++;
	if (number_of_digits && number_of_digits <= 6)
		return (number_of_digits + minus);
	return (0);
}

static void			exc_number(t_shell *shell, bool *status)
{
	int				number_of_deletions;
	int				offset;
	char			*track;
	char			*ptr_to_exc;
	t_cmd			*cmd;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(shell->buffer.content + offset++, "!")))
	{
		if ((number_of_deletions = good_number_of_digits(ptr_to_exc + 1) + 1))
		{
			if((cmd = get_cmd_by_id(shell, ft_atoi(ptr_to_exc + 1))))
			{
				track = shell->buffer.content;
				sh_move_home(shell);
				while (track++ != ptr_to_exc)
					sh_move_right(shell);
				while (number_of_deletions--)
					sh_delete_current_char(shell);
				auto_manage_buffer(shell, cmd->content);
				*status = true;
				sh_move_end(shell);
			}
		}
	}
}

bool				auto_history(t_shell *shell)
{
	bool			status;

	status = false;
	exc_double(shell, &status);
	exc_number(shell, &status);
	return (status);
}