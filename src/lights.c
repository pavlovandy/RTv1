/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:23:45 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/09 18:23:46 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			check_shadow_inter(t_pixel_cal *pc, t_rt *rt, double min, double max)
{
	int		obj_iter;
	double	closest_dist;
	int		closest_obj;
	t_roots	roots;

	closest_dist = max;
	closest_obj = -1;
	obj_iter = -1;
	while (++obj_iter < rt->scene.count_obj)
	{
		roots = rt->fun.inter_f[rt->scene.obj[obj_iter].fig_type]\
			(pc->intersect_point, pc->light_dir, rt->scene.obj[obj_iter].data, pc);
		if (roots.t1 < closest_dist && roots.t1 > min)
		{
			closest_dist = roots.t1;
			closest_obj = obj_iter;
		}
		if (roots.t2 < closest_dist && roots.t2 > min)
		{
			closest_dist = roots.t2;
			closest_obj = obj_iter;
		}
	}
	return (closest_obj);
}

double		calculate_lighting(t_pixel_cal *pc, t_rt *rt)
{
	int			i;
	t_light		*light;
	double		t_max;
	
	pc->intensity = 0.f;
	i = -1;
	while (++i < rt->scene.count_light)
	{
		light = rt->scene.light + i;
		if (light->type_num == AMBIENT)
			pc->intensity += light->intensity;
		else 
		{
			if (light->type_num == POINT)
				pc->light_dir = light->v - pc->intersect_point;
			else
				pc->light_dir = light->v;
			t_max = (light->type_num == POINT) ? 1 : BIG_VALUE;
			if (check_shadow_inter(pc, rt, 0.0000000001, t_max) != -1)
				continue ;
	
			pc->scalar = dot_prod(pc->normal, pc->light_dir);
			if (pc->scalar > 0)
				pc->intensity += (light->intensity * pc->scalar / (vect_len(pc->light_dir) * vect_len(pc->normal)));
			if (pc->specular != -1)
			{
				pc->reflected_ray =  multi_vect(pc->normal, 2 *dot_prod(pc->normal, pc->light_dir)) - pc->light_dir;
				pc->scalar = dot_prod(pc->reflected_ray, pc->to_eye_dir);
				if (pc->scalar > 0)
					pc->intensity += light->intensity * pow(pc->scalar / (vect_len(pc->reflected_ray) * vect_len(pc->to_eye_dir)), pc->specular);
			}
		}
	}
	return (pc->intensity);
}

int		get_light_type(t_light *light)
{
	if (ft_strcmp(light->type, "point") == 0)
		light->type_num = POINT;
	else if (ft_strcmp(light->type, "direct") == 0)
		light->type_num = DIRECT;
	else if (ft_strcmp(light->type, "ambient") == 0)
		light->type_num = AMBIENT;
	else
		return (error_message(IRED"Wrong light type"COLOR_OFF));
	return (0);
}

int		read_light_data(int fd, t_light *light)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_string(fd, &light->type, "type : {"))
		return (1);
	if (get_light_type(light))
		return (1);
	if (check_line_for_value(fd, &light->intensity, "intensity : {"))
		return (1);
	if (light->intensity < 0)
		return (error_message(TCYN"Light intensity less then zero"TNULL));
	if (light->type_num == POINT || light->type_num == DIRECT)
		if (check_line_for_coord(fd, &light->v, "v : {"))
			return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
