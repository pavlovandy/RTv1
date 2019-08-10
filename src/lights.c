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

float		calculate_lighting(t_pixel_cal *p_pc, t_rt *rt)
{
	int			i;
	t_light		*light;
	t_pixel_cal	pc;

	pc = *p_pc;
	pc.intensity = 0.f;
	i = -1;
	while (++i < rt->scene.count_light)
	{
		light = rt->scene.light + i;
		if (light->type_num == AMBIENT)
			pc.intensity += light->intensity;
		else 
		{
			if (light->type_num == POINT)
				pc.l = light->v - pc.p;
			else
				pc.l = light->v;
			pc.scalar = dot_prod(pc.n, pc.l);
			if (pc.scalar > 0)
				pc.intensity += (light->intensity * pc.scalar / (vect_len(pc.l) * vect_len(pc.n)));
			if (pc.specular != -1) 
			{
				pc.r =  multi_vect(pc.n, 2 *dot_prod(pc.n, pc.l)) - pc.l;
				pc.scalar = dot_prod(pc.r, pc.v);
				if (pc.scalar > 0)
					pc.intensity += light->intensity * pow(pc.scalar / (vect_len(pc.r) * vect_len(pc.v)), pc.specular);
			}
		}
	}
	return (pc.intensity);
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