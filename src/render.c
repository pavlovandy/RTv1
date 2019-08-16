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

#define BACKGROUND_COLOR	(t_vector){0, 0, 0}

t_vector	canvas_to_viewport(int x, int y)
{
	return ((t_vector){(double)x * VW / WIN_WIDTH, \
								-(double)y * VH / WIN_HEIGHT, (double)D});
}

void		check_closest_inter(t_rt *rt, t_pixel_cal *pc)
{
	int		obj_iter;
	t_roots	roots;

	pc->closest_dist = BIG_VALUE;
	pc->closest_obj = -1;
	obj_iter = -1;
	while (++obj_iter < rt->scene.count_obj)
	{
		roots = rt->fun.inter_f[rt->scene.obj[obj_iter].fig_type](\
		pc->eye_point, pc->eye_point_dir, rt->scene.obj[obj_iter].data, pc);
		if (roots.t1 < pc->closest_dist && roots.t1 > 1)
		{
			pc->closest_dist = roots.t1;
			pc->closest_obj = obj_iter;
			if (rt->scene.obj[obj_iter].fig_type == PLANE)
				pc->sign = pc->dp_d_v < 0 ? 1 : -1;
		}
		if (roots.t2 < pc->closest_dist && roots.t2 > 1)
		{
			pc->closest_dist = roots.t2;
			pc->closest_obj = obj_iter;
			if (rt->scene.obj[obj_iter].fig_type == PLANE)
				pc->sign = pc->dp_d_v < 0 ? 1 : -1;
		}
	}
}

t_vector	ray_trace(t_vector eye_point, t_vector eye_dir, t_rt *rt)
{
	t_pixel_cal		pc;

	pc.eye_point = eye_point;
	pc.eye_point_dir = eye_dir;
	check_closest_inter(rt, &pc);
	if (pc.closest_obj > -1)
	{
		if (rt->scene.obj[pc.closest_obj].fig_type == SPHERE)
			sphere_cal(&pc, rt->scene.obj[pc.closest_obj].data);
		else if (rt->scene.obj[pc.closest_obj].fig_type == PLANE)
			plane_cal(&pc, rt->scene.obj[pc.closest_obj].data);
		else if (rt->scene.obj[pc.closest_obj].fig_type == CONE)
			cone_cal(&pc, rt->scene.obj[pc.closest_obj].data);
		else if (rt->scene.obj[pc.closest_obj].fig_type == CYLIN)
			cylin_cal(&pc, rt->scene.obj[pc.closest_obj].data);
		return (multi_vect(pc.color, calculate_lighting(&pc, rt)));
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
			d = ft_rotate_camera(d, &rt->pov);
			color = ray_trace(rt->pov.coord, d, rt);
			color = trim_color(color);
			put_pixel(x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, \
										RGB(color), rt->sdl.win_sur);
		}
	}
	SDL_UpdateWindowSurface(rt->sdl.win);
}
