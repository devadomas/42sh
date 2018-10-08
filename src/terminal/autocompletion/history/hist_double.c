/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 08:17:10 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:43:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

void				auto_hist_double(t_shell *sh, bool *status)
{
	int				offset;
	char			*track;
	char			*ptr_to_exc;

	offset = 0;
	while ((ptr_to_exc = ft_strstr(sh->buffer.content + offset++, "!!")))
	{
		track = sh->buffer.content;
		sh_move_home(sh);
		while (track++ != ptr_to_exc)
			sh_move_right(sh);
		if (sh->cmd)
		{
			sh_delete_current_char(sh);
			sh_delete_current_char(sh);
			auto_manage_buffer(sh, sh->cmd->content);
			*status = true;
		}
		sh_move_end(sh);
	}
}