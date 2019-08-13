/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:49:53 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/12 17:49:54 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		cone_cal(t_pixel_cal *pc, t_cone_data *cone)
{
	double			value;

	pc->intersect_point = pc->eye_point + multi_vect(pc->eye_point_dir, pc->closest_dist);
	pc->color = cone->color;
	pc->specular = cone->specular;
	pc->a = dot_prod(pc->eye_point_dir, cone->dir) * \
							pc->closest_dist + dot_prod(pc->oc, cone->dir);
	value = cone->tangent * cone->tangent + 1;
	pc->normal = pc->intersect_point - cone->vertex - multi_vect(cone->dir, pc->a * value);
	pc->to_eye_dir = -pc->eye_point_dir;
}

t_roots		cone_roots(t_vector eye, t_vector eye_dir, void *data, t_pixel_cal *pc)
{
	t_cone_data		*cone;
	double			value;

	cone = (t_cone_data*)data;
	pc->oc = eye - cone->vertex;
	pc->dp_d_v = dot_prod(eye_dir, cone->dir);
	pc->dp_x_v = dot_prod(pc->oc, cone->dir);

	value = (1 + cone->tangent * cone->tangent);
	pc->a = dot_prod(eye_dir, eye_dir) - value * pc->dp_d_v * pc->dp_d_v;
	pc->b = dot_prod(eye_dir, pc->oc) - value * pc->dp_d_v * pc->dp_x_v;
	pc->c = dot_prod(pc->oc, pc->oc) - value * pc->dp_x_v * pc->dp_x_v;
	pc->d = pc->b * pc->b - pc->a * pc->c;
	if (pc->d < 0)
		return ((t_roots){BIG_VALUE, BIG_VALUE});
	pc->d = sqrt(pc->d);
	return ((t_roots){(-pc->b - pc->d) / pc->a, (-pc->b + pc->d) / pc->a});
}

int		read_cone_data(int fd, t_cone_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->vertex, "vertex : {"))
		return (1);
	if (check_line_for_value(fd, &data->tangent, "angle : {"))
		return (1);
	data->tangent = tan(data->tangent / 2 * M_PI / 180);
	if (check_line_for_coord(fd, &data->dir, "dir : {"))
		return (1);
	if (make_unit_vector(&data->dir))
		return (error_message(TRED"Directional vector is 0-vector"TNULL));
	if (check_line_for_coord(fd, &data->color, "color : {"))
		return (1);
	if (data->color[0] > 255 || data->color[1] > 255 || data->color[2] > 255)
		return (error_message(TRED"Bad color values"TNULL));
	if (data->color[0] < 0 || data->color[1] < 0 || data->color[2] < 0)
		return (error_message(TRED"Bad color values"TNULL));
	if (check_line_for_int_value(fd, &data->specular, "specular : {"))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}