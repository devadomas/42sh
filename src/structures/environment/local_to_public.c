/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_to_public.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:30:54 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:57:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_local_to_public(t_env *env, char *key)
{
	int			i;
	int			index;
	t_env_item	*item;

	i = 1;
	index = env_get_hash(key, env->size, 0);
	item = env->items[index];
	while (item)
	{
		if (item->key && item->value && item->local
		&& !ft_strcmps(item->key, key))
		{
			item->local = false;
			return ;
		}
		index = env_get_hash(key, env->size, i);
		item = env->items[index];
		i++;
	}
}
