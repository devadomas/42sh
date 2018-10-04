/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:43:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 13:15:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_cut_selection(t_shell *sh)
{
	int	start;
	int	stop;

	if (!sh->modes.select)
		return ;
	sh->modes.browse = FALSE;
	start = sh->selection.start_abs;
	stop = sh->selection.stop;
	sh_copy_selection(sh);
	while (sh->cursor.abs_pos < stop)
		sh_move_right(sh);
	while (sh->cursor.abs_pos > start)
		sh_delete_char(sh);
}
