/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 16:30:14 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 17:14:31 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				jobs_display(t_shell *sh)
{
	t_process		*process;

	process = sh->process;
	while (process)
	{
		process_display(process);
		process = process->next;
	}
}