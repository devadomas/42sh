/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:26:03 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 15:50:26 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <limits.h>

static t_job	*job_get_top(t_job *job)
{
	t_job		*cpy;
	int			top;

	cpy = job;
	top = INT_MIN;
	while (cpy)
	{
		if (cpy->rank > top)
			top = cpy->rank;
		cpy = cpy->next;
	}
	while (job)
	{
		if (job->rank == top)
			return (job);
		job = job->next;
	}
	return (NULL);
}

static t_job	*job_get_sec(t_job *job, t_job *top)
{
	t_job		*cpy;
	int			sec;

	cpy = job;
	sec = INT_MIN;
	while (cpy)
	{
		if (cpy->rank > sec && cpy != top)
			sec = cpy->rank;
		cpy = cpy->next;
	}
	while (job)
	{
		if (job->rank == sec)
			return (job);
		job = job->next;
	}
	return (NULL);
}

static char		job_get_rank(t_job *job)
{
	t_job		*top;
	t_job		*sec;

	top = job_get_top(job);
	sec = job_get_sec(job, top);
	if (job == top)
		return ('+');
	if (job == sec)
		return ('-');
	return (' ');
}

static char		*job_get_status(t_job *job)
{
	if (!job)
		return (NULL);
	if (job_is_stopped(job) && !job_is_completed(job))
		return ("suspended");
	else if (job_is_completed(job))
		return ("done");
	return ("running");
}

void			jobs_display(t_job *job)
{
	char		rank;
	char		*status;

	if (!job)
		return ;
	while (job)
	{
		rank = job_get_rank(job);
		status = job_get_status(job);
		ft_printf("[%d] %c %6s %s\n", job->id, rank, status, job->command);
		job = job->next;
	}
}
