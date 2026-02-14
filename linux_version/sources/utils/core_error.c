/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:22 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:03:23 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_err(char *str, t_collector **g_root, int err)
{
	ft_printf("Error: %s\n", str);
	if (g_root && *g_root)
		gc_free_all(g_root);
	exit(err);
}
