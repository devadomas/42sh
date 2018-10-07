/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:47:37 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:58:26 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_calc_len_file_name(t_ac *ac, t_obj *obj)
{
	int				len;
	char			*str;
	t_data			*data;

	data = &obj->data;
	str = data->str;
	len = ft_strlenu(str);
	data->len_of_str = len;
	if (data->dir || data->lnk || data->sock || data->wht
				|| data->ifo || auto_is_executeable(obj))
		data->len_of_str++;
	len++;
	if (len > ac->len_file_name)
		ac->len_file_name = len;
}
