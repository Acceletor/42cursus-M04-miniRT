/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:21 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:03:22 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	to_byte(double x)
{
	if (x <= EPSILON)
		return (0);
	if (x >= 1.0)
		return (255);
	return ((int)(x * 255.999));
}

static int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

int	vec_to_rgb(t_vec c) // expects 0..1
{
	return (create_rgb(to_byte(c.x), to_byte(c.y), to_byte(c.z)));
}

t_vec	clamp01(t_vec c)
{
	if (c.x < EPSILON)
		c.x = EPSILON;
	if (c.y < EPSILON)
		c.y = EPSILON;
	if (c.z < EPSILON)
		c.z = EPSILON;
	if (c.x > 1.0)
		c.x = 1.0;
	if (c.y > 1.0)
		c.y = 1.0;
	if (c.z > 1.0)
		c.z = 1.0;
	return (c);
}
