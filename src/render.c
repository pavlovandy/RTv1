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

#define BACKGROUND_COLOR	(t_vector){255, 255, 255}

t_vector	canvas_to_viewport(int x, int y)
{
	return ((t_vector){(float)x * VW / WIN_WIDTH, -(float)y * VH / WIN_HEIGHT, (float)D});
}

t_vector	ray_trace(t_vector view_point, t_vector view_port, t_rt *rt)
{
	int		obj_iter;
	t_sphere_data *data;
	t_pixel_cal		pc;

	pc.closest_dist = BIG_VALUE;
	pc.closest_obj = -1;
	obj_iter = -1;
	while (++obj_iter < rt->scene.count_obj)
	{
		pc.roots = sphere_roots(view_point, view_port, rt->scene.obj[obj_iter].data);
		if (pc.roots.t1 < pc.closest_dist && pc.roots.t1 > 1)
		{
			pc.closest_dist = pc.roots.t1;
			pc.closest_obj = obj_iter;
		}
		if (pc.roots.t2 < pc.closest_dist && pc.roots.t2 > 1)
		{
			pc.closest_dist = pc.roots.t2;
			pc.closest_obj = obj_iter;
		}
	}
	if (pc.closest_obj > -1)
	{
		pc.p = view_point + multi_vect(view_port, pc.closest_dist);
		data = rt->scene.obj[pc.closest_obj].data;
		pc.n = pc.p - data->cent;
		pc.n = multi_vect(pc.n, (1.0 / vect_len(pc.n)));
		pc.specular = data->specular;
		pc.v = -view_port;
		return (multi_vect(data->color, calculate_lighting(&pc, rt)));
	}
	return (BACKGROUND_COLOR);
}

void		start_render(t_rt *rt)
{
	int			x;
	int			y;
	t_vector	d;
	t_vector	color;

	y = -WIN_HEIGHT / 2 - 1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -WIN_WIDTH / 2 - 1;
		while (++x < WIN_WIDTH / 2)
		{
			d = canvas_to_viewport(x, y);
			color = ray_trace(rt->pov.coord, d, rt);
			if (color[0] > 255)
				color[0] = 255;
				if (color[1] > 255)
				color[1] = 255;
				if (color[2] > 255)
				color[2] = 255;
			put_pixel(x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, RGB(color), rt->sdl.win_sur);
		}
	}
}
