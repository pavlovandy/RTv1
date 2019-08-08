/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:31:39 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:31:44 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#define BACKGROUND_COLOR	0xffffff


t_vector	canvas_to_viewport(int x, int y)
{
	return ((t_vector){(float)x * VW / WIN_WIDTH, (float)y * VH / WIN_HEIGHT, (float)D});
}

Uint32		ray_trace(t_vector view_point, t_vector view_port, t_rt *rt)
{
	int		closest_obj;
	float	closest_dist;
	t_roots	roots;
	int		obj_iter;
	t_sphere_data *data;

	closest_dist = BIG_VALUE;
	closest_obj = -1;

	obj_iter = -1;
	while (++obj_iter < rt->scene.count_obj)
	{
		roots = sphere_roots(view_point, view_port, rt->scene.obj[obj_iter].data);

		if (roots.t1 < closest_dist && roots.t1 > 1)
		{
			closest_dist = roots.t1;
			closest_obj = obj_iter;
		}
		if (roots.t2 < closest_dist && roots.t2 > 1)
		{
			closest_dist = roots.t2;
			closest_obj = obj_iter;
		}
	}
	if (closest_obj > -1)
	{
		data = rt->scene.obj[closest_obj].data;
		return (data->color);
	}
	return (BACKGROUND_COLOR);
}

void		start_render(t_rt *rt)
{
	int			x;
	int			y;
	t_vector	d;
	t_vector	o;
	Uint32		color;

	o = (t_vector){0, 0, 0};

	y = -WIN_HEIGHT / 2 - 1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -WIN_WIDTH / 2 - 1;
		while (++x < WIN_WIDTH / 2)
		{
			d = canvas_to_viewport(x, y);
			color = ray_trace(o, d, rt);
			put_pixel(x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, color, rt->sdl.win_sur);
		}
	}
}
