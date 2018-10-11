/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:38:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 12:55:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	command_import_error(int fd, char *path)
{
	(path) ? remove(path) : 0;
	(path) ? ft_strdel(&path) : 0;
	(fd != -1) ? close(fd) : 0;
}

static char	command_key_verified(int fd)
{
	char	line[VERIF_KEY_LEN + 1];

	if (read(fd, line, VERIF_KEY_LEN + 1) != VERIF_KEY_LEN + 1)
		return (FALSE);
	line[VERIF_KEY_LEN] = '\0';
	if (ft_strcmps(line, VERIF_KEY))
		return (FALSE);
	return (TRUE);
}

static char	command_parse_and_add(t_shell *sh, char *content)
{
	t_cmd		*new;

	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return (FALSE);
	new->id = (sh->cmd) ? sh->cmd->id + 1 : 1;
	ft_strcpy(new->content, content);
	new->display_len = ft_strlenu(new->content);
	new->unicode_len = ft_strlens(new->content);
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
	return (TRUE);
}

void		command_import(t_shell *sh)
{
	int		fd;
	char	*path;
	char	*buffer;

	buffer = NULL;
	if (!(path = env_search(sh->env, "HISTFILE")))
		return ;
	if ((fd = open(path, O_RDONLY)) == -1 || !command_key_verified(fd))
		return (command_import_error(fd, path));
	while (get_next_line(fd, &buffer) == 1)
	{
		if (command_parse_and_add(sh, buffer) == 0)
		{
			ft_strdel(&buffer);
			return (command_import_error(fd, path));
		}
		ft_strdel(&buffer);
	}
	close(fd);
}
