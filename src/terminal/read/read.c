/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 19:17:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_read(t_shell *sh)
{
	sh_print_prompt(sh);
	while (TRUE)
	{
		if (read(0, sh->read->line, LINE_SIZE - 1) == -1)
			break ;
		if (sh->read->line[0] == 4
		&& !sh->modes.multiline)
			break ;
		sh_read_dispatcher(sh);
		ft_bzero(sh->read->line, LINE_SIZE);
	}
}
