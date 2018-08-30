/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:45:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/26 21:29:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment_init(t_shell *shell, t_env **env, char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		environment_add(shell, env, environ[i]);
		i++;
	}
	if (*env)
		shell->env = (*env)->head;
}