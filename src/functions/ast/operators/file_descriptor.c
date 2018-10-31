/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 10:34:55 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/31 21:14:38 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	do_aggregation(t_shell *sh, t_token_tree *tree, char *front,
								char *cmd)
{
	int		closed;
	char	*back;
	char	ret;
	int		fd[3];

	closed = (!ft_strncmp(cmd, ">&", 2) ? 1 : 0);
	if (!(back = get_back_descriptor(cmd)))
		error_malloc_reader(sh, "token");
	fd[0] = ft_atoi(front);
	fd[1] = ft_atoi(back);
	if ((fd[0] == 0 && !ft_strcmp(front, "0")) || (*back != '-' && fd[1] == 0))
	{
		ft_strdel(&back);
		return (error_file_descriptor());
	}
	fd[2] = dup(fd[0]);
	(*back != '-') ? (dup2(fd[1], fd[0])) : (close(fd[0]));
	ret = execute_tree(sh, tree->left);
	dup2(fd[2], fd[0]);
	close(fd[2]);
	ft_strdel(&back);
	return (ret);
}

char		execute_fd_aggr(t_shell *sh, t_token_tree *tree)
{
	size_t		len;
	char		ret;
	char		*cmd;
	char		*front;

	len = 0;
	cmd = tree->tokens[0];
	while (cmd[len] != '\0' && (cmd[len] != '>' && cmd[len] != '<'))
		len++;
	if (!(front = get_front_descriptor(cmd, len,
				(!ft_strncmp(cmd + len, ">&", 2) ? 1 : 0))))
		error_malloc_reader(sh, "token");
	ret = do_aggregation(sh, tree, front, cmd + len);
	ft_strdel(&front);
	return (ret);
}
