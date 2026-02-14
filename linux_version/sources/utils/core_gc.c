/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:24 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:03:25 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	gc_free_all(t_collector **g_root)
{
	t_collector	*tmp;

	while (*g_root)
	{
		tmp = (*g_root)->next;
		free((*g_root)->adr);
		free(*g_root);
		*g_root = tmp;
	}
}

t_collector	*new_node(void *adr)
{
	t_collector	*node;

	node = malloc(sizeof(t_collector));
	if (!node)
		return (NULL);
	node->adr = adr;
	node->next = NULL;
	return (node);
}

int	gc_append_adr(t_collector **g_root, void *adr)
{
	t_collector	*node;
	t_collector	*tmp;

	node = new_node(adr);
	if (!node)
		return (0);
	if (!*g_root)
	{
		*g_root = node;
		return (1);
	}
	tmp = *g_root;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

void	*gc_malloc(t_collector **g_root, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_append_adr(g_root, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
