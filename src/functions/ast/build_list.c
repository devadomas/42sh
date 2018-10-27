/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 21:08:41 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 17:39:53 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			tree_splice_point(t_lexer lexer, size_t i)
{
	if (lexer.tokens[i].type == TOKEN_ANDIF ||
		lexer.tokens[i].type == TOKEN_AGGREG ||
		lexer.tokens[i].type == TOKEN_ORIF ||
		lexer.tokens[i].type == TOKEN_REDIR ||
		lexer.tokens[i].type == TOKEN_SEMICOLON ||
		lexer.tokens[i].type == TOKEN_PIPE ||
		lexer.tokens[i].type == TOKEN_REDIR)
		return (true);
	return (false);
}

static void			tree_group_token(t_lexer lexer, t_token_tree **head,
										size_t len, size_t begin)
{
	t_token_tree		*new;
	size_t				i;

	if (len == 0 || !(new = new_tree_node()))
		return ;
	new->size = len;
	new->type = (len > 1 ? 0 : get_tree_token_type(lexer.tokens[begin]));
	if (!(new->tokens = (char **)ft_memalloc(sizeof(char *) * (len + 1))))
		error_malloc_reader(g_sh, "token");
	new->tokens[len] = NULL;
	i = 0;
	while (i < len)
	{
		new->tokens[i] = ft_strdup(lexer.tokens[i + begin].id);
		i++;
	}
	add_tree_to_back(head, new);

}

t_token_tree		*build_list(t_lexer lexer)
{
	t_token_tree		*head;
	size_t				len;
	size_t				i;

	head = NULL;
	len = 0;
	i = 0;
	// printf("Lexer output:\n");
	// for (size_t x = 0; x < lexer.size; x++)
	// 	printf("%zu: token: %s | type: %d\n", x, lexer.tokens[x].id, lexer.tokens[x].type);
	while (i < lexer.size)
	{
		if (tree_splice_point(lexer, i))
		{
			tree_group_token(lexer, &head, len, i - len);
			tree_group_token(lexer, &head, 1, i);
			len = 0;
		}
		else
			len++;
		i++;
	}
	tree_group_token(lexer, &head, len, i - len);
	// printf("Token group output:\n");
	// while (head)
	// {
	// 	printf("Class: %d | size: %zu | Elements: ", head->type, head->size);
	// 	for (size_t i = 0; i < head->size; i++)
	// 		printf("%s ", head->tokens[i]);
	// 	printf("\n");
	// 	head = head->right;
	// }
	return (head);
}
