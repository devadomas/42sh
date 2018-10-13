/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:09:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 18:42:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_export_add_noequal(t_env *env, char *key)
{
	char	*value;

	value = env_search_local(env, key);
	if (env_search_public(env, key))
		return (sh_export_error(NULL, NULL, 5, key));
	if (!value)
		return (sh_export_error(NULL, NULL, 3, key));
	env_local_to_public(env, key, value);
	return (0);
}

static char	sh_export_add_equal(t_shell *sh, t_env *env, char *arg)
{
	int			bin;
	int			eq_sym;
	char		*key;
	char		*val;
	t_bin_obj	*obj;

	bin = sh_export_isbin(arg);
	key = sh_export_parse(ft_strdups(arg));
	eq_sym = sh_setenv_equal(key);
	val = (bin)
		? ft_strdups(arg + bin) : ft_strdups(ft_strchrsp(key, '='));
	key[eq_sym] = '\0';
	if (bin && !(obj = bin_search(sh->bin, val)))
		return (sh_export_error(key, val, 3, NULL));
	if (!env_search(env, key) && env->count + 1 >= env->size)
		return (sh_export_error(key, val, 4, NULL));
	(bin)
		? env_insert(sh, env, key, obj->path)
		: env_insert(sh, env, key, val);
	env_local_to_public(env, key, val);
	ft_strdel(&key);
	ft_strdel(&val);
	return (0);
}

char		sh_export_add(t_shell *sh, t_env *env, char *arg)
{
	if (!arg || arg[0] == '=')
		return (sh_export_error(NULL, NULL, 2, NULL));
	if (ft_strcountif(arg, '=') == 0)
		return (sh_export_add_noequal(env, arg));
	return (sh_export_add_equal(sh, env, arg));
}