/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:26:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 20:28:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_history_option_c(t_shell *sh)
{
	ft_putendl("... history clearing start");
	command_delete_all(sh);
	remove(env_search(sh->local_env, "HISTFILE"));
	ft_putendl("... history clearing end");
	return (0);
}
