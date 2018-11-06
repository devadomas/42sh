/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:59:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 17:34:39 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			job_destroy_all(t_job *job)
{
	(void)job;
	ft_printf("JOBS: destroying jobs!\n");
	free(job);
}